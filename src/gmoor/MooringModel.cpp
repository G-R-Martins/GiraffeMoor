#include "PCH.h"
#include "MooringModel.h"
#include "Summary.h"
#include "IO.h"
#include "AuxFunctions.h"

//max/min difinitions
#ifndef max
#define max(a,b)	(((a) > (b)) ? (a) : (b))
#endif
#ifndef min
#define min(a,b)	(((a) < (b)) ? (a) : (b))
#endif

// Map solution only for debug mode
#ifndef NDEBUG
#define MAP_SOLUTION_ITERATIONS
#endif

//Global object
extern GiraffeModel gm;
 
//Constants variables
constexpr auto PI = 3.1415926535897932384626433832795;

MooringModel::MooringModel()
	: cur_line(0), tot_elem(0), cur_node_mesh(1), cur_elem(1), cur_cs(2), 
	cur_node_set(1), cur_vessel(0), cur_special_constraint(0), cur_node_set_constraint(1), 
	cur_constraint(0), cur_load(0), cur_disp(0), cur_rbdata(0), node_set_contact_id(0), pil_node_set_id(0),
	existSharedLine(false), last_contact_node_id(0),
	x_tdp(0.0), x_tdp_ext(0.0), elem_tdp(0), existTDP(true),
	rot_fairlead(PI / 2.0), extrem_tensions({0.,0.})
{
	//Reserving positions for vectors
	lines.reserve(32);
	vessels.reserve(16);
	keypoints.reserve(64);
	segment_properties.reserve(16);
}

MooringModel::~MooringModel()
{}

bool MooringModel::GenerateGiraffeModel()
{
	//Computes segment properties from readed data
	PreCalcSegmentPropertiesData();

	//Mooring model -> Giraffe model
	CopyData();

	//Catenary equation -> prescribed displacements and TDZ (if exists)
	if (!GenerateCatenary())
		return false;
	
	//Check the necessity to couple rotation of beam segments between chain segments
	CheckDummyElements();
		
	//Dynamic relaxation parameters
	if (moorsolution.ExistDynRelax_Lines())
		GenerateDynamicRelaxation();

	/*Check if exist at least one shared line 
		important to create same displacemt with the correspondent vessels*/
	existSharedLine = Look4SharedLine();

	//Vessel(s)
	GenerateVessels();
	
	//Rigid nodeset to couple fairleads and vessel
	GenerateRigidNodeSets();

	//Set model and generate steps (with pescribed displacements and/or loads)
	GeneralSetting();

	//SeabedSetRhoFluid
	GenerateSeabed();

	//Nodal constraints 
	GenerateConstraints();
		

	std::sort(gm.node_set_vector.begin(), gm.node_set_vector.end());

	return true;
}

//Computes data from entered Segment Properties
void MooringModel::PreCalcSegmentPropertiesData()
{
	//Percorrendo properties
	for (SegmentProperty& seg : segment_properties)
	{
		//Se for do tipo polimérico é necessário calcular propriedades mecânicas equivalentes
		if (seg.IsBeam() && seg.GetYoungMod() != 0)
		{
			if (seg.GetSG() != 1.0 && seg.GetYoungMod() > 0.0)
				seg.SetDiameter(sqrt(4 * seg.GetMass() / (PI * seg.GetSG() * environment.GetRhoFluid())));

			double d = seg.GetDiameter();
			double E = seg.GetYoungMod();
			double nu = seg.GetPoisson();
			double G = E / (2 * (1 + nu));		//shear modulus
			double A = PI * pow(d, 2.0) / 4.0;	//area
			double J = PI * pow(d, 4.0) / 32.0;	//polar moment
			double I = PI * pow(d, 4.0) / 64.0;	//inertia moment

			//Setting values
			seg.SetEA(E * A);
			seg.SetEI(E * I);
			seg.SetGA(G * A);
			seg.SetGJ(G * J);
		}
		if (seg.IsTruss() && seg.GetSG() != 1 && seg.GetYoungMod() > 0.0)
			seg.SetDiameter(sqrt(4 * seg.GetMass() / (PI * seg.GetSG() * environment.GetRhoFluid() )));

		if (!seg.GetContactDiameter()) 
			seg.SetContactDiameter(seg.GetDiameter());
	}
}

//Copies data from MooringModel to GiraffeModel database
void MooringModel::CopyData()
{	
	/*	Segment properties -> PipeSection	*/
	for (SegmentProperty& sp : segment_properties)
		gm.pipe_section_vector.emplace_back(PipeSection(sp.GetNumber(), sp.IsBeam(), sp.GetDiameter(), sp.GetMass(), 
														sp.GetEA(), sp.GetEI(), sp.GetGJ(), sp.GetGA(),
														sp.GetCDt(), sp.GetCDn(), sp.GetCAt(), sp.GetCAn(),
														sp.GetYoungMod(), sp.GetPoisson()));

	/*	MoorEnvironment -> Environment	*/

	//Gravity
	gm.environment.SetGravity(environment.GetGravity());
	
	gm.environment.SetGravityBooltable(BoolTable{ true });

	gm.environment.SetRhoFluid (environment.GetRhoFluid());
	gm.environment.SetSeaCurrentVec(environment.GetSeaCurrentVec());
	gm.environment.SetWaterDepth(environment.GetWaterDepth());

	//CADs data to post processing 
	gm.post.SetAllCADs(std::move(moorpost.GetAllVesselCADs()));
}


//Generates prescribed displacement fields (extensible catenary)
bool MooringModel::GenerateCatenary()
{
	/*======================*
	 * Generating global CS *
	 *======================*/
	gm.GenerateCoordinateSystem(1, { 1.,0.,0. }, { 0.,0.,1. });


	/*===============*
	 * Iterate lines *
	 *===============*/

	unsigned int cur_node = 0;// , cur_disp = 0;

	for (Line& line : lines)
	{
		/*======================*
		 * Initialize variables *
		 *======================*/

		//Line ID
		cur_line = line.GetNumber() - 1;

		//Points to represent the anchor and/or fairlead
		Matrix coordinates_A(3), coordinates_B(3);

		//Line projections on seabed
		double Hf, Vf;

		//Original position of the fairlead used to calculate stiffness matrix
		Matrix Fair_stiff_matrix(3);

		//Forces at the top
		Matrix F(2);


		tot_elem = 0;

		/*===========*
		 * Functions *
		 *===========*/

		//Setting general parameters 
		Catenary_GeneralSetting(line, coordinates_A, coordinates_B, Fair_stiff_matrix);

		//Vertical forces at the end of each segment
		std::vector<double> FV(line.GetNSegments() + 1);

		if(!SolveCatenaryEquations(line, coordinates_A, coordinates_B, Hf, Vf, F, FV, Fair_stiff_matrix))
			return false;

		SetLinesConfiguration(line, F, FV);

		CheckSegmentsSize(line);

		auto n_segs = line.GetNSegments();
		
		//Displacement field data (coordinates, segments)
		std::vector<std::vector<double>> xcat_n, zcat_n, roty_n;
		xcat_n.resize(n_segs), zcat_n.resize(n_segs), roty_n.resize(n_segs);

		//vector of vectors with meshes for the line segments
		x0_n.resize(n_segs);

		//Reserving memory for data of each segment
		for (unsigned int seg = 0; seg < line.GetNSegments(); ++seg )
		{
			unsigned int n_nodes = line.GetSegment(seg).GetNNodes();
			x0_n[seg].resize(n_nodes);
			xcat_n[seg].resize(n_nodes);
			zcat_n[seg].resize(n_nodes);
			roty_n[seg].resize(n_nodes);
		}
		//Setting mesh parameters (creates matrix with nodes position)
		SetMeshProperties(line);

		//Call GenerateMesh to generate the current line mesh
		GenerateMesh(line, coordinates_A, coordinates_B, Hf, Vf);

		//Set penetration for the line
		if ( existTDP && line.HasAnchor() )
			ImposePenetration(line);

		//Generates displacement field (and updates fairlead rotation)
		GenerateCatenaryDisplacement(line, F, FV, cur_node, xcat_n, zcat_n, roty_n);
	}


	return true;
}

/*Catenary functions
	  -> 'GenerateCatenary' calls other functions*/
void MooringModel::Catenary_GeneralSetting(Line& line, Matrix& A, Matrix& B, Matrix& Fairleads_StiffnessMatrix)
{
	//Calculating gamma_s for all segments (and the maximum), total length and equivalent parameters
	line.SetTotalLength(0.0);

	for (LineSegment& seg : line.GetAllSegments())
	{
		line.AddLength(seg.GetLength());
		seg.SetGamma(environment.GetGravity() * segment_properties[seg.GetProperty() - 1].GetMass()
			- environment.GetGravity() * environment.GetRhoFluid() * PI * pow(segment_properties[seg.GetProperty() - 1].GetDiameter(), 2) / 4.0);
	}

	//Anchor and fairlead nodes ID
	unsigned int point_A = line.GetKeypointA();
	unsigned int point_B = line.GetKeypointB();

	//Setting points of the anchor and fairlead(s)
	A(0, 0) = keypoints[point_A - 1].GetCoordinate('x');
	A(1, 0) = keypoints[point_A - 1].GetCoordinate('y');
	A(2, 0) = keypoints[point_A - 1].GetCoordinate('z');
	B(0, 0) = keypoints[point_B - 1].GetCoordinate('x');
	B(1, 0) = keypoints[point_B - 1].GetCoordinate('y');
	B(2, 0) = keypoints[point_B - 1].GetCoordinate('z');

	//Calculating original position of the fairlead to calculate analytical stiffness matrix
	Fairleads_StiffnessMatrix(0, 0) = keypoints[point_B - 1].GetCoordinate('x');
	Fairleads_StiffnessMatrix(1, 0) = keypoints[point_B - 1].GetCoordinate('y');
	Fairleads_StiffnessMatrix(2, 0) = keypoints[point_B - 1].GetCoordinate('z');
}

bool MooringModel::SolveCatenaryEquations(Line& line, Matrix& A, Matrix& B,
										  double& Hf, double& Vf, Matrix& F, std::vector <double>& FV,
										  Matrix& Fairleads_StiffnessMatrix)
{
	// Limits to the counters (force initial guess) and error
	static constexpr int MAX_ITERATIONS_FH0 = 100;
	static constexpr int MAX_ITERATIONS_FV0 = 1000;
	static constexpr int MAX_ITERATIONS_NEWTON = 100;
	static constexpr double error_max = 1e-6;

	// Residue
	double res;

	// Jacobian matrix
	Matrix J(2, 2);

	// Contribution to stiffness matrix for the current line
	static Matrix Ki(2, 2);
	// Counters
	int aux0, aux1, aux2, aux3;

	// Supposes that there is no TDP
	existTDP = false;

	// Evaluate the order of the force initial guess
	double gamma_min = 1'000'000.0, gamma_max = -1'000'000.0;
	for (const LineSegment& seg : line.GetAllSegments())
	{
		if (seg.GetGamma() < gamma_min)	gamma_min = seg.GetGamma();
		if (seg.GetGamma() > gamma_max)	gamma_max = seg.GetGamma();
	}
	int m = static_cast<int>( ceil(log10(max(fabs(gamma_min), gamma_max))) );
	//m = 3;

#ifdef MAP_SOLUTION_ITERATIONS
	std::cout << "gamma_min = " << gamma_min << "\tgamma_max = " << gamma_max << "\n\n";
	std::cout << "m = " << m << "\n\n";
	unsigned int it = 0;
#endif

	//Two times => before and after penetration
	for (aux0 = 1; aux0 <= 2; aux0++)
	{

		//Anchor and fairlead horizontal projections
		if (aux0 == 1) Hf = sqrt(pow(( A(0, 0) - B(0, 0) ), 2) + pow(( A(1, 0) - B(1, 0) ), 2));
		Vf = B(2, 0) - A(2, 0);
		//if (aux0 == 1)	Vf = B(2, 0) - A(2, 0);

		//Updates FH initial guess 
		for (aux1 = 1; aux1 <= MAX_ITERATIONS_FH0; aux1++)
		{
			//Updates Force initial guess 
			for (aux2 = 1; aux2 <= MAX_ITERATIONS_FV0; aux2++)
			{
				if (aux0 == 2 && aux1 == 1 && aux2 == 1)
					/*Use the last calculated values - before penetration*/;
				else
				{
					F(0, 0) = aux1 * pow(10.0, m);
					F(1, 0) = aux2 * pow(10.0, m);
				}

				for (aux3 = 0; aux3 < MAX_ITERATIONS_NEWTON; aux3++)
				{
					//Calculating FV for each segment
					FV[line.GetNSegments()] = F(1, 0);
					double dif = 0.0;
					unsigned int cont_ds = line.GetNSegments() - 1;
					for (auto k_it = line.GetAllSegments().crbegin(); 
						k_it != line.GetAllSegments().crend(); 
						++k_it, --cont_ds)
					{
						dif -= k_it->GetLength() * k_it->GetGamma();
						FV[cont_ds] = FV[line.GetNSegments()] + dif;
					}

					if (line.HasAnchor() && A(2, 0) <= -environment.GetWaterDepth())
					{
						for (unsigned int cont = 0; cont < line.GetNSegments() + 1; cont++)
						{
							if (FV[cont] < 0)	FV[cont] = 0.0;
							else break;	//Break when it starts to be positive, the negative values are related to buoys only
						}
					}

					std::vector <double> raiz;
					for (unsigned int r = 0; r < line.GetNSegments() + 1; r++)
						raiz.push_back(sqrt(pow(F(0, 0), 2) + pow(FV[r], 2)));

					double h = 0.0, v = 0.0; //projections
					Matrix E(2); //equation system

					double FH0 = F(0, 0);
					double FV0 = F(1, 0);

					J.clear();
					for (unsigned int seg = 1; seg <= line.GetNSegments(); seg++)
					{
						double cur_gamma = line.GetSegment(seg - 1).GetGamma();
						double cur_EA = segment_properties[line.GetSegment(seg - 1).GetProperty() - 1].GetEA();
						double cur_len = line.GetSegment(seg - 1).GetLength();

						Matrix J_aux(2, 2);
						J_aux(0, 0) = cur_len / cur_EA + 1.0 / cur_gamma * ( log(( FV[seg] + raiz[seg] ) / FH0) - log(( FV[seg - 1] + raiz[seg - 1] ) / FH0) ) - 1.0 / cur_gamma * ( FV[seg] / raiz[seg] - FV[seg - 1] / raiz[seg - 1] );
						J_aux(0, 1) = FH0 / cur_gamma * ( 1.0 / raiz[seg] - 1.0 / raiz[seg - 1] );
						J_aux(1, 0) = J_aux(0, 1);
						J_aux(1, 1) = 1.0 / cur_gamma * ( FV[seg] / raiz[seg] - FV[seg - 1] / raiz[seg - 1] ) + 1.0 / ( cur_EA * cur_gamma ) * ( FV[seg] - FV[seg - 1] );

						J = J + J_aux;

						h += cur_len * ( 1 + FH0 / cur_EA ) - ( FV[seg] - FV[seg - 1] ) / cur_gamma + FH0 / cur_gamma * ( log(( FV[seg] + raiz[seg] ) / FH0) - log(( FV[seg - 1] + raiz[seg - 1] ) / FH0) );
						v += 1.0 / cur_gamma * ( raiz[seg] - raiz[seg - 1] ) + 0.5 * ( pow(FV[seg], 2) - pow(FV[seg - 1], 2) ) / ( cur_gamma * cur_EA );
					}
					E(0, 0) = h - Hf;
					E(1, 0) = v - Vf;

					F = F - (invert2x2(J) * E);

					if (F(0, 0) < 0.0 ) F(0, 0) = abs(F(0, 0));
					if (F(1, 0) < 0.0 ) F(1, 0) = abs(F(1, 0));

					res = sqrt(pow(E(0, 0), 2) + pow(E(1, 0), 2));

#ifdef MAP_SOLUTION_ITERATIONS
					std::cout << "----------------------------------------\n";
					std::cout << "Line number : " << line.GetNumber() << "\n"
							  << "iteration: " << ++it << "\n"
							  << "res: " << res << "\n";
					std::cout << "F\n"; F.print();
					std::cout << "E\n"; E.print();
					std::cout << "J\n"; J.print();
					std::cout << "h = " << h << "\t v = " << v << "\n";
#endif

					if (res < error_max) break;
				}
				if (res < error_max) break;
			}
			if (res < error_max) break;
		}
		
		//Stiffness matrix
		Ki = invert2x2(J);

		//Checks for divergence (maximum number of iterations)
		if (aux1 == MAX_ITERATIONS_FH0 && aux2 == MAX_ITERATIONS_FV0)
		{
			Log::SetWarning(Log::Warning::SOLVING_CATENARY, "ERROR", (int)line.GetNumber());
			Log::SetError(Log::Error::FEM_GENERATION);

			return false;
		}
		
		//Before apply penetration in seabed
		if (aux0 == 1)
		{
			//Tension at first and last nodes -> used in summary file
			extrem_tensions = { sqrt(pow(F(0,0),2) + pow(FV[0],2)), sqrt(pow(F(0,0),2) + pow(F(1,0),2)) };

			//If FV0 <= 0  and  Anchor point <= Water depth -> exist TDP
			if (FV[0] <= 0 && A(2, 0) <= -environment.GetWaterDepth())
			{
				existTDP = true;
				for (unsigned int cont = 1; cont < line.GetNSegments() + 1; ++cont)
				{
					if (FV[cont] > 0)
					{
						line.SetTDPSegment(--cont);
						break;
					}
				}
			}
			//Otherwise, set segment to the first
			else
				line.SetTDPSegment(0);

			//Recalculate the vertical point using the penetration of the first segment
			if (line.HasAnchor())
			{
				//Evaluate the penetration of the first segment
				SegmentProperty* prop_ptr = &segment_properties[line.GetSegment(0).GetProperty() - 1];

				//Reset the vertical point
				B(2, 0) = keypoints[line.GetKeypointB() - 1].GetCoordinate('z') +
					(prop_ptr->GetMass() * environment.GetGravity()) / (environment.GetSeabed().GetStiffness() * prop_ptr->GetContactDiameter());
			}
			else  break;
		}
	}

	//Line contribution to the stiffness matrix
	if (stiff_matrix && stiff_matrix->ExistAnalyticalStiffMat())
	{
		std::vector<double> eul_ang = { 0, 0, 0 };

		double alpha = atan2(( A(1, 0) - B(1, 0) ), ( A(0, 0) - B(0, 0) ));
		stiff_matrix->calc_Kaux(Fairleads_StiffnessMatrix, eul_ang, Hf, Vf, alpha, F, Ki);
	}

	return true;
}


void MooringModel::ImposePenetration(Line& line)
{
	//The penetration is calculated with data of the segments that have contact with seabed in the 
	// static configuration or the first segment (in cases like a steep wave line)
	unsigned int lim_seg = existTDP ? line.GetTDPSegment() : 0;

	//Penetration of the first segment
	double dz0;

	//Until reaches TDP segment (if exists)
	for (unsigned int seg = 0; seg <= lim_seg; seg++ )
	{
		LineSegment* seg_ptr = &line.GetSegment(seg);
		SegmentProperty* prop_ptr = &segment_properties[seg_ptr->GetProperty() - 1];

		//Auxiliary variables
		double len = seg_ptr->GetLength();
		double disc = (double)seg_ptr->GetDiscretization();

		//Set contact parameters
		double k_lin = environment.GetSeabed().GetStiffness() * prop_ptr->GetContactDiameter();
		seg_ptr->SetEpsilon(k_lin * len / disc);

		//Set penetration
		penetrations.emplace_front(std::array{ 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 });
		penetrations.front().SetLine(std::array{ 1.0, 0.0, 0.0, -( prop_ptr->GetMass() * environment.GetGravity()) / ( k_lin ), 0.0, 0.0, 0.0 });
		//penetrations.back().SetLine(std::array{ 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 });
		gm.GenerateNodalDisplacement(++cur_disp, seg_ptr->GetNodeSet(), 1, &penetrations.front(), BoolTable(true, 1, false));
		
		//Save the penetration of the first segment
		if ( seg == 0 ) dz0 = penetrations.front().GetValue(1, 3);
	}

	//If exist other segments, calculate equivalent parameters (used to calculate dynamic relaxation, if exists)
	if ( lim_seg != line.GetNSegments() - 1 )
	{
		//If there is no TDP, starts at segment 0, otherwise; at the next segment after TDP
		unsigned int seg = existTDP ? lim_seg + 1 : 0;

		for ( ; seg < line.GetNSegments(); ++seg )
		{
			line.GetSegment(seg).SetEpsilon(line.GetSegment(0).GetEpsilon());
			gm.GenerateNodalDisplacement(++cur_disp, line.GetSegment(seg).GetNodeSet(), 1, &penetrations.front(), BoolTable(true, 1, false));
		}
	}
}

void MooringModel::SetLinesConfiguration(Line& line, Matrix& F, std::vector<double>& FV)
{
	//Looking for TDP
	if (!existTDP)//seg_tdp<0
	{
		x_tdp = 0;
		x_tdp_ext = 0;
	}
	else
	{
		const unsigned int seg_tdp = line.GetTDPSegment();
		//Calculating TDP and length in the segments before TDP segment 
		double sum_len_tdp = 0;
		for (unsigned int i = 0; i <= seg_tdp; i++)
			sum_len_tdp += line.GetSegment(i).GetLength();

		x_tdp = sum_len_tdp - FV[seg_tdp + 1] / line.GetSegment(seg_tdp).GetGamma();
		double leng_tdp = x_tdp - sum_len_tdp;

		//Determination of the TDP position after the extension
		double leng_ext = 0;
		for ( unsigned int seg = 0; seg <= seg_tdp; seg++ )
			leng_ext += line.GetSegment(seg).GetLength() * ( 1 + F(0, 0) / segment_properties[line.GetSegment(seg).GetProperty() - 1].GetEA() );

		x_tdp_ext = leng_ext + leng_tdp * ( 1 + F(0, 0) / segment_properties[line.GetSegment(seg_tdp).GetProperty() - 1].GetEA());
	}

	//Determination of the line configuration type
	for (const LineSegment& seg : line.GetAllSegments())
	{
		if (!existTDP)
		{
			if (keypoints[line.GetKeypointA() - 1].GetCoordinate('x') == keypoints[line.GetKeypointB() - 1].GetCoordinate('x') &&
				keypoints[line.GetKeypointA() - 1].GetCoordinate('y') == keypoints[line.GetKeypointB() - 1].GetCoordinate('y'))
				line.SetConfiguration("Vertical line");
			else
				line.SetConfiguration("Suspended above the seabed");
		}
		else if (seg.GetGamma() < 0 && line.GetConfiguration() != "Lazy wave" && line.GetConfiguration() != "Steep wave")
		{
			if (x_tdp > 0)	line.SetConfiguration("Lazy wave");
			else			line.SetConfiguration("Steep wave");
		}
		else if ( line.GetConfiguration() != "Lazy wave" && line.GetConfiguration() != "Steep wave" )
		{
			if ( x_tdp > 0 )	line.SetConfiguration("Catenary");
			else				line.SetConfiguration("Taut-Leg");
		}
		
	}
}

void MooringModel::CheckSegmentsSize(Line& line)
{
	for (LineSegment& cur_seg : line.GetAllSegments())
	{
		//Nodes of the segment
		unsigned int n = segment_properties[cur_seg.GetProperty() - 1].IsTruss() ? 1 : 2;
		unsigned int disc = cur_seg.GetDiscretization();
		cur_seg.SetNNodes(n * disc + 1);
		//Elements of the segment
		cur_seg.SetNElements(disc);
		
		//Whole line
		tot_elem += disc;
		line.SetTotalNumNodes(cur_seg.GetNNodes());
	}

	//Exclude transitions between segments
	line.IncrementTotNodes(1 - (unsigned int)lines[line.GetNumber() - 1].GetNSegments());
}


void MooringModel::SetMeshProperties(Line& line)
{
	double cur_len = 0.0;

	for (unsigned int seg = 0; seg < line.GetNSegments(); seg++)
	{
		unsigned int div = line.GetSegment(seg).GetDiscretization();
		double len = line.GetSegment(seg).GetLength();

		for (unsigned int i = 1; i <= div; i++)
		{
			if (seg > 0 && i == 1 && line.GetNSegments() > 1) //Copy last node to the first segment node
				x0_n[seg][0] = cur_len;

			if ( segment_properties[line.GetSegment(seg).GetProperty() - 1].IsTruss() )
				x0_n[seg][i] = cur_len + len * i / div;
			else
			{
				x0_n[seg][2 * i - 1] = cur_len + len * ( 2.0 * i - 1.0 ) / ( 2.0 * div );
				x0_n[seg][2 * i] = cur_len + len * ( 2.0 * i ) / ( 2.0 * div );
			}
		}
		cur_len += len;
	}

}

//Generates mesh for the current line
void MooringModel::GenerateMesh(Line& line, Matrix& A, Matrix& F, double& Hf, double& Vf)
{
	//Temporary data to create summary of the current line
	std::array<unsigned int, 2> summ_elem = { 0,0 }, summ_nodesets = { 0,0 };

	//total nodes of the current line (it may start negative to disregards nodes between segments)
	unsigned int nodes_line = 1 - line.GetNSegments(); //here migth happens overflow. It works, but maybe I should avoid overflow and someday I will...
	unsigned int init_line = 0; //first node of the current line
	
	static Matrix E3(3);
	static Matrix E1(3);

	//Creating points to represent the anchor (A) and the fairlead (F)
	F(2, 0) = line.HasAnchor() ?
		keypoints[line.GetKeypointA() - 1].GetCoordinate('z') 
		: keypoints[line.GetKeypointB() - 1].GetCoordinate('z');

	//Generating local coordinate system - for each line a single CS is established
	E1.clear();	E3.clear();
	E1(0, 0) = 0.0;
	E1(1, 0) = 0.0;
	E1(2, 0) = 1.0;
	if ( Hf > 0.0 )
		E3 = 1.0 / norm(F - A) * ( F - A );
	//If is vertical -> global coordinate system
	else 
	{
		E3(0, 0) = 1.0;
		E3(1, 0) = 0.0;
		E3(2, 0) = 0.0;
	}
	line.SetCoordinateSystem(cur_cs);
	gm.GenerateCoordinateSystem(cur_cs, E1, E3);


	//Nodesets of the first node
	line.SetNodesetA(cur_node_set++);

	//Iterates through the segments
	for (unsigned int seg = 0; seg < line.GetNSegments(); seg++)
	{
		LineSegment* seg_ptr = &line.GetSegment(seg);

		//Comment (nodes and nodeset)
		std::stringstream comment;

		//Check if is used beam or truss in the segment
		bool isBeam = segment_properties[seg_ptr->GetProperty() - 1].IsBeam();
		unsigned int n = isBeam ? 2 : 1;

		//Generate nodeset for the current segment
		seg_ptr->SetNodeSet(cur_node_set);
		
		//Defines number of nodes for beam/truss elements
		unsigned int n_elem = seg_ptr->GetNElements() * n;
		unsigned int addFirstNode = seg == 0 ? 1 : 0; //If is the first segment, the anchor node must be included
		
		gm.GenerateNodeSet(cur_node_set++, n_elem + addFirstNode, (unsigned int)cur_node_mesh, 1, 
			std::string("Nodes of the segment ") + std::to_string(seg + 1) + " of the line " + std::to_string(line.GetNumber())
		);
		
		//Count number of nodes to generate line node set
		nodes_line += seg_ptr->GetNNodes();

		unsigned int node_x0 = 0;

		//Same rotation (if there is a segment of beam elements between segments of truss elements)
		if ( seg > 0 && line.GetNSegments() >= 2 &&
			segment_properties[line.GetSegment(seg - 1).GetProperty() - 1].IsTruss() &&
			segment_properties[line.GetSegment(seg).GetProperty() - 1].IsBeam() )
			line.AddTransitionNode((unsigned int)cur_node_mesh - 1);

		//Generate nodes, nodesets and elements
		for (unsigned int cur_elem_seg = 1; cur_elem_seg <= seg_ptr->GetNElements(); cur_elem_seg++)
		{
			bool bool_gen_node_comment = false;
			bool bool_first_element = false;

			//Anchor (or first fairlead, in case of a line without an anchor)
			if (cur_elem_seg == 1) 
			{
				bool_first_element = true;
				if (seg == 0)
				{
					//With an anchor
					if (line.HasAnchor())
					{
						comment << "Anchor of line " << line.GetNumber();

						//Booelan to indicate if the anchor nodeset was found 
						bool nodeset_found = false;

						//Checks if there is different constraint for this anchor
						for (MoorConstraint& constraint : anchor_constraints)
						{
							if (line.GetNumber() == constraint.GetNumber())
							{
								constraint.SetNodeset(line.GetNodesetA());
								nodeset_found = true;
								break;
							}
						}
						
						if (!nodeset_found)
							anchor_nodesets_id.push_front(line.GetNodesetA());
						
						//Monitors
						if (gm.monitor.MonitorAnchorNodes())	gm.monitor.PushNodeID(cur_node_mesh);
						if (gm.monitor.MonitorAnchorElements())	gm.monitor.PushElementID(cur_elem);
					}
					//Two fairleads
					else
					{
						comment << "Initial point of line " << line.GetNumber();
						fairlead_nodesets_id.push_front(line.GetNodesetA());

						//Monitors
						if (gm.monitor.MonitorFairleadNodes())		gm.monitor.PushNodeID(cur_node_mesh);
						if (gm.monitor.MonitorFairledElements())		gm.monitor.PushElementID(cur_elem);
					}	

					//Node and nodeset of the first node (anchor or first fairlead)
					gm.GenerateNode(cur_node_mesh, A, comment.str());
					line.SetNodeA(cur_node_mesh);
					gm.GenerateNodeSet(line.GetNodesetA(), (unsigned int)cur_node_mesh, comment.str());

					//Summary list
					summ_elem[0] = cur_elem;
					summ_nodesets[0] = line.GetNodesetA();

					init_line = cur_node_mesh++;
					++node_x0;
				}
				else //equal the last node of the last segment
					++node_x0;
			}
			//Last node (fairlead)
			if (seg == ( line.GetNSegments() - 1 ) && cur_elem_seg == seg_ptr->GetNElements())
			{
				bool_gen_node_comment = true;

				//With an anchor
				if (line.HasAnchor())
					comment << "Fairlead of line " << line.GetNumber();
				else //Second fairlead
					comment << "End point of line " << line.GetNumber();
				
				//Node and nodeset of fairlead
				line.SetNodeB(cur_node_mesh + n - 1);
				last_contact_node_id = cur_node_mesh + n - 1;
				gm.GenerateNodeSet(cur_node_set, last_contact_node_id, comment.str());
				fairlead_nodesets_id.push_front(cur_node_set);
				++cur_node_set;

				//Monitors
				if (gm.monitor.MonitorFairleadNodes())		gm.monitor.PushNodeID(cur_node_mesh + n - 1);
				if (gm.monitor.MonitorFairledElements())	gm.monitor.PushElementID(cur_elem);

				//Summary list
				summ_elem[1] = cur_elem;
				summ_nodesets[1] = cur_node_set - 1;
			}

			//Generate other(s) element node(s) and update node lists
			if (!isBeam)
			{
				if (bool_gen_node_comment)	gm.GenerateNode(cur_node_mesh, A + E3 * x0_n[seg][node_x0], comment.str());
				else						gm.GenerateNode(cur_node_mesh, A + E3 * x0_n[seg][node_x0]);
				
				++cur_node_mesh;
				++node_x0;
			}
			else 
			{
				for (int cont = 1; cont <= 2; cont++)
				{
					if (bool_gen_node_comment && cont == 2)	gm.GenerateNode(cur_node_mesh, A + E3 * x0_n[seg][node_x0], comment.str());
					else									gm.GenerateNode(cur_node_mesh, A + E3 * x0_n[seg][node_x0]);
					++cur_node_mesh;
					++node_x0;
				}
			}
			comment.str("");  //reset stringstream

			//Generate elements
			if (!isBeam)	gm.GenerateTrussElement(cur_elem, bool_first_element, seg_ptr->GetProperty(), (unsigned int)cur_node_mesh - 2, (unsigned int)cur_node_mesh - 1);
			else			gm.GeneratePipeElement(cur_elem, bool_first_element, seg_ptr->GetProperty(), cur_cs, (unsigned int)cur_node_mesh - 3, (unsigned int)cur_node_mesh - 2, (unsigned int)cur_node_mesh - 1);
			++cur_elem;
		}	
	}

	//Nodesets of the last nodes
	line.SetNodesetB(cur_node_set - 1);

	//Summary file
	Summary::AddLine({ line.GetNodeA(), line.GetNodeB() }, summ_elem, summ_nodesets, extrem_tensions,
					 (unsigned int)line.GetNumber(), line.GetConfiguration(), existTDP, x_tdp_ext, line.GetTotalLength(), ( unsigned int )line.GetNSegments());

	//Mooring line NodeSet
	gm.GenerateNodeSet(cur_node_set++, nodes_line, (unsigned int)init_line, 1, std::string{"Nodes of line "} + std::to_string(line.GetNumber()));
	++cur_cs;
}

void MooringModel::GenerateCatenaryDisplacement(Line& line, Matrix& F, std::vector <double>& FV, unsigned int& cur_node, 
												std::vector<std::vector<double>>& xcat_n, std::vector<std::vector<double>>& zcat_n, std::vector<std::vector<double>>& roty_n)
{
	double sum_len = 0.0;
	for (unsigned int seg = 0; seg < line.GetNSegments(); seg++)
	{
		double EA_n = segment_properties[line.GetSegment(seg).GetProperty() - 1].GetEA();

		for (unsigned int node = 0; node < line.GetSegment(seg).GetNNodes(); node++)
		{
			if (seg > 0 && node == 0)
				sum_len += line.GetSegment(seg - 1).GetLength();

			double prev_xcat = 0.0, prev_zcat = 0.0;
			if (seg > 0)
			{
				prev_xcat = xcat_n[seg - 1][line.GetSegment(seg - 1).GetNNodes() - 1];
				prev_zcat = zcat_n[seg - 1][line.GetSegment(seg - 1).GetNNodes() - 1];
			}

			double s = x0_n[seg][node];
			double s_ext = prev_xcat + ( s - sum_len ) * ( 1.0 + F(0, 0) / EA_n );
			double FV_s = 0.0;

			if (s_ext > x_tdp_ext)
			{
				FV_s = ( seg == line.GetTDPSegment() ) ?
					FV[seg] + line.GetSegment(seg).GetGamma() * ( s - x_tdp ) : 
					FV[seg] + line.GetSegment(seg).GetGamma() * ( s - sum_len );
			}

			if (node == 0 && seg == 0)
			{
				xcat_n[seg][node] = zcat_n[seg][node] = 0.0;
				roty_n[seg][node] = -atan(FV[seg] / F(0, 0));
			}
			else
			{
				xcat_n[seg][node] = prev_xcat + ( s - sum_len ) * ( 1.0 + F(0, 0) / EA_n ) - ( FV_s - FV[seg] ) / line.GetSegment(seg).GetGamma()
					+ F(0, 0) / line.GetSegment(seg).GetGamma() * ( log(( FV_s + sqrt(pow(FV_s, 2) + pow(F(0, 0), 2)) ) / F(0, 0))
						- log(( FV[seg] + sqrt(pow(FV[seg], 2) + pow(F(0, 0), 2)) ) / F(0, 0)) );
				zcat_n[seg][node] = prev_zcat + 1.0 / line.GetSegment(seg).GetGamma() * ( sqrt(pow(FV_s, 2) + pow(F(0, 0), 2))
					- sqrt(pow(FV[seg], 2) + pow(F(0, 0), 2)) ) + 1.0 / ( 2.0 * line.GetSegment(seg).GetGamma() * EA_n ) * ( pow(FV_s, 2) - pow(FV[seg], 2) );
				roty_n[seg][node] = -atan(FV_s / F(0, 0));

				std::cout << std::setprecision(10) << sqrt(pow(FV_s, 2) + pow(F(0, 0), 2)) << "\n";
			}
		}
	}

	gm.GenerateDisplacementField(++cur_disp, line.GetCoordinateSystem(), 2); 

	//Inserts current displacement field in the displacement vector
	for (unsigned int seg = 0; seg < (unsigned int)x0_n.size(); ++seg)
	{
		unsigned int node_init = ( seg > 0 ) ? 1 : 0;
		for (unsigned int node = node_init; node < line.GetSegment(seg).GetNNodes(); ++node)
		{
			std::array<double, 6> disp = { zcat_n[seg][node], 0.0, xcat_n[seg][node] - x0_n[seg][node],
				0.0, -roty_n[seg][node], 0.0 };
			static_cast<DisplacementField*>(gm.displacement_vector[cur_disp - 1].get())->InsertDisplacement(++cur_node, disp);
		}
	}

	//Updates the fairlead rotation
	unsigned int seg_rot = (unsigned int)x0_n.size() - 1;
	unsigned int node_rot = line.GetSegment(seg_rot).GetNNodes() - 1;
	if (roty_n[seg_rot][node_rot] < rot_fairlead)
		rot_fairlead = -roty_n[seg_rot][node_rot];
}

void MooringModel::CheckDummyElements()
{
	//BoolTable
	BoolTable constraint_booltable(true);

	//Check if dummy elements are required and create them
	unsigned int dummy_element = 1;	//count dummy elements
	Matrix dummy_nodes(3, 1);	//matrix to generate nodes  
	double dummy_z = environment.GetWaterDepth(); //depth -> dummy elements are generated under the seabead
	
	for (Line& line : lines)
	{
		if (line.GetNSegments() > 1)
		{
			unsigned int seg_size_init = (unsigned int)segment_properties.size(); //properties before create dummy elements properties
			for (unsigned int seg = 1; seg < line.GetNSegments(); ++seg)
			{
				if ( segment_properties[line.GetSegment(seg - 1).GetProperty() - 1].IsTruss() &&
					segment_properties[line.GetSegment(seg).GetProperty() - 1].IsBeam() && line.GetNSegments() >= 2 )
				{
					//Create dummy element properties
					if ((unsigned int)segment_properties.size() == seg_size_init)
						gm.pipe_section_vector.emplace_back(PipeSection((seg_size_init + 1), true, 1., 0., 1., 100., 1., 1., 0., 0., 0., 0., 1., 0.5));
					
					//Create dummy element nodes
					for (int i : { 1, 2, 3 })
					{
						dummy_nodes(0, 0) = 0;
						dummy_nodes(1, 0) = 0;
						dummy_nodes(2, 0) = dummy_z;
						--dummy_z;
						if (i == 1)
							gm.GenerateNode(cur_node_mesh, dummy_nodes, std::string{ "Dummy element " + dummy_element});
						else
							gm.GenerateNode(cur_node_mesh, dummy_nodes);
						++cur_node_mesh;
						dummy_nodes.clear();
					}
	
					//Create dummy element node set
					gm.GenerateNodeSet(cur_node_set, (unsigned int)cur_node_mesh - 3, std::string{ "Dummy element " + dummy_element });
					
					//Create dummy element under the seabed
					gm.GeneratePipeElement(cur_elem, false, (int)segment_properties.size(), 1, (unsigned int)cur_node_mesh - 1, (unsigned int)cur_node_mesh - 2, (unsigned int)cur_node_mesh - 3);
					++cur_elem;
					++dummy_element;
	
					//Create same rotation constraint
					gm.GenerateSameRotation(++cur_special_constraint, cur_node_mesh - 1, lines[cur_line].GetTransitionNode(dummy_element - 2), constraint_booltable);
					
					//Dummy element - fixed
					gm.GenerateNodalConstraint(++cur_constraint, cur_node_set++, 
						constraint_booltable, constraint_booltable, constraint_booltable, constraint_booltable, constraint_booltable, constraint_booltable);
				}
			}
		}
	}
}


void MooringModel::GenerateContacts()
{
	//After generate all line nodes, generate vessel and dummy elements elements, 
	 //must create a nodeset and the contact surface (lines-seabed)
	node_set_contact_id = cur_node_set++;
	gm.GenerateNodeSet(node_set_contact_id, last_contact_node_id, 1, 1, "Nodes to establish contact model");

	//Contact booltables
	BoolTable bool_c(true);
	
	unsigned int NSSS_ID = 0;
	for (Line& line : lines)
	{
		unsigned int segID = 0;
		for ( LineSegment& seg : line.GetAllSegments() )
			gm.GenerateNSSSContact(++NSSS_ID, seg.GetNodeSet(), 1, environment.GetSeabed().GetFrictionCoefficient(),
								   seg.GetEpsilon(), environment.GetSeabed().GetDamping(), seg.GetEpsilon() * 0.1, 0.0,
								   environment.GetSeabed().GetPinball(), 0, 1, std::move(bool_c), 
								   std::string("Segment number ") + std::to_string(++segID) + " of the line number " + std::to_string(line.GetNumber())
			);
	}
}


void MooringModel::GenerateDynamicRelaxation()
{
	auto dyn_relax = moorsolution.GetStepDynRelaxLines();

	for ( Line& line : lines )
	{
		//Equivalents paramenters to set (a possible) dynamic relaxation
		double rholen = 0.0, arealen = 0.0;

		//Until reaches TDP segment (if exists)
		for (LineSegment& seg : line.GetAllSegments())
		{
			SegmentProperty* prop_ptr = &segment_properties[seg.GetProperty() - 1];

			//Update equivalent properties
			arealen += ( PI * pow(prop_ptr->GetDiameter(), 2) / 4.0 ) * seg.GetLength();
			rholen += prop_ptr->GetMass() * seg.GetLength();
		}

		//Equivalents paramenters to set penetration
		rho_eq.push_back(rholen / line.GetTotalLength());
		area_eq.push_back(arealen / line.GetTotalLength());
	}


	//Dynamic relaxation parameters
	double L_s = 0.0, m_a = 0.0, m_m = 0.0;

	double delta = dyn_relax->GetDecrement();
	const double zeta = log(1.0 / delta) / (sqrt(4.0 * pow(PI, 2.0) + log(1.0 / delta)));

	//Data to calculates natural frequency and alpha
	for (size_t line = 0; line < lines.size(); line++)
	{
		double temp_ma = environment.GetRhoFluid() * area_eq[line];
		if (temp_ma > m_a)
		{
			m_a = temp_ma;
			m_m = rho_eq[line];
		}

		//Suspended length
		double temp_Ls = lines[line].GetTotalLength()- x_tdp;
		if (temp_Ls > L_s)	L_s = temp_Ls;
	}
	
	// Calculate parameters
	double fi = 72.9851 * exp(-449.293 * rot_fairlead)
		+ 27.4192 * exp(-67.2391 * rot_fairlead)
		+ 11.005 * exp(-9.97913 * rot_fairlead)
		+ 6.46725 * exp(-0.820751 * rot_fairlead);

	//double fi = 8.25 - 11.42 * rot_fairlead + 8.56 * pow(rot_fairlead, 2) - 2.53 * pow(rot_fairlead, 3);
	double w_n = fi * sqrt(( m_m - m_a ) / ( ( m_m + m_a ) ) * (environment.GetGravity() / L_s ));

	dyn_relax->SetAlphaRayleigh(zeta * 2.0 * w_n);
	dyn_relax->SetDuration(static_cast<unsigned int>(ceil(2.0 * PI / w_n)));

#ifdef MAP_SOLUTION_ITERATIONS
	std::cout << "\n ============================================= \n";
	std::cout << "\n - theta = " << rot_fairlead << " rad"
		<< "\n - m_m = " << m_m
		<< "\n - m_a = " << m_a
		<< "\n - L_s = " << L_s
		<< "\n - fi = " << fi
		<< "\n - freq = " << w_n << " rad/s"
		<< "\n - alpha = " << dyn_relax->GetAlpha_ray()
		<< "\n - zeta = " << zeta
		<< "\n - period = " << 2.0 * PI / w_n << " s\n";
	std::cout << "\n ============================================= \n";
#endif

}

bool MooringModel::Look4SharedLine()
{ 
	return (std::count_if(lines.begin(), lines.end(),
		[](const Line& line) { return line.IsShared(); }) > 0);
}

//Generates vessel (node, element, nodeset and fairleads coupling)
void MooringModel::GenerateVessels()
{
	
	for (Vessel& vessel : vessels)
	{
		unsigned int keypoint = vessel.GetKeypoint() - 1;
		unsigned int num = vessel.GetNumber();
		
		std::string comment = std::string("Vessel number ") + std::to_string(num);

		//Node
		gm.GenerateNode(cur_node_mesh, keypoints[keypoint].GetAllCoordinates(), comment);
		vessel.SetNode(cur_node_mesh);

		//Node Set (vessel)
		vessel.SetNodeset(cur_node_set);
		gm.GenerateNodeSet(vessel.GetNodeset(), (unsigned int)cur_node_mesh, comment);
		++cur_node_set;

		//Vessels 

		//Check CAD name for the current vessel
		auto it_cad = std::find_if(gm.post.GetAllCADs().begin(), gm.post.GetAllCADs().end(),
								  [&](CADData& cadData) { return cadData.GetNumber() == num; });
		it_cad._Ptr ?
			gm.GenerateRigidBodyData(++cur_rbdata, vessel.GetMass(), vessel.GetInertiaTensor(),
				keypoints[keypoint].GetAllCoordinates(), it_cad->GetNumber(),
				std::string{"Vessel of platform number " + std::to_string(num)})
			: 
			gm.GenerateRigidBodyData(++cur_rbdata, vessel.GetMass(), vessel.GetInertiaTensor(), 
				keypoints[keypoint].GetAllCoordinates());
		
		
		//Rigid body element
		vessel.SetElement(cur_elem);
		gm.GenerateRigidBodyElement(cur_elem++, cur_rbdata, 1, (unsigned int)cur_node_mesh++);

		//Coupling fairleads to vessel -> SameDisplacement (GIRAFFE special constraint)
		BoolTable constraint_booltable(false, 2, true);

		//Searchs for the first line with the current vessel
		auto it = std::find(lines.begin(), lines.end(), num);
		while (it != lines.end() && it->GetVesselAt(0) == num)
		{
			vessel.AddNode2RigidNodeset(cur_node_mesh);
			gm.GenerateNode(cur_node_mesh, keypoints[it->GetKeypointB() - 1].GetCoordinate('x'), 
							keypoints[it->GetKeypointB() - 1].GetCoordinate('y'), 
							keypoints[it->GetKeypointB() - 1].GetCoordinate('z'));
			gm.GenerateSameDisplacement(++cur_special_constraint, cur_node_mesh++, it->GetNodeB(), constraint_booltable);
			
			++it;
		}
		vessel.SetRigidNodeset(cur_node_set++);
		

		//Monitor Vessel
		if ( gm.monitor.MonitorVesselNodes() )
			gm.monitor.PushNodeID(vessel.GetNode());
		if ( gm.monitor.MonitorVesselElements() )
			gm.monitor.PushElementID(vessel.GetElement());
	}

}

void MooringModel::GenerateRigidNodeSets()
{
	BoolTable constraint_booltable(false, 2, true);

	/*If exist shared line(s), must check if the fairleads
		must be included to some rigid node set */
	if (existSharedLine)
		IncludeSharedLinesFaileads(constraint_booltable);

	//Generate rigid nodesets
	constraint_booltable.Clear();
	constraint_booltable.Push_Back(true);
	for (Vessel& vessel : vessels)
	{
		gm.GenerateNodeSet(vessel.GetRigidNodeset(), vessel.GetNodesRigidNodeset(), "Vessel Rigid Node Set");
		gm.GenerateRigidNodeSet(++cur_special_constraint, vessel.GetNode(), vessel.GetRigidNodeset(), constraint_booltable);
	}
	
}

void MooringModel::IncludeSharedLinesFaileads(BoolTable& bool_t)
{
	auto line_it = std::find(lines.begin(), lines.end(), 0);
	//Iterates through the shared lines
	while (line_it != lines.end() && line_it->IsShared())
	{
		//Check if the extremities nodes is already in some rigid nodeset
		for (Vessel& vessel : vessels)
		{
			auto& rigid_NS = vessel.GetNodesRigidNodeset();

			std::stringstream comment;

			//First node												**not found**
			if (std::find(rigid_NS.cbegin(), rigid_NS.cend(), line_it->GetNodeA()) == rigid_NS.cend())
			{
				//Check if must be included
				if (line_it->GetVesselAt(0) == vessel.GetNode())
				{
					rigid_NS.emplace(cur_node_mesh); //Include to vessel rigid nodeset

					comment << "Node to couple line " << line_it->GetNumber() << " and vessel " << vessel.GetNumber();

					gm.GenerateNode(cur_node_mesh, keypoints[line_it->GetKeypointA() - 1].GetAllCoordinates(), comment.str());
					gm.GenerateSameDisplacement(++cur_special_constraint, cur_node_mesh++, line_it->GetNodeA(), bool_t);

					//coupled_nodeA = true;
				}
			}

			//Second node												**not found**
			if (std::find(rigid_NS.cbegin(), rigid_NS.cend(), line_it->GetNodeB()) == rigid_NS.cend())
			{
				//Check if must be included
				if (line_it->GetVesselAt(1) == vessel.GetNumber())
				{
					rigid_NS.emplace(cur_node_mesh); //Include to vessel rigid nodeset

					comment << "Node to couple line " << line_it->GetNumber() << " and vessel " << vessel.GetNumber();

					gm.GenerateNode(cur_node_mesh, keypoints[line_it->GetKeypointB() - 1].GetAllCoordinates(), comment.str());
					gm.GenerateSameDisplacement(++cur_special_constraint, cur_node_mesh++, line_it->GetNodeB(), bool_t);

				}
			}
		} //end for (vessels)
		++line_it;
	} //end while (lines)
}

//Setting analysis general data
void MooringModel::GeneralSetting()
{
	/*============================*
	 * Post processing parameters *
	 *============================*/

	//If there is just one line, do not write rigid member coupling fairlead and vessel
	gm.post.SetFlags(std::move(moorpost.GetWritingFlags()));

	//Monitor nodes
	for (auto const& seq : *gm.monitor.GetNodesSequence())
	{
		unsigned int temp = seq.begin;
		for (unsigned int cont = 0; cont < seq.nodes; ++cont)
		{
			gm.monitor.PushNodeID(temp);
			temp += seq.increment;
		}
	}
	gm.monitor.GetNodeIDs().sort();
	gm.monitor.GetNodeIDs().unique();

	//Monitor elements
	for (auto const& seq : *gm.monitor.GetElementsSequence())
	{
		unsigned int temp = seq.begin;
		for (unsigned int cont = 0; cont < seq.elements; ++cont)
		{
			gm.monitor.PushElementID(temp);
			temp += seq.increment;
		}
	}
	gm.monitor.GetElementIDs().sort();
	gm.monitor.GetElementIDs().unique();

	//Monitor contact
	if (gm.monitor.MonitorLinesSeabedContact())	gm.monitor.PushContactID(1);


	/*================*
	 * Solution steps *
	 *================*/

	unsigned int step = 0;
	double start = 0;
	
	//Initial steps setting model parameters
	SettingModelSteps(step, start);

	//Analysis step(s)
	GenerateAnalysisSteps(step, start);
	
	//Generate vessel displacements
	if (!vessel_displacements.empty()) 
		GenerateVesselDisplacements();

	//Generate forces
	if (!moor_loads.empty())	
		GenerateForces();
	
	//Generate displacement fields (harmonic)
	if (!line_disp_fields.empty())	
		GenerateDisplacementFields();

}

void MooringModel::SettingModelSteps(unsigned int& step, double& start)
{
	//Enforcing penetration
	gm.GenerateStaticSolutionStep(++step, start, start + 1., 1., 1., 0.0001, 20, 2, 4, 1.5, 100);
	Summary::GetSteps().emplace_back(std::make_tuple(start, start + 1.0, "Enforcing penetration"));
	start += 1.0;

	//Applying prescribed displacements
	gm.GenerateStaticSolutionStep(++step, start, start + 1., 1., 1., 0.0001, 20, 2, 4, 1.5, 100);
	Summary::GetSteps().emplace_back(std::make_tuple(start, start + 1.0, "Applying prescribed displacement field"));
	start += 1.0;

	//Solution step to include sea current
	size_t steps_before_seacurrent = 3;

	//Coupling fairlead(s)
	if (moorsolution.ExistDynRelax_Lines())
	{
		++steps_before_seacurrent;

		//Dynamic relaxation
		auto relax = moorsolution.GetStepDynRelaxLines();
		double total_duration = (double)relax->GetDuration() * (double)relax->GetPeriods();
		gm.GenerateDynamicSolutionStep(++step, start, start + total_duration,
			relax->GetTimestep(), relax->GetMaxTimestep(), relax->GetMinTimestep(),
			15, 3, 4, 2, relax->GetSample(),
			relax->GetAlpha_ray(), relax->GetBeta_ray(), 0, relax->GetGamma_new(), relax->GetBeta_new(), true);
		Summary::GetSteps().emplace_back(std::make_tuple(start, start + total_duration, "Coupling fairleads during a dynamic relaxation"));
		start += total_duration;

		//Static step
		gm.GenerateStaticSolutionStep(++step, start, start + 1., 1., 1., 0.00001, 20, 2, 4, 1.5, 100);
		Summary::GetSteps().emplace_back(std::make_tuple(start, start + 1., "Static step after dynamic relaxation"));
		start += 1.;
	}
	else
	{
		//Static step
		gm.GenerateStaticSolutionStep(++step, start, start + 1., 1., 1., 0.00001, 20, 2, 4, 1.5, 100);
		Summary::GetSteps().emplace_back(std::make_tuple(start, start + 1., "Coupling fairleads statically"));
		start += 1.;
	}


	//Includes sea current
	if (environment.ExistSeaCurrent())
	{
		//BoolTable
		gm.environment.GetSeaCurrentBooltable().Multiple_Push_Back(false, steps_before_seacurrent);
		gm.environment.GetSeaCurrentBooltable().Push_Back(true);

		//Solution step
		std::shared_ptr<SolutionStep> seacurrent_step = moorsolution.ExistSeaCurrentStep() ? 
			// ... if exist a sea current step, just get a reference to the variable ...
			moorsolution.GetStepSeaCurrent() : 
			// ... otherwise, create the step with default options
			moorsolution.InitStepSeaCurrent();
		
		double total_step_time = seacurrent_step->GetEndTime();
		gm.GenerateStaticSolutionStep(++step, start, start + total_step_time,
			seacurrent_step->GetTimestep(), seacurrent_step->GetMaxTimestep(), seacurrent_step->GetMinTimestep(),
			20, 2, 3, 1.5, seacurrent_step->GetSample());
		Summary::GetSteps().emplace_back(std::make_tuple(start, start + total_step_time, "Establishing sea current"));
		start += total_step_time;
	}
	//Sea current bool table, just for Morison effects
	else
		gm.environment.GetSeaCurrentBooltable().Multiple_Push_Back(std::vector{ false, false, true });

	moorsolution.SetStepsBeforeAnalysis(step);
}

void MooringModel::GenerateAnalysisSteps(unsigned int& step, double& start)
{
	// Time increment (solution step total time)
	double dt = 0.0;

	for (SolutionStep& analysis_step : moorsolution.GetStepsVec())
	{
		// "global_start" might be used to apply vessel displacements and/or nodal loads
		analysis_step.SetGlobalStartTime(start);
		dt = analysis_step.GetEndTime();
		
		// Static step
		if (analysis_step.IsStatic())
		{
			gm.GenerateStaticSolutionStep(++step, start, start + dt,
										  analysis_step.GetTimestep(),
										  analysis_step.GetMaxTimestep(),
										  analysis_step.GetMinTimestep(), 20, 2, 4, 1.5,
										  analysis_step.GetSample());
			Summary::GetSteps().emplace_back(std::make_tuple(start, start + dt, "Static step"));
		}
		//Dynamic step
		else 
		{
			gm.GenerateDynamicSolutionStep(++step, start, start + dt,
										   analysis_step.GetTimestep(),
										   analysis_step.GetMaxTimestep(),
										   analysis_step.GetMinTimestep(), 15, 3, 2, 1.5,
										   analysis_step.GetSample(), 
										   analysis_step.GetAlpha_ray(),
										   analysis_step.GetBeta_ray(), 0,
										   analysis_step.GetGamma_new(),
										   analysis_step.GetBeta_new());
			Summary::GetSteps().emplace_back(std::make_tuple(start, start + dt, "Dynamic step"));
		}
		//Update initial time
		start += dt;
	}
}

void MooringModel::GenerateVesselDisplacements()
{
	for (VesselDisplacement& disp : vessel_displacements)
	{
		//Temporary auxiliary variables
		unsigned int ID = disp.GetVesselID() - 1;
		unsigned int analysis_step = disp.GetStep() - 1;
		unsigned int global_step = moorsolution.GetStepsBeforeAnalysis() + analysis_step;
		double start = moorsolution.GetStep(analysis_step).GetGlobalStart();

		//Displacement description (vessel number and type of displacement)
		std::string description2add;

		//MathCode
		if (disp.IsMathCode())
		{
			auto ptr = disp.GetMathCode();

			//Changes 't0' to real value in the equation(s)
			ptr->SetEquationInitialTime(start);

			//Displacement
			gm.GenerateNodalDisplacement(++cur_disp, vessels[ID].GetNodeset(), 1, ptr);
			description2add = "\n\t\t- Displacement of the vessel " + std::to_string(vessels[ID].GetNumber()) + " with MathCode";
		}
		//External file
		else if (disp.IsExternalFile())
		{
			//Displacement
			gm.GenerateNodalDisplacement(++cur_disp, vessels[ID].GetNodeset(), 1, disp.GetFileName(), disp.GetNHeaderLines(), disp.GetNSteps());
			description2add = "\n\t\t- Displacement of the vessel " + std::to_string(vessels[ID].GetNumber()) + 
				" with data from file \"" + disp.GetFileName() + "\"";
		}
		//Time series
		else if (disp.IsTable())
		{
			auto time_series = disp.GetTimeSeries();

			for (size_t i = 1; i < time_series->table.size(); i++)
				time_series->table[i][0] += start;

			//Generate displacement
			gm.GenerateNodalDisplacement(++cur_disp, vessels[ID].GetNodeset(), 1, time_series);
			description2add = "\n\t\t- Applying time series to vessel " + std::to_string(vessels[ID].GetNumber());
		}
		
		//Append description of the current step (after 'dynamic' or 'static' description)
		std::get<2>(Summary::GetSteps()[global_step]) += description2add;
	}
}

//Generate applied forces
void MooringModel::GenerateForces()
{
	for (MoorLoad& load : moor_loads)
	{
		//Temporary auxiliary variables
		unsigned int analysis_step = load.GetStep() - 1;
		unsigned int global_step = moorsolution.GetStepsBeforeAnalysis() + analysis_step;
		double start = moorsolution.GetStep(analysis_step).GetGlobalStart();
		unsigned int line = load.GetLineID() - 1;
		unsigned int node = load.GetNodeID() - 1;
		unsigned int segID = load.GetSegmentID();
		unsigned int nodeset;

		//Updates load number
		++cur_load;

		//Displacement description (vessel number and type of displacement)
		std::string description2add = "\n\t\t- Applying load at ";

		//Vessel node
		if (load.GetDescription() == "vessel")
		{
			nodeset = vessels[node].GetNodeset();
			description2add += "vessel " + std::to_string(vessels[node].GetNumber());
		}
		//First node of a line
		else if (load.GetDescription() == "first" && segID == 1)
		{
			nodeset = lines[line].GetNodesetA();
			description2add += "the first node of the line " + std::to_string(load.GetLineID());
		}
		//Last node of a line
		else if (load.GetDescription() == "last" && segID == lines[line].GetNSegments())
		{
			nodeset = lines[line].GetNodesetB();
			description2add += "the last node of the line " + std::to_string(load.GetLineID());
		}
		// If is not a vessel or fairlead node, a new nodeset must be created
		else
		{
			unsigned int temp_node = (unsigned int)lines[line].GetNodeA() - 1; //first node
			unsigned int add_nodes;

			for (unsigned int seg = 0; seg < segID; ++seg)
			{
				unsigned int nodes_seg = lines[line].GetSegment(seg).GetNNodes();
				if (segID == seg + 1)
				{
					if (load.GetDescription() == "first")
						add_nodes = 1;
					else if (load.GetDescription() == "last")
						add_nodes = nodes_seg;
					else if (load.GetDescription() == "middle")
						          //Is even ? calculation for an even number of nodes : calculation for an odd number of nodes;
						add_nodes = ( nodes_seg & 1 ) == 0 ? nodes_seg / 2 : ( unsigned int )floor(nodes_seg / 2) + 1;
					else
						add_nodes = (unsigned int)load.GetNodeID();
				}
				//Is not this segment yet
				else
					add_nodes = nodes_seg;

				temp_node += add_nodes; //Before exclude transition nodes (they may have been counted twice)
			}

			//Exclude nodes of transition between segments of the count
			temp_node -= lines[line].GetNSegments() - 1;

			//Node set
			nodeset = ++cur_node_set;
			gm.GenerateNodeSet(nodeset, temp_node, std::string{ "Nodeset to apply the nodal force number " + cur_load });
		}

		//Matching start time with Giraffe time
		if (load.IsMathCode())
		{
			load.GetMathCode()->SetEquationInitialTime(start);
			gm.GenerateNodalForce(cur_load, nodeset, load.GetMathCode());
			description2add += " with MathCode";
		}
		else if (load.IsExternalFile())
		{
			gm.GenerateNodalForce(cur_load, nodeset, load.GetFileName(), load.GetNHeaderLines(), load.GetNSteps());
			description2add += " with data from file \"" + std::string(load.GetFileName()) + "\"";
		}
		else //Time series table
		{
			for (unsigned int i = 0; i < load.GetTimeSeries()->GetNLines(); i++)
				load.GetTimeSeries()->table[i][0] += start;

			gm.GenerateNodalForce(cur_load, nodeset, load.GetTimeSeries());
			description2add += " with time series data";
		}

		//Append description of the current step (after 'dynamic' or 'static' description)
		std::get<2>(Summary::GetSteps()[global_step]) += description2add;
	}
}

void MooringModel::GenerateDisplacementFields()
{
	for (LineDisplacementField& disp_field : line_disp_fields)
	{
		//Temporary auxiliary variables
		unsigned int analysis_step = disp_field.GetStep() - 1;
		unsigned int global_step = moorsolution.GetStepsBeforeAnalysis() + analysis_step;
		
		//Pointer to the current line
		Line* line = &lines[disp_field.GetNumber() - 1];
		
		//Displacement description (vessel number and type of displacement)
		std::string description2add = std::string("\n\t\t- Applying harmonic displacement field at the line number ") + std::to_string(line->GetNumber());

		//Generate harmonic displacement field for the current line
		gm.GenerateDisplacementField(++cur_disp, line->GetCoordinateSystem(), global_step + 1);// , (unsigned int)line->GetTotalNumNodes());

		unsigned int global_node = line->GetNodeA();
		for (unsigned int seg = 0; seg < line->GetNSegments(); ++seg)
		{
			unsigned int seg_first_node = seg == 0 ? 1 : 0;
			unsigned int seg_last_node = line->GetSegment(seg).GetNNodes() - 1;

			for (unsigned int node = seg_first_node; node < seg_last_node; ++node)
				//dynamic_cast< DisplacementField* >( gm.displacement_vector[cur_disp - 1] )->InsertDisplacement(
				static_cast<DisplacementField*>(gm.displacement_vector[cur_disp - 1].get())->InsertDisplacement(
					++global_node,
					std::array{ 0.0,
					-disp_field.GetAmplitude() * std::sin(x0_n[seg][node] * PI / line->GetTotalLength() * disp_field.GetMode()),
					0.0, 0.0, 0.0 , 0.0 });
		}
		
		//Append description of the current step (after 'dynamic' or 'static' description)
		std::get<2>(Summary::GetSteps()[global_step]) += description2add;	
	}
}

//Generates seabed (contact surface)
void MooringModel::GenerateSeabed()
{
	//min and max coordinates
	double xmin = 0.0, xmax = 0.0; //x -> lambda 1 of 'oscillatory surface'
	double ymin = 0.0, ymax = 0.0; //y -> lambda 2 of 'oscillatory surface'

	for (const Line& moor : lines)
	{
		//Keypoints ID
		unsigned int pointA = moor.GetKeypointA() - 1;
		unsigned int pointB = moor.GetKeypointB() - 1;

		//Check X (min e max)
		if (keypoints[pointA].GetCoordinate('x') < xmin)	xmin = keypoints[pointA].GetCoordinate('x');
		if (keypoints[pointB].GetCoordinate('x') < xmin)	xmin = keypoints[pointB].GetCoordinate('x');
		if (keypoints[pointA].GetCoordinate('x') > xmax)	xmax = keypoints[pointA].GetCoordinate('x');
		if (keypoints[pointB].GetCoordinate('x') > xmax)	xmax = keypoints[pointB].GetCoordinate('x');

		//Check Y (min e max)
		if (keypoints[pointA].GetCoordinate('y') < ymin)	ymin = keypoints[pointA].GetCoordinate('y');
		if (keypoints[pointB].GetCoordinate('y') < ymin)	ymin = keypoints[pointB].GetCoordinate('y');
		if (keypoints[pointA].GetCoordinate('y') > ymax)	ymax = keypoints[pointA].GetCoordinate('y');
		if (keypoints[pointB].GetCoordinate('y') > ymax)	ymax = keypoints[pointB].GetCoordinate('y');
	}

	//Check Vessel keypoint
	for (Vessel& vessel : vessels)
	{
		unsigned int keypoint = vessel.GetKeypoint() - 1;
		
		//Check X (min e max)
		if (keypoints[keypoint].GetCoordinate('x') < xmin)	xmin = keypoints[keypoint].GetCoordinate('x');
		if (keypoints[keypoint].GetCoordinate('x') > xmax)	xmax = keypoints[keypoint].GetCoordinate('x');

		//Check Y (min e max)
		if (keypoints[keypoint].GetCoordinate('y') < ymin)	ymin = keypoints[keypoint].GetCoordinate('y');
		if (keypoints[keypoint].GetCoordinate('y') > ymax)	ymax = keypoints[keypoint].GetCoordinate('y');
	}

	//Checks for null values and change they for half of water depth
	double depth = environment.GetWaterDepth();
	if (ymin == 0.0)	ymin = -depth / 2.0;
	if (ymax == 0.0)	ymax = depth / 2.0;
	if (xmin == 0.0)	xmin = -depth / 2.0;
	if (xmax == 0.0)	xmax = depth / 2.0;
	
	//Surface size (lambdas)
	///                5 * maximum (absolute) to ensure contact
	double l1 = ceil(5.0 * max(fabs(xmax), fabs(xmin)));
	double l2 = ceil(5.0 * max(fabs(ymax), fabs(ymin)));
	
	//Pinball (hypotenuse, considering extreme points of the surface)
	environment.GetSeabed().SetPinball(sqrt(pow(xmax - xmin, 2) + pow(ymax - ymin, 2)));

	environment.GetSeabed().SetRadius(0.0);

	//Pilot node (seabed)
	std::array<double, 3> pilot_p = { ( xmax + xmin ) / 2.0, ( ymax + ymin ) / 2.0, -depth };
	int pil = (int)gm.node_vector.size() + 1;
	gm.GenerateNode(pil, pilot_p, "Pilot Node (Seabed)");

	//Node Set (seabed)
	pil_node_set_id = cur_node_set++;
	gm.GenerateNodeSet(pil_node_set_id, pil, "Seabed");
	environment.GetSeabed().SetPilotNode(pil);

	//Establishing oscillatory surface
	gm.GenerateOscillatorySurf(1, 0.0, 0.0, 0.0, l1, l2, 0.0, 0.0, 1.0, 1.0, 1, pil);
	gm.GenerateSurfaceSet(1, {1});

	
	//Establishing contact
	GenerateContacts();
	
	//Folder with post files
	std::string surfaces_folder = IO::folder_name + "post/";
	bool VTKseabedOk = false, VTKwaterOk; //indicate if seabed/water surface VTK files were created

	//Creates post files directory and seabed and water surface vtk files
	if ( !std::filesystem::is_directory(surfaces_folder) &&	  ///check if exist
		!std::filesystem::create_directory(surfaces_folder) ) ///if not, try to create it
		Log::SetWarning("\n  GIRAFFE POST: Post files directory could not be created. Thus, no seabed/water VTK file created.");
	else
	{
		VTKseabedOk = gm.post.CreateSeabedVTK(surfaces_folder, { 2.0 * xmin, 2.0 * fabs(xmax) }, { 2.0 * ymin, 2.0 * fabs(ymax) }, -environment.GetWaterDepth());
		VTKwaterOk = gm.post.CreateWaterVTK(surfaces_folder, { 2.0 * xmin, 2.0 * fabs(xmax) }, { 2.0 * ymin, 2.0 * fabs(ymax) });
	}

	//Setting contact surface flag
	if (!VTKseabedOk && !gm.post.GetWritingFlags().GetRigidContactSurfacesFlag())
		gm.post.GetWritingFlags().SetRigidContactSurfacesFlag(true);
}

//Generates constraints
void MooringModel::GenerateConstraints()
{
	//Bool tables
	BoolTable U(true, 2, false), ROT(true, 2, false);
	
	gm.GenerateNodalConstraint(++cur_constraint, node_set_contact_id, U, U, U, ROT, ROT, ROT);

	//Anchors
	U.Reset(true, 3);
	ROT.Reset(true, 2);
	
	BoolTable ROTZ(true, 1, false);

	//With different constraint definitions
	for (const MoorConstraint& anchor : anchor_constraints)
	{
		//Copies of the booltables for the first steps
		BoolTable ROTX2(ROT), ROTY2(ROT), ROTZ2(ROTZ);

		ROTX2.Multiple_Push_Back(anchor.GetRotX());
		ROTY2.Multiple_Push_Back(anchor.GetRotY());
		ROTZ2.Multiple_Push_Back(anchor.GetRotZ());

		gm.GenerateNodalConstraint(++cur_constraint, anchor.GetNodeset(), U, U, U, ROTX2, ROTY2, ROTZ2);
	}

	//Anchors with default constraints
	ROT.Push_Back(true);
	ROTZ.Push_Back(true);

	for (const unsigned int& nodeset : anchor_nodesets_id)
		gm.GenerateNodalConstraint(++cur_constraint, nodeset, U, U, U, ROT, ROT, ROTZ);

	//Fairleads
	U.Reset(std::vector{ true, true, true, false });
	ROT.Reset(std::vector{ false, true, false });
	for (auto nodeset : fairlead_nodesets_id)
		gm.GenerateNodalConstraint(++cur_constraint, nodeset, U, U, U, ROT, ROT, ROT);

	//Lines
	if (!line_constraints.empty())
	{
		//Default conditions (steps to set the FE model)
		std::vector<bool> bool_list = { true, true, false };
		//Check for other steps after coupling fairleads
		if ( moorsolution.GetStepsBeforeAnalysis() > 3 )
		{
			for ( unsigned int i = 3; i < moorsolution.GetStepsBeforeAnalysis(); ++i )
				bool_list.push_back(false);
		}

		for (MoorConstraint& constr : line_constraints)
		{
			//Booltables
			std::vector<BoolTable> bt_vec(6);
			std::fill(bt_vec.begin(), bt_vec.end(), bool_list);

			//Booltables
			for (unsigned int i = 0; i < 6; i++ )
				bt_vec[i].Multiple_Push_Back(constr.GetConstraint(i));

			gm.GenerateNodalConstraint(++cur_constraint, lines[constr.GetNumber() - 1].GetNodesetB() + 1,
									   bt_vec[0], bt_vec[1], bt_vec[2], bt_vec[3], bt_vec[4], bt_vec[5]);
		}
	}
	else
	{
		for ( LineDisplacementField& disp_field : line_disp_fields )
		{
			BoolTable bool_table;

			//Default conditions (steps to set the FE model)
			std::list bool_list = {true, true, false};
			if ( moorsolution.GetStepsBeforeAnalysis() > 3 )
				for ( unsigned int i = 3; i < moorsolution.GetStepsBeforeAnalysis(); ++i )
					bool_list.push_back(false);

			//Other steps, until reach the step after the displacement field
			for ( unsigned int i = 1; i <= disp_field.GetStep() + 1; ++i )
				i == disp_field.GetStep() ? bool_list.emplace_back(true) : bool_list.emplace_back(false);
			bool_table.Multiple_Push_Back(bool_list);

			gm.GenerateNodalConstraint(++cur_constraint, lines[disp_field.GetNumber() - 1].GetNodesetB() + 1,
									   bool_table, bool_table, bool_table, bool_table, bool_table, bool_table);
		}
	}

	
	//Vessel
	///Default constraint (all fixed)
	if (vessel_constraints.empty())
	{
		//Vessel - fixed
		U.Reset(true, 1);
		ROT.Reset(true, 1);
		for (Vessel& vessel : vessels)
			gm.GenerateNodalConstraint(++cur_constraint, vessel.GetNodeset(), U, U, U, ROT, ROT, ROT);
	}
	///Different constraint(s) defined in the input file
	else
	{
		int step0 = 3;

		//If there is a dynamic relaxation step
		if (moorsolution.ExistDynRelax_Lines())			
			++step0;
		//If there is a numerical stiffness matrix
		if (stiff_matrix && stiff_matrix->ExistNumericalStiffMat()) 
			++step0;
		//If there is a sea current 
		if (moorsolution.ExistSeaCurrentStep()) // TODO: verificar se deve ser giraffe environment
			++step0;

		//Creates booltables
		BoolTable boolX(true, step0, false), boolY(true, step0, false), boolZ(true, step0, false),
			boolROTX(true, step0, false), boolROTY(true, step0, false), boolROTZ(true, step0, false);

		
		//Vessels with constraint defined
		std::unordered_set<unsigned int> constrainted_vessels;

		for (MoorConstraint& constr : vessel_constraints)
		{
			constrainted_vessels.insert(constr.GetNumber());
			 
			//BoolTables for the current vessel 
			BoolTable vessel_X(boolX), vessel_Y(boolY), vessel_Z(boolZ),
				vessel_ROTX(boolROTX), vessel_ROTY(boolROTY), vessel_ROTZ(boolROTZ);

			//Booltables
			for (int i = 0; i < 6; i++)
			{
				auto const& c = constr.GetConstraint(i);
				if (i == 0)			vessel_X.Multiple_Push_Back(c);
				else if (i == 1)	vessel_Y.Multiple_Push_Back(c);
				else if (i == 2)	vessel_Z.Multiple_Push_Back(c);
				else if (i == 3)	vessel_ROTX.Multiple_Push_Back(c);
				else if (i == 4)	vessel_ROTY.Multiple_Push_Back(c);
				else if (i == 5)	vessel_ROTZ.Multiple_Push_Back(c);
			}

			gm.GenerateNodalConstraint(++cur_constraint, vessels[constr.GetNumber() - 1].GetNodeset(), 
									   vessel_X, vessel_Y, vessel_Z, vessel_ROTX, vessel_ROTY, vessel_ROTZ);
		}

		//Iterate through the vessels while still exist vessels to constraint
		if (constrainted_vessels.size() != vessels.size())
		{
			//Vessel - fixed
			U.Reset(true, 1);
			ROT.Reset(true, 1);
			for (Vessel& vessel : vessels)
			{
				if (constrainted_vessels.find(vessel.GetNumber()) != constrainted_vessels.end())
					continue; //found -> already constrainted
				else
				{
					constrainted_vessels.insert(vessel.GetNumber());
					gm.GenerateNodalConstraint(++cur_constraint, vessel.GetNodeset(), U, U, U, ROT, ROT, ROT);
				}
			}
		}
	}


	//Seabed - fixed
	U.Reset(true, 1);
	ROT.Reset(true, 1);
	gm.GenerateNodalConstraint(++cur_constraint, pil_node_set_id, U, U, U, ROT, ROT, ROT);
}


//Create segments for lines with 'SegmentSet' defined 
void MooringModel::GenerateSegments()
{
	//Iterates through the lines
	for (Line& line : lines)
	{
		if (line.GetSegmentSetOpt())
		{
			//Iterates through the 'LineSegment' objects in 'SegmentSet', 
			//copying it to the 'segments' vector in the current line
			unsigned int setID = line.GetSegmentSet() - 1;
			for (unsigned int i = 0; i < segment_sets[setID].GetSegmentSetSize(); ++i)
				line.AddSegment(segment_sets[setID].GetSegment(i));
		}
	}
}
