#include "PCH.h"
#include "MooringModel.h"
#include "Summary.h"
#include "Log.h"
#include "IO.h"
#include "AuxFunctions.h"

//max/min difinitions
#ifndef max
#define max(a,b)	(((a) > (b)) ? (a) : (b))
#endif
#ifndef min
#define min(a,b)	(((a) < (b)) ? (a) : (b))
#endif


//Global object
extern GiraffeModel gm;
 
//Constants variables
constexpr auto PI = 3.1415926535897932384626433832795;
static double g;

MooringModel::MooringModel()
	: cur_line(0), tot_elem(0), cur_node_mesh(1), cur_elem(1), cur_cs(2), 
	cur_node_set(1), cur_vessel(0), cur_special_constraint(0), cur_node_set_constraint(1), 
	cur_constraint(0), cur_load(0), cur_disp(0), cur_rbdata(0), node_set_contact(0), pil_node_set(0),
	TDZ(false), existSharedLine(false), x_tdp(0.0), x_tdp_ext(0.0), elem_tdp(0), seg_tdp(0), existTDP(true), 
	penetration(nullptr), rot_fairlead(PI / 2.0), extrem_tensions({0.,0.})
{
	//Reserving positions for vectors
	line_vector.reserve(32);
	vessel_vector.reserve(16);
	keypoint_vector.reserve(64);
	segment_property_vector.reserve(16);
	platform_vector.reserve(16);
}

MooringModel::~MooringModel()
{
	//Destroying pointers
	if (penetration)	delete[] penetration;
}

bool MooringModel::GenerateGiraffeModel()
{
	//Check if segments must be generated from 'SegmentSet'
	GenerateSegments();

	//Computes segment properties from readed data
	PreCalcSegmentPropertiesData();

	//Mooring model -> Giraffe model
	CopyData();

	//Catenary equation -> prescribed displacements and TDZ (if exists)
	if (!GenerateCatenary())
		return false;
	
	//Check the necessity to couple rotation of beam segments between chain segments
	CheckDummyElements();

	//Contact node set and surface 
	GenerateContact();
	
	//Dynamic relaxation parameters
	if (moorsolution.bool_DynamicRelax)	
		GenerateDynamicRelaxation();

	/*Check if exist at least one shared line 
		important to create same displacemt with the correspondent vessels*/
	existSharedLine = Look4SharedLine();

	//Vessel(s)
	GenerateVessel();
	
	//Rigid nodeset to couple fairleads and vessel
	GenerateRigidNodeSets();

	//Set model and generate steps (with pescribed displacements and/or loads)
	GeneralSetting();

	//SeabedSetRhoFluid
	GenerateSeabed();

	//Nodal constraints 
	GenerateConstraints();

	//Platform(s)
	if (!platform_vector.empty())
		GeneratePlatform();
		
	return true;
}

//Computes data from entered Segment Properties
void MooringModel::PreCalcSegmentPropertiesData()
{
	//Percorrendo properties
	for (SegmentProperty& seg : segment_property_vector)
	{
		//Se for do tipo polimérico é necessário calcular propriedades mecânicas equivalentes
		if (seg.type == 'b' && seg.E != 0)
		{
			if (seg.SG != 1.0 && seg.E > 0.0)
				seg.diameter = sqrt(4 * seg.rho / (PI * seg.SG * environment.GetRhoFluid()));

			double d = seg.diameter;
			double E = seg.E;
			double nu = seg.nu;
			double G = E / (2 * (1 + nu));			//shear modulus
			double A = PI * pow(d, 2) / 4.0;		//area
			double J = PI * pow(d, 4) / 32.0;		//polar moment
			double I = PI * pow(d, 4) / 64.0;		//inertia moment

			//Setting values
			seg.EA = E * A;
			seg.EI = E * I;
			seg.GA = G * A;
			seg.GJ = G * J;
		}
		if (seg.type == 't' && seg.SG != 1 && seg.E > 0.0)
			seg.diameter = sqrt(4 * seg.rho / (PI * seg.SG * environment.GetRhoFluid())); 
	}
}

//Copies data from MooringModel to GiraffeModel database
void MooringModel::CopyData()
{	
	/*	Segment properties -> PipeSection	*/
	for (SegmentProperty& sp : segment_property_vector)
		gm.pipe_section_vector.emplace_back(PipeSection(sp.number, sp.type, sp.diameter, sp.rho, sp.EA, sp.EI, sp.GJ, sp.GA, 
														sp.CDt, sp.CDn, sp.CAt, sp.CAn, sp.E, sp.nu));

	/*	MoorEnvironment -> Environment	*/

	//Gravity
	g = MoorEnvironment::GetGravity();
	gm.environment.SetGravity(g);
	
	BoolTable bool_g; //Gravity bootable
	bool_g.Set(1, true);
	gm.environment.SetGravityBooltable(bool_g);

	gm.environment.SetRhoFluid (environment.GetRhoFluid());
	gm.environment.SetSeaCurrentVec(environment.GetSeaCurrentVec());
	gm.environment.SetWaterDepth(environment.GetWaterDepth());

	//CADs data to post processing 
	gm.post.cads_vector = std::move(moorpost.platform_cads);
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

	for (Line& line : line_vector)
	{
		/*======================*
		 * Initialize variables *
		 *======================*/

		//Number of segments
		unsigned int n_segs = static_cast< unsigned int >( line.segments.size() );

		//Line ID
		cur_line = line.number - 1;

		//Points to represent the anchor and/or fairlead
		Matrix coordinates_A(3), coordinates_B(3);

		//Line projections on seabed
		double Hf, Vf;

		//Original position of the fairlead used to calculate stiffness matrix
		Matrix Fair_stiff_matrix(3);

		//Forces at the top
		Matrix F(2);

		//segment to generate mesh without considering TDZ
		unsigned int seg_init = 0;

		tot_elem = 0;

		/*===========*
		 * Functions *
		 *===========*/

		//Setting general parameters 
		Catenary_GeneralSetting(line, n_segs, coordinates_A, coordinates_B, Fair_stiff_matrix);

		//Vertical forces at the end of each segment
		std::vector <double> FV(( size_t )n_segs + 1);

		if(!SolveCatenaryEquations(line, n_segs, coordinates_A, coordinates_B, Hf, Vf, F, FV, Fair_stiff_matrix))
			return false;

		SetLinesConfiguration(line, F, FV, n_segs);

		if (line.percent > 0 && x_tdp > 0 && abs(line.anc_tdp) > 0 && abs(line.tdp_fair) > 0)
			GenerateCatenaryTDZ(line, n_segs, seg_init);
		else
			TDZ = false;

		//Confere tamanho dos segmentos depois da TDZ, se existirem ou todos de uma vez, caso não haja TDZ
		if (!TDZ || seg_init == ++line.tdz->tdz_f.seg)
			CheckSegmentsSize(line, n_segs, seg_init);

		//Displacement field data (coordinates, segments)
		std::vector<std::vector<double>> xcat_n, zcat_n, roty_n;
		xcat_n.resize(n_segs), zcat_n.resize(n_segs), roty_n.resize(n_segs);

		//vector of vectors with meshes for the line segments
		x0_n.resize(n_segs);

		//Reserving memory for data of each segment
		for (unsigned int seg = 0; seg < n_segs; seg++)
		{
			unsigned int n_nodes = line.segments[seg].GetNNodes();
			x0_n[seg].resize(n_nodes);
			xcat_n[seg].resize(n_nodes);
			zcat_n[seg].resize(n_nodes);
			roty_n[seg].resize(n_nodes);
		}
		//Setting mesh parameters (creates matrix with nodes position)
		SetMeshProperties(line, n_segs);

		//Call GenerateMesh to generate the current line mesh
		GenerateMesh(line, coordinates_A, coordinates_B, Hf, Vf);

		//Generates displacement field (and updates fairlead rotation)
		GenerateCatenaryDisplacement(line, n_segs, F, FV, cur_node, xcat_n, zcat_n, roty_n);
	}

	return true;
}

/*Catenary functions
	  -> 'GenerateCatenary' calls other functions*/
void MooringModel::Catenary_GeneralSetting(Line& line, const unsigned int& n_segs, 
										   Matrix& A, Matrix& B, Matrix& Fairleads_StiffnessMatrix)
{
	//Calculating gamma_s for all segments (and the maximum), total length and equivalent parameters
	line.total_length = 0.0;

	for (unsigned int seg = 0; seg < n_segs; seg++)
	{
		line.total_length += line.segments[seg].GetLength();

		//Gamma_s
		line.gamma_s.emplace_back(g * segment_property_vector[line.segments[seg].GetProperty() - 1].rho
								  - g * environment.GetRhoFluid() * PI * pow(segment_property_vector[line.segments[seg].GetProperty() - 1].diameter, 2) / 4.0);
	}

	//Anchor and fairlead nodes ID
	unsigned int point_A = line.keypoint_A;
	unsigned int point_B = line.keypoint_B;

	//Setting points of the anchor and fairlead(s)
	A(0, 0) = keypoint_vector[point_A - 1].GetCoordinate('x');
	A(1, 0) = keypoint_vector[point_A - 1].GetCoordinate('y');
	A(2, 0) = keypoint_vector[point_A - 1].GetCoordinate('z');
	B(0, 0) = keypoint_vector[point_B - 1].GetCoordinate('x');
	B(1, 0) = keypoint_vector[point_B - 1].GetCoordinate('y');
	B(2, 0) = keypoint_vector[point_B - 1].GetCoordinate('z');

	//Calculating original position of the fairlead to calculate analytical stiffness matrix
	Fairleads_StiffnessMatrix(0, 0) = keypoint_vector[point_B - 1].GetCoordinate('x');
	Fairleads_StiffnessMatrix(1, 0) = keypoint_vector[point_B - 1].GetCoordinate('y');
	Fairleads_StiffnessMatrix(2, 0) = keypoint_vector[point_B - 1].GetCoordinate('z');
}

bool MooringModel::SolveCatenaryEquations(Line& line, const unsigned int& n_segs, Matrix& A, Matrix& B,
										  double& Hf, double& Vf, Matrix& F, std::vector <double>& FV,
										  Matrix& Fairleads_StiffnessMatrix)
{
	//Limits to the counters (force initial guess) and error
	static constexpr int MAX_ITERATIONS_FH0 = 10;
	static constexpr int MAX_ITERATIONS_FV0 = 1000;
	static constexpr int MAX_ITERATIONS_NEWTON = 50;
	static constexpr double error_max = 1e-6;

	//Residue
	double res;

	//Jacobian matrix
	Matrix J(2, 2);

	//Contribution to stiffness matrix for the current line
	static Matrix Ki(2, 2);
	//Counters
	int aux0, aux1, aux2, aux3;

	//Supposes that there is no TDP
	existTDP = false;

	//Order of the force initial guess
	auto [gmin, gmax] = std::minmax_element(line.gamma_s.begin(), line.gamma_s.end());
	int m = ( int )floor(log10(max(fabs(*gmin), fabs(*gmax))));

	//Two times = before and after penetration
	for (aux0 = 1; aux0 <= 2; aux0++)
	{
		//Anchor and fairlead horizontal projections
		Hf = sqrt(pow(( A(0, 0) - B(0, 0) ), 2) + pow(( A(1, 0) - B(1, 0) ), 2));
		if (aux0 == 1)	Vf = B(2, 0) - A(2, 0);

		//Updates FH initial guess 
		for (aux1 = 1; aux1 < MAX_ITERATIONS_FH0; aux1++)
		{
			//Updates FV initial guess 
			for (aux2 = 1; aux2 < MAX_ITERATIONS_FV0; aux2++)
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
					FV[n_segs] = F(1, 0);
					double dif = 0.0;
					for (int cont_ds = ( int )n_segs - 1; cont_ds >= 0; cont_ds--)
					{
						dif -= line.segments[cont_ds].GetLength() * line.gamma_s[cont_ds];
						FV[cont_ds] = FV[n_segs] + dif;
					}

					//if (A(2, 0) <= -environment.waterdepth)
					//{
						for (unsigned int cont = 0; cont < n_segs + 1; cont++)
						{
							if (FV[cont] < 0)	FV[cont] = 0.0;
							else break;	//Break when it starts to be positive, the negative values are related to buoys only
						}
					//}

					std::vector <double> raiz;
					for (unsigned int r = 0; r < n_segs + 1; r++)
						raiz.push_back(sqrt(pow(F(0, 0), 2) + pow(FV[r], 2)));

					double h = 0.0, v = 0.0; //projections
					Matrix E(2); //equation system

					J.clear();
					for (size_t seg = 1; seg <= ( size_t )n_segs; seg++)
					{
						double cur_gamma = line.gamma_s[seg - 1];
						double cur_EA = segment_property_vector[( line.segments[seg - 1].GetProperty() ) - 1].EA;
						double cur_len = line.segments[seg - 1].GetLength();

						Matrix J_aux(2, 2);
						J_aux(0, 0) = cur_len / cur_EA + 1.0 / cur_gamma * ( log(( FV[seg] + raiz[seg] ) / F(0, 0)) - log(( FV[seg - 1] + raiz[seg - 1] ) / F(0, 0)) ) - 1.0 / cur_gamma * ( FV[seg] / raiz[seg] - FV[seg - 1] / raiz[seg - 1] );
						J_aux(0, 1) = F(0, 0) / cur_gamma * ( 1.0 / raiz[seg] - 1.0 / raiz[seg - 1] );
						J_aux(1, 0) = J_aux(0, 1);
						J_aux(1, 1) = 1.0 / cur_gamma * ( FV[seg] / raiz[seg] - FV[seg - 1] / raiz[seg - 1] ) + 1.0 / ( cur_EA * cur_gamma ) * ( FV[seg] - FV[seg - 1] );

						J = J + J_aux;

						h += cur_len * ( 1 + F(0, 0) / cur_EA ) - ( FV[seg] - FV[seg - 1] ) / cur_gamma + F(0, 0) / cur_gamma * ( log(( FV[seg] + raiz[seg] ) / F(0, 0)) - log(( FV[seg - 1] + raiz[seg - 1] ) / F(0, 0)) );
						v += 1.0 / cur_gamma * ( raiz[seg] - raiz[seg - 1] ) + 0.5 * ( pow(FV[seg], 2) - pow(FV[seg - 1], 2) ) / ( cur_gamma * cur_EA );
					}
					E(0, 0) = h - Hf;
					E(1, 0) = v - Vf;

					F = F - (invert2x2(J) * E);

					if (F(0, 0) < 0) F(0, 0) = abs(F(0, 0));
					if (F(1, 0) < 0) F(1, 0) = abs(F(1, 0));

					res = sqrt(pow(E(0, 0), 2) + pow(E(1, 0), 2));
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
			std::stringstream ss;
			ss << "\n   + Error solving equations for line number " << line.number;
			Log::AddWarning(ss);
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
				for (unsigned int cont = 1; cont < n_segs + 1; ++cont)
				{
					if (FV[cont] > 0)
					{
						seg_tdp = --cont;
						break;
					}
				}
			}
			//Otherwise, set segment to the first
			else
				seg_tdp = 0;
		}

		//Equivalent weight until reach TDP segment (included)
		double gamma_eq = 0.0;

		//Penetration at the end of the first loop, if the line has an anchor
		if (!line.hasAnchor)
			break;
		else if (aux0 == 1)
		{
			//The penetration is calculated with data of the segments that have contact with seabed in the static configuration 
			//or the first segment (in cases like a steep wave line)
			unsigned int lim_seg = existTDP ? seg_tdp : 0;

			//Equivalents paramenters to set penetration
			double rholen = 0.0, arealen = 0.0;

			//To set penetration (dz)
			int elements = 0;

			//Until reaches TDP segment (if exists)
			for (unsigned int seg = 0; seg <= lim_seg; seg++)
			{
				arealen += ( PI * pow(segment_property_vector[line.segments[seg].GetProperty() - 1].diameter, 2) / 4.0 ) * line.segments[seg].GetLength();
				rholen += segment_property_vector[line.segments[seg].GetProperty() - 1].rho * line.segments[seg].GetLength();
				elements += line.segments[seg].GetDiscretization();
			}

			//Equivalent specific weight
			if (existTDP)		gamma_eq = g * rholen;

			//If exist other segments, calculate equivalent parameters (used to calculate dynamic relaxation, if exists)
			if (lim_seg != n_segs - 1)
			{
				//If there is no TDP, starts at segment 0, otherwise; at the next segment after TDP
				unsigned int seg = existTDP ? lim_seg + 1 : 0;
				for (; seg < n_segs; ++seg)
				{
					arealen += ( PI * pow(segment_property_vector[line.segments[seg].GetProperty() - 1].diameter, 2) / 4.0 ) * line.segments[seg].GetLength();
					rholen += segment_property_vector[line.segments[seg].GetProperty() - 1].rho * line.segments[seg].GetLength();
					elements += line.segments[seg].GetDiscretization();
				}
			}

			//Equivalents paramenters to set penetration
			rho_eq.push_back(rholen / line.total_length);
			area_eq.push_back(arealen / line.total_length);

			/*Imposing penetrarion in the seabed*/

			//Equivalent specific weight
			if (!existTDP)	gamma_eq = g * rholen;

			//Vertical displacement
			double dz = -gamma_eq / ( elements * environment.GetSeabed().stiffness );
			penetration[line.number - 1].SetLine(0, 0, 0, 0, 0, 0, 0);
			penetration[line.number - 1].SetLine(1, 0, 0, dz, 0, 0, 0);

			//Generates penetration displacement
			gm.GenerateNodalDisplacement(++cur_disp, line.number * 3, 1, &penetration[line.number - 1]);

			//Fairlead force used to calculate analytical stiffness matrix
			B(2, 0) = keypoint_vector[line.keypoint_B - 1].GetCoordinate('z') - dz;
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

void MooringModel::SetLinesConfiguration(Line& line, Matrix& F, std::vector <double>& FV, const unsigned int& n_segs)
{
	//Looking for TDP
	if (!existTDP)//seg_tdp<0
	{
		x_tdp = 0;
		x_tdp_ext = 0;
	}
	else
	{
		//Calculating TDP and length in the segments before TDP segment 
		double sum_len_tdp = 0;
		for (unsigned int i = 0; i <= seg_tdp; i++)
			sum_len_tdp += line.segments[i].GetLength();

		x_tdp = sum_len_tdp - FV[( size_t )seg_tdp + 1] / line.gamma_s[seg_tdp];
		double leng_tdp = x_tdp - sum_len_tdp;

		//Determination of the TDP position after the extension
		double leng_ext = 0;
		for (unsigned int seg = 0; seg <= seg_tdp; seg++)
			leng_ext += line.segments[seg].GetLength() * ( 1 + F(0, 0) / segment_property_vector[line.segments[seg].GetProperty() - 1].EA );

		x_tdp_ext = leng_ext + leng_tdp * ( 1 + F(0, 0) / segment_property_vector[line.segments[seg_tdp].GetProperty() - 1].EA );
	}

	//Determination of the line configuration type
	for (unsigned int cont = 0; cont < n_segs; cont++)
	{
		if (!existTDP)
		{
			if (keypoint_vector[line.keypoint_A-1].GetCoordinate('x') == keypoint_vector[line.keypoint_B-1].GetCoordinate('x') &&
				keypoint_vector[line.keypoint_A-1].GetCoordinate('y') == keypoint_vector[line.keypoint_B-1].GetCoordinate('y'))
				line.configuration = "Vertical line";
			else
				line.configuration = "Suspended above the seabed";
		}
		else if (line.gamma_s[cont] < 0 && line.configuration != "Lazy wave" && line.configuration != "Steep wave")
		{
			if (x_tdp > 0)
				line.configuration = "Lazy wave";
			else
				line.configuration = "Steep wave";
		}
		else
		{
			if (line.configuration != "Lazy wave" && line.configuration != "Steep wave")
			{
				if (x_tdp > 0)
					line.configuration = "Catenary";
				else
					line.configuration = "Taut-Leg";
			}
		}
	}
}

void MooringModel::GenerateCatenaryTDZ(Line& line, const unsigned int& n_segs, unsigned int& seg_init)
{
	TDZ = true;

	line.tdz->tdz_a.node_extreme_line = line.tdz->tdz_a.node_extreme_seg = false;
	line.tdz->tdz_f.node_extreme_line = line.tdz->tdz_f.node_extreme_seg = false;

	//Checks if TDZ exceeds the line
	line.tdz->x_a = x_tdp + line.anc_tdp;

	//If the stretch more discretized exceeds the anchor
	if (line.tdz->x_a < 0)
	{
		line.tdz->x_a = 0.0;
		line.tdz->tdz_a.node_extreme_line = true;
		line.tdz->tdz_a.elem = 1;
		line.tdz->tdz_a.len_elem_out = line.segments[0].GetLength() / line.segments[0].GetDiscretization();
	}
	line.tdz->x_f = x_tdp + line.tdp_fair;

	//If the stretch more discretized exceeds the fairlead
	if (line.tdz->x_f > line.total_length)
	{
		line.tdz->x_f = 0.0;
		line.tdz->tdz_f.node_extreme_line = true;
		line.tdz->tdz_f.elem = 1;
		line.tdz->tdz_f.len_elem_out = line.segments[n_segs - 1].GetLength() / line.segments[n_segs - 1].GetDiscretization();
	}

	//Finding the segments which contais the begin and the finish of the TDZ
	double cur_x = 0.0;
	bool seek_pointA = true, seek_pointF = true;
	for (unsigned int cur_seg = 0; cur_seg < n_segs; cur_seg++)
	{
		cur_x += line.segments[cur_seg].GetLength();
		if (line.tdz->x_a < cur_x && seek_pointA)
		{
			line.tdz->tdz_a.seg = cur_seg;
			seek_pointA = false;
		}
		if (line.tdz->x_f <= cur_x && seek_pointF)
		{
			line.tdz->tdz_f.seg = cur_seg;
			seek_pointF = false;
		}
		if (!seek_pointA && !seek_pointF)
			break;
	}

	//Confines TDZ in the TDP segment
	if (seg_tdp - line.tdz->tdz_a.seg > 1)
	{
		line.tdz->tdz_a.node_extreme_seg = true;
		line.tdz->tdz_a.seg = ( int )seg_tdp;
		line.tdz->tdz_a.len_elem_out = line.segments[seg_tdp - 1].GetLength() / line.segments[seg_tdp - 1].GetDiscretization();
	}
	else
		line.tdz->tdz_a.len_elem_out = line.segments[seg_tdp].GetLength() / line.segments[seg_tdp].GetDiscretization();
	if (line.tdz->tdz_f.seg - seg_tdp > 1)
	{
		line.tdz->tdz_f.node_extreme_seg = true;
		line.tdz->tdz_f.seg = ( int )seg_tdp;
		line.tdz->tdz_f.len_elem_out = line.segments[( size_t )seg_tdp + 1].GetLength() / line.segments[( size_t )seg_tdp + 1].GetDiscretization();
	}
	else
		line.tdz->tdz_f.len_elem_out = line.segments[seg_tdp].GetLength() / line.segments[seg_tdp].GetDiscretization();

	double len_before_seg_a = 0; //total length before the segment which contais the point A

	//Number of nodes in segments before the segments which contais the point A (if these segments exist)
	if (line.tdz->tdz_a.seg > 0)
	{
		for (unsigned int seg = 0; seg < line.tdz->tdz_a.seg; seg++)
		{
			double len = line.segments[seg].GetLength();
			unsigned int tdz_disc = line.segments[seg].GetDiscretization();
			len_before_seg_a += len;
			line.tdz->tdz_a.elem += tdz_disc;

			int n = segment_property_vector[line.segments[seg].GetProperty() - 1].type == 't' ? 1 : 2;

			line.segments[seg].SetNNodes(n * tdz_disc + 1);

			line.segments[seg].SetNElements(tdz_disc);
			tot_elem += tdz_disc;
		}
	}

	double len = line.segments[seg_tdp].GetLength() / line.segments[seg_tdp].GetDiscretization();
	line.tdz->len_elem_tdp = len * ( 1.0 - line.percent / 100.0 );

	//Verifica se TDZ inicia no primeiro elemento do segmento e corrige comprimento do elemento anterior à TDZ
	if (line.tdz->x_a < len_before_seg_a + len && !line.tdz->tdz_a.node_extreme_seg)
	{
		line.tdz->tdz_a.elements_out = ( unsigned int )line.segments[( size_t )seg_tdp - 1].GetLength() / line.segments[( size_t )seg_tdp - 1].GetDiscretization();
		line.tdz->tdz_a.node_extreme_seg = true;
		line.tdz->x_a = len_before_seg_a;
	}
	else //Caso contrário, acha o elemento que inicia a TDZ
	{
		line.tdz->tdz_a.elements_out = ( unsigned int )floor(( line.tdz->x_a - len_before_seg_a ) / len);
		line.tdz->x_a = len_before_seg_a + line.tdz->tdz_a.elements_out * len;
	}

	//Verifica se TDZ acaba no último elemento do segmento e corrige comprimento do elemento posterior à TDZ
	if (line.tdz->x_f > len_before_seg_a + line.segments[seg_tdp].GetLength() && !line.tdz->tdz_f.node_extreme_seg)
	{
		line.tdz->tdz_f.elements_out = ( unsigned int )line.segments[( size_t )seg_tdp + 1].GetLength() / line.segments[( size_t )seg_tdp + 1].GetDiscretization();
		line.tdz->tdz_f.node_extreme_seg = true;
		line.tdz->x_f = len_before_seg_a + line.segments[seg_tdp].GetLength();
	}
	else //Caso contrário, acha quantidade de elementos no segmento após a TDZ
	{
		line.tdz->tdz_f.elements_out = ( unsigned int )floor(( len_before_seg_a + line.segments[seg_tdp].GetLength() - line.tdz->x_f ) / len);
		line.tdz->x_f = len_before_seg_a + line.segments[seg_tdp].GetLength() - line.tdz->tdz_f.elements_out * len;
	}

	line.tdz->tdz_a.Sn = x_tdp - line.tdz->x_a + line.tdz->len_elem_tdp / 2.0 + line.tdz->tdz_a.len_elem_out;
	line.tdz->CreateTDZsegment(line.tdz->tdz_a);

	line.tdz->tdz_f.Sn = line.tdz->x_f - x_tdp + line.tdz->len_elem_tdp / 2.0 + line.tdz->tdz_f.len_elem_out;
	line.tdz->CreateTDZsegment(line.tdz->tdz_f);

	if (line.tdz->tdz_a.case_seg > 4 && line.tdz->tdz_f.case_seg > 4)
		TDZ = false;

	line.tdz->tdz_a.elem = line.tdz->tdz_a.elements_out + 1;
	elem_tdp = line.tdz->tdz_a.elem + line.tdz->tdz_a.n_elements - 2;
	line.tdz->tdz_f.elem = elem_tdp + line.tdz->tdz_f.n_elements - 2;

	//Number of nodes in TDZ segment
	int n = segment_property_vector[line.segments[seg_tdp].GetProperty() - 1].type == 't' ? 1 : 2;
	unsigned int elements_seg_tdz = line.tdz->tdz_a.elements_out + line.tdz->tdz_a.n_elements - 2 + 1 + line.tdz->tdz_f.n_elements - 2 + line.tdz->tdz_f.elements_out;

	line.segments[seg_tdp].SetNNodes(n * elements_seg_tdz + 1);
	line.segments[seg_tdp].SetNElements(elements_seg_tdz);
	tot_elem += elements_seg_tdz;

	//Initial segment to check
	if (n_segs - line.tdz->tdz_f.seg > 1)
		seg_init = ++line.tdz->tdz_f.seg;
}

void MooringModel::CheckSegmentsSize(Line& line, const unsigned int& n_segs, const unsigned int& seg_init)
{
	for (unsigned int seg = seg_init; seg < n_segs; seg++)
	{
		//Nodes of the segment
		unsigned int n = segment_property_vector[line.segments[seg].GetProperty() - 1].type == 't' ? 1 : 2;
		unsigned int disc = line.segments[seg].GetDiscretization();
		line.segments[seg].SetNNodes(n * disc + 1);
		//Elements of the segment
		line.segments[seg].SetNElements(disc);
		
		//Whole line
		tot_elem += disc;
		line.tot_nodes = line.segments[seg].GetNNodes();
	}

	//Exclude transitions between segments
	line.tot_nodes -= ( unsigned int )line_vector[line.number - 1].segments.size() - 1;
}


void MooringModel::SetMeshProperties(Line& line, const unsigned int& n_segs)
{
	double cur_len = 0.0;

	//Calculate mesh for segments before the seg_a (if these segments exist) or for all segments (if there is no TDZ)
	unsigned int seg_stop_mesh = TDZ ? ( line.tdz->tdz_a.seg ) : n_segs;
	for (unsigned int seg = 0; seg < seg_stop_mesh; seg++)
	{
		size_t div = (size_t)line.segments[seg].GetDiscretization();
		double len = line.segments[seg].GetLength();

		for (size_t i = 1; i <= div; i++)
		{
			if (seg > 0 && i == 1 && n_segs > 1) //Copy last node to the first segment node
				x0_n[seg][0] = cur_len;

			if (segment_property_vector[line.segments[seg].GetProperty() - 1].type == 't')
				x0_n[seg][i] = cur_len + len * i / div;
			else
			{
				x0_n[seg][2 * i - 1] = cur_len + len * ( 2.0 * i - 1.0 ) / ( 2.0 * div );
				x0_n[seg][2 * i] = cur_len + len * ( 2.0 * i ) / ( 2.0 * div );
			}
		}
		cur_len += len;
	}

	//TouchDown zone segment
	if (TDZ)
	{
		double add_len;

		//Until TDZ starts (node A)
		size_t div = line.segments[seg_tdp].GetDiscretization();
		double len = line.segments[seg_tdp].GetLength();
		if (!line.tdz->tdz_a.node_extreme_seg)
		{
			for (size_t i = 1; i <= (size_t)line.tdz->tdz_a.elements_out; i++)
			{
				if (segment_property_vector[line.segments[seg_tdp].GetProperty() - 1].type == 't')
					x0_n[0][i] = cur_len + len * (double)(i / div);
				else
				{
					x0_n[0][2 * i - 1] = cur_len + len * ( 2.0 * i - 1.0 ) / ( 2.0 * div );
					x0_n[0][2 * i] = cur_len + len * ( 2.0 * i ) / ( 2.0 * div );
				}
			}
			cur_len += line.tdz->tdz_a.elements_out * len / div;
		}

		//Until reach TDP element
		 //Checks the boundaries to consider the PG 
		size_t init_elem = ( line.tdz->tdz_a.node_extreme_seg || line.tdz->tdz_a.node_extreme_line ) ? line.tdz->tdz_a.n_elements : line.tdz->tdz_a.n_elements - 1;
		size_t end_elem = ( line.tdz->tdz_a.case_seg > 2 ) ? 1 : 2;
		for (size_t i = init_elem, elem_line = ( size_t)line.tdz->tdz_a.elem; i >= end_elem; i--, elem_line++)
		{
			add_len = line.tdz->len_elem_tdp * pow(line.tdz->tdz_a.q, ( i - 1 )) + line.tdz->tdz_a.dist_dif_len;
			if (segment_property_vector[line.segments[seg_tdp].GetProperty() - 1].type == 't')
				x0_n[0][elem_line] = cur_len + add_len;
			else
			{
				x0_n[0][2 * elem_line - 1] = cur_len + 0.5 * add_len;
				x0_n[0][2 * elem_line] = cur_len + add_len;
			}
			cur_len += add_len;
		}

		//TDP element
		add_len = ( line.tdz->tdz_f.case_seg > 2 ) ? ( line.tdz->len_elem_tdp + line.tdz->tdz_f.dist_dif_len ) : ( line.tdz->len_elem_tdp );
		if (segment_property_vector[line.segments[seg_tdp].GetProperty() - 1].type == 't')
			x0_n[0][elem_tdp] = cur_len + add_len;
		else
		{
			x0_n[0][2 * (size_t)elem_tdp - 1] = cur_len + 0.5 * add_len;
			x0_n[0][2 * (size_t)elem_tdp] = cur_len + add_len;
		}
		cur_len += add_len;

		//Until TDZ ends (node F)
		//Checks the boundaries to consider the PG
		end_elem = ( line.tdz->tdz_f.node_extreme_seg || line.tdz->tdz_f.node_extreme_line ) ? line.tdz->tdz_f.n_elements : line.tdz->tdz_f.n_elements - 1;
		for (size_t i = 2, elem_line = (size_t)elem_tdp + 1; i < end_elem; i++, elem_line++)
		{
			add_len = line.tdz->len_elem_tdp * pow(line.tdz->tdz_f.q, ( i - 1 )) + line.tdz->tdz_f.dist_dif_len;
			if (segment_property_vector[line.segments[seg_tdp].GetProperty() - 1].type == 't')
				x0_n[0][elem_line] = cur_len + add_len;
			else
			{
				x0_n[0][2 * elem_line - 1] = cur_len + 0.5 * add_len;
				x0_n[0][2 * elem_line] = cur_len + add_len;
			}
			cur_len += add_len;
		}

		//Last TDZ element
		if (segment_property_vector[line.segments[seg_tdp].GetProperty() - 1].type == 't')
			x0_n[0][line.tdz->tdz_f.elem] = line.tdz->x_f;
		else
		{
			x0_n[0][2 * (size_t)line.tdz->tdz_f.elem - 1] = ( line.tdz->x_f + cur_len ) / 2.0;
			x0_n[0][2 * (size_t)line.tdz->tdz_f.elem] = line.tdz->x_f;
		}
		cur_len = line.tdz->x_f;

		//Until TDZ segment ends
		if (!line.tdz->tdz_f.node_extreme_seg && !line.tdz->tdz_f.node_extreme_line)
		{
			for (size_t i = ( size_t)line.tdz->tdz_f.elem + 1; i <= ( ( size_t )line.tdz->tdz_f.elem + ( size_t )line.tdz->tdz_f.elements_out ); i++)
			{
				if (segment_property_vector[line.segments[seg_tdp].GetProperty() - 1].type == 't')
					x0_n[0][i] = cur_len + line.tdz->tdz_f.len_elem_out;
				else
				{
					x0_n[0][2 * i - 1] = cur_len + line.tdz->tdz_f.len_elem_out / 2.0;
					x0_n[0][2 * i] = cur_len + line.tdz->tdz_f.len_elem_out;
				}
				cur_len += line.tdz->tdz_f.len_elem_out;
			}
		}

		//Segments after TDZ (if they exist)
		if (line.tdz->tdz_f.seg > n_segs - 1)
		{
			for (unsigned int seg = line.tdz->tdz_f.seg + 1; seg < n_segs; seg++)
			{
				div = line.segments[seg].GetDiscretization();
				len = line.segments[seg].GetLength() / div;

				for (size_t i = 1; i <= div; i++)
				{
					if (seg > 0 && i == 1 && n_segs > 1) //Copy last node to the first segment node
						x0_n[seg][0] = cur_len;

					if (segment_property_vector[line.segments[seg].GetProperty() - 1].type == 't')
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
	}

}

//Generates mesh for the current line
void MooringModel::GenerateMesh(Line& line, Matrix& A, Matrix& F, double& Hf, double& Vf)
{
	//Esta função deve gerar todos os nós e elementos da linha de ancoragem a partir das definições da linha e seus segmentos
	
	//Comment (nodes and nodeset)
	char comment[200];

	//Temporary data to create summary of the current line
	std::array<unsigned int, 2> summ_elem = { 0,0 }, summ_nodesets = { 0,0 };


	//total nodes of the current line (it may start negative to disregards nodes between segments)
	unsigned int nodes_line = 1 - static_cast<unsigned int>(line.segments.size()); //here migth happens overflow. It works, but should avoid overflow
	unsigned int init_line; //first node of the current line
	
	static Matrix E3(3);
	static Matrix E1(3);

	//Creating points to represent the anchor (A) and the fairlead (F)
	F(2, 0) = line.hasAnchor == true ? 
		keypoint_vector[static_cast<std::vector<Keypoint, std::allocator<Keypoint>>::size_type>(line.keypoint_A) - 1].GetCoordinate('z') 
		: keypoint_vector[static_cast<std::vector<Keypoint, std::allocator<Keypoint>>::size_type>(line.keypoint_B) - 1].GetCoordinate('z');

	//Generating local coordinate system - for each line a single CS is established
	E1.clear();	E3.clear();
	E1(0, 0) = 0.0;
	E1(1, 0) = 0.0;
	E1(2, 0) = 1.0;
	if (Hf > 0.0)
		E3 = 1.0 / norm(F - A) * ( F - A );
	//If is vertical -> global coordinate system
	else 
	{
		E3(0, 0) = 1.0;
		E3(1, 0) = 0.0;
		E3(2, 0) = 0.0;
	}
	line.cs = cur_cs;
	gm.GenerateCoordinateSystem(cur_cs, E1, E3);


	//Iterates through the segments
	for (size_t seg = 0; seg < line.segments.size(); seg++)
	{
		//Nodesets of the first nodes
		line.nodeset_A = cur_node_set;

		//Count number of nodes to generete line node set
		nodes_line += line.segments[seg].GetNNodes(); 

		char type = segment_property_vector[line.segments[seg].GetProperty() - 1].type;
		int n = (type == 't') ? 1 : 2;
		unsigned int node_x0 = 0;

		//Same rotation (if there is a segment of beam elements between segments of truss elements)
		if (seg > 0)
		{
			if ((segment_property_vector[line.segments[seg - 1].GetProperty() - 1].type == 't' && segment_property_vector[line.segments[seg].GetProperty() - 1].type == 'b' && line.segments.size() >= 2))
				line.transition_nodes.push_back(cur_node_mesh - 1);
		}

		//Generate nodes, nodesets and elements
		for (size_t cur_elem_seg = 1; cur_elem_seg <= line.segments[seg].GetNElements(); cur_elem_seg++)
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
					if (line.hasAnchor)
					{
						//Coincident anchor and start of TDZ
						if (TDZ && line.tdz->tdz_a.node_extreme_line)
							sprintf(comment, "Anchor of line %d and start of TDZ segment", line.number);
						//Just anchor
						else
							sprintf(comment, "Anchor of line %d", line.number);
						
						//Booelan to indicate if the anchor nodeset was found 
						bool nodeset_found = false;

						//Checks if there is different constraint for this anchor
						if (moor_constraint.ExistAnchorConstraint())
						{
							for (AnchorConstraint& anchor : moor_constraint.GetAnchorConstraints())
								if (line.number == anchor.GetNumberID())
								{
									anchor.SetNodeSet(cur_node_set);
									nodeset_found = true;
									break;
								}
						}

						if (!nodeset_found)
							anchor_nodesets.push_front(cur_node_set);
						
						//Monitors
						if (gm.monitor.bool_nodes_anchors)		gm.monitor.nodes.push_front(cur_node_mesh);
						if (gm.monitor.bool_elements_anchors)	gm.monitor.elements.push_front(cur_elem);
					}
					//Two fairleads
					else
					{
						sprintf(comment, "Initial point of line %d", line.number);
						fairlead_nodesets.push_front(cur_node_set);

						//Monitors
						if (gm.monitor.bool_nodes_fairleads)		gm.monitor.nodes.push_front(cur_node_mesh);
						if (gm.monitor.bool_elements_fairleads)		gm.monitor.elements.push_front(cur_elem);
					}	

					//Node and nodeset of anchor
					gm.GenerateNode(cur_node_mesh, A, comment);
					line.node_A = cur_node_mesh;
					gm.GenerateNodeSet(cur_node_set, cur_node_mesh, comment);
					++cur_node_set;

					//Summary list
					summ_elem[0] = cur_elem;
					summ_nodesets[0] = cur_node_set-1;

					init_line = cur_node_mesh++;
					++node_x0;
				}
				else //equal the last node of the last segment
					++node_x0;
			}
			//Fairlead node
			if (seg == ( line.segments.size() - 1 ) && cur_elem_seg == ( size_t )line.segments[seg].GetNElements())
			{
				bool_gen_node_comment = true;

				//With an anchor
				if (line.hasAnchor)
				{
					//Coincident fairlead and end of TDZ
					if (TDZ && line.tdz->tdz_f.node_extreme_line)
						sprintf(comment, "Fairlead of line %d and end of TDZ segment", line.number);
					//Just fairlead
					else
						sprintf(comment, "Fairlead of line %d", line.number);
				}
				else //Second fairlead
				{
					//Coincident fairlead and end of TDZ
					if (TDZ && line.tdz->tdz_f.node_extreme_line)
						sprintf(comment, "End point of line %d and TDZ segment", line.number);
					//Just fairlead
					else
						sprintf(comment, "End point of line %d", line.number);
				}

				//Node and nodeset of fairlead
				line.node_B = cur_node_mesh + n - 1;
				gm.GenerateNodeSet(cur_node_set, cur_node_mesh + n - 1, comment);
				fairlead_nodesets.push_front(cur_node_set);
				++cur_node_set;

				//Monitors
				if (gm.monitor.bool_nodes_fairleads)		gm.monitor.nodes.push_front(cur_node_mesh + n - 1);
				if (gm.monitor.bool_elements_fairleads)		gm.monitor.elements.push_front(cur_elem);

				//Summary list
				summ_elem[1] = cur_elem;
				summ_nodesets[1] = cur_node_set - 1;
			}
			//TDZ nodes
			if (seg == seg_tdp && TDZ)
			{
				if (cur_elem == line.tdz->tdz_a.elem - 1)
				{
					bool_gen_node_comment = true;
					sprintf(comment, "Touchdown zone start of the line %d", line.number);
				}
				if (cur_elem == line.tdz->tdz_f.elem)
				{
					bool_gen_node_comment = true;
					sprintf(comment, "Touchdown zone end of the line %d", line.number);
				}
				
				//Monitors
				if (gm.monitor.bool_nodes_tdz && (cur_elem == line.tdz->tdz_a.elem - 1 || cur_elem == line.tdz->tdz_f.elem - 1 || cur_elem == elem_tdp - 1))
					gm.monitor.nodes.push_front(cur_node_mesh + n - 1);
				if (gm.monitor.bool_elements_tdz && (cur_elem == line.tdz->tdz_a.elem - 1 || cur_elem == line.tdz->tdz_f.elem - 1 || cur_elem == elem_tdp - 1))
					gm.monitor.elements.push_front(cur_node_mesh + n - 1);
				
				//Summary list

				/// TODO: insert nodes into the table in the summary file, between anchor and fairlead data
 
			}

			//Generate other(s) element node(s) and update node lists
			if (type == 't')
			{
				if (bool_gen_node_comment)
					gm.GenerateNode(cur_node_mesh, A + E3 * x0_n[seg][node_x0], comment);
				else
					gm.GenerateNode(cur_node_mesh, A + E3 * x0_n[seg][node_x0]);
				++cur_node_mesh;
				++node_x0;
			}
			else if (type == 'b')
			{
				for (int cont = 1; cont <= 2; cont++)
				{
					if (bool_gen_node_comment && cont == 2)
						gm.GenerateNode(cur_node_mesh, A + E3 * x0_n[seg][node_x0], comment);
					else
						gm.GenerateNode(cur_node_mesh, A + E3 * x0_n[seg][node_x0]);
					++cur_node_mesh;
					++node_x0;
				}
			}

			//Generate elements
			if (type == 't')
				gm.GenerateTrussElement(cur_elem, bool_first_element, line.segments[seg].GetProperty(), cur_node_mesh - 2, cur_node_mesh - 1);
			else //type == 'b'
				gm.GeneratePipeElement(cur_elem, bool_first_element, line.segments[seg].GetProperty(), cur_cs, cur_node_mesh - 3, cur_node_mesh - 2, cur_node_mesh - 1);
			++cur_elem;
		}	
	}

	//Nodesets of the last nodes
	line.nodeset_B = cur_node_set - 1;

	//Summary file
	Summary::AddLine({ line.node_A, line.node_B }, summ_elem, summ_nodesets, extrem_tensions, 
					 line.number, line.configuration, existTDP, x_tdp_ext, line.total_length, ( unsigned int )line.segments.size());

	//Mooring line NodeSet
	sprintf(comment, "Nodes of line %d", line.number);
	gm.GenerateNodeSet(cur_node_set, nodes_line, init_line, 1, comment);
	++cur_node_set;
	++cur_cs;
}

void MooringModel::GenerateCatenaryDisplacement(Line& line, const unsigned int& n_segs, Matrix& F, std::vector <double>& FV, unsigned int& cur_node, 
												std::vector<std::vector<double>>& xcat_n, std::vector<std::vector<double>>& zcat_n, std::vector<std::vector<double>>& roty_n)
{
	double sum_len = 0.0;
	for (unsigned int seg = 0; seg < n_segs; seg++)
	{
		double EA_n = segment_property_vector[line.segments[seg].GetProperty() - 1].EA;

		for (unsigned int node = 0; node < line.segments[seg].GetNNodes(); node++)
		{
			if (seg > 0 && node == 0)
				sum_len += line.segments[seg - 1].GetLength();

			double prev_xcat = 0.0, prev_zcat = 0.0;
			if (seg > 0)
			{
				prev_xcat = xcat_n[seg - 1][line.segments[seg - 1].GetNNodes() - 1];
				prev_zcat = zcat_n[seg - 1][line.segments[seg - 1].GetNNodes() - 1];
			}

			double s = x0_n[seg][node];
			double s_ext = prev_xcat + ( s - sum_len ) * ( 1.0 + F(0, 0) / EA_n );
			double FV_s = 0.0;

			if (s_ext > x_tdp_ext)
			{
				if (seg == seg_tdp)
					FV_s = FV[seg] + line.gamma_s[seg] * ( s - x_tdp );
				else
					FV_s = FV[seg] + line.gamma_s[seg] * ( s - sum_len );
			}

			if (node == 0 && seg == 0)
			{
				xcat_n[seg][node] = zcat_n[seg][node] = 0.0;
				roty_n[seg][node] = -atan(FV[seg] / F(0, 0));
			}
			else
			{
				xcat_n[seg][node] = prev_xcat + ( s - sum_len ) * ( 1.0 + F(0, 0) / EA_n ) - ( FV_s - FV[seg] ) / line.gamma_s[seg] + F(0, 0) / line.gamma_s[seg] * ( log(( FV_s + sqrt(pow(FV_s, 2) + pow(F(0, 0), 2)) ) / F(0, 0)) - log(( FV[seg] + sqrt(pow(FV[seg], 2) + pow(F(0, 0), 2)) ) / F(0, 0)) );
				zcat_n[seg][node] = prev_zcat + 1.0 / line.gamma_s[seg] * ( sqrt(pow(FV_s, 2) + pow(F(0, 0), 2)) - sqrt(pow(FV[seg], 2) + pow(F(0, 0), 2)) ) + 1.0 / ( 2.0 * line.gamma_s[seg] * EA_n ) * ( pow(FV_s, 2) - pow(FV[seg], 2) );
				roty_n[seg][node] = -atan(FV_s / F(0, 0));
			}
		}
	}

	gm.GenerateDisplacementField(++cur_disp, line.cs, 2); 

	//Inserts current displacement field in the displacement vector
	for (unsigned int seg = 0; seg < x0_n.size(); seg++)
	{
		unsigned int node_init = ( seg > 0 ) ? 1 : 0;
		for (unsigned int node = node_init; node < line.segments[seg].GetNNodes(); node++)
		{
			std::array<double, 6> disp = { zcat_n[seg][node], 0.0, xcat_n[seg][node] - x0_n[seg][node],
				0.0, -roty_n[seg][node], 0.0 };
			static_cast< DisplacementField* >( gm.displacement_vector[cur_disp - 1] )->InsertDisplacement(++cur_node, disp);
		}
	}

	//Updates the fairlead rotation
	size_t seg_rot = x0_n.size() - 1;
	size_t node_rot = line.segments[seg_rot].GetNNodes() - 1;
	if (roty_n[seg_rot][node_rot] < rot_fairlead)
		rot_fairlead = -roty_n[seg_rot][node_rot];
}

void MooringModel::CheckDummyElements()
{
	char comment[200];
	//BoolTable
	BoolTable bool_t;
	bool_t.Clear();

	//Check if dummy elements are required and create them
	unsigned int dummy_element = 1;		//count dummy elements
	Matrix dummy_nodes(3, 1);	//matrix to generate nodes  
	double dummy_z = environment.GetWaterDepth(); //depth -> dummy elements are generated under the seabead
	
	for (Line& line : line_vector)
	{
		if (line.segments.size() > 1)
		{
			unsigned int seg_size_init = static_cast<unsigned int>(segment_property_vector.size()); //properties before create dummy elements properties
			for (unsigned int seg = 1; seg < line.segments.size(); seg++)
			{
				if (segment_property_vector[line.segments[seg - 1].GetProperty() - 1].type == 't' && 
					segment_property_vector[line.segments[seg].GetProperty() - 1].type == 'b' && line.segments.size() >= 2)
				{
					//Create dummy element properties
					if (segment_property_vector.size() == seg_size_init)
					{
						//segment_property_vector.emplace_back(SegmentProperty(seg_size_init + 1, 'b', 1.0, 0.0, 0.0, 1.0, 100.0, 1.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.5, 1.0);
						gm.pipe_section_vector.emplace_back(PipeSection(seg_size_init + 1, 'b', 1., 0.,1.,100.,1.,1.,0.,0.,0.,0.,1.,0.5));
					}
	
					//Create dummy element nodes
					for (int i = 1; i < 4; i++)
					{
						dummy_nodes(0, 0) = 0;
						dummy_nodes(1, 0) = 0;
						dummy_nodes(2, 0) = dummy_z;
						--dummy_z;
						if (i == 1)
						{
							sprintf(comment, "Dummy element %d", dummy_element);
							gm.GenerateNode(cur_node_mesh, dummy_nodes, comment);
						}
						else
							gm.GenerateNode(cur_node_mesh, dummy_nodes);
						++cur_node_mesh;
						dummy_nodes.clear();
					}
	
					//Create dummy element node set
					sprintf(comment, "Dummy element %d", dummy_element);
					gm.GenerateNodeSet(cur_node_set, cur_node_mesh - 3, comment);
					bool_t.Set(1, true);
	
					//Create dummy element under the seabed
					gm.GeneratePipeElement(cur_elem, false, (int)segment_property_vector.size(), 1, cur_node_mesh - 1, cur_node_mesh - 2, cur_node_mesh - 3);
					++cur_elem;
					++dummy_element;
	
					//Create same rotation constraint
					bool_t.Set(1, true);
					gm.GenerateSameRotation(++cur_special_constraint, cur_node_mesh - 1, line_vector[cur_line].transition_nodes[dummy_element - 2], bool_t);
					
					//Dummy element - fixed
					BoolTable UX, UY, UZ, ROTX, ROTY, ROTZ;
					UX.Set(1, true);
					UY.Set(1, true);
					UZ.Set(1, true);
					ROTX.Set(1, true);
					ROTY.Set(1, true);
					ROTZ.Set(1, true);
	
					gm.GenerateNodalConstraint(++cur_constraint, cur_node_set, UX, UY, UZ, ROTX, ROTY, ROTZ);
					++cur_node_set;
				}
			}
		}
	}
}

void MooringModel::GenerateContact()
{
	//After generate all line nodes, generate vessel and dummy elements nodes, elements and constraints, 
	 //must create a nodeset and the contact surface (lines-seabed)

	//BoolTable
	BoolTable bool_t;
	bool_t.Clear();

	//Generating NodeSet (will be used to establish contact model afterwards)
	node_set_contact = cur_node_set++;
	gm.GenerateNodeSet(node_set_contact, cur_node_mesh - 1, 1, 1, "Nodes to establish contact model");
}


void MooringModel::GenerateDynamicRelaxation()
{
	//Dynamic relaxation parameters
	double q = 0.0, L_s = 0.0, m_a = 0.0, m_m = 0.0;
	const double zeta = log(1.0 / moorsolution.decrement) / ( sqrt(4.0 * pow(PI, 2.0) + log(1.0 / moorsolution.decrement)) );

	//Data to calculates natural frequency and alpha
	for (size_t line = 0; line < line_vector.size(); line++)
	{
		double temp_ma = environment.GetRhoFluid() * area_eq[line];
		if (temp_ma > m_a)
		{
			m_a = environment.GetRhoFluid() * area_eq[line];
			m_m = rho_eq[line];
			q = ( m_m - m_a ) * g;
		}

		//Suspended length
		double temp_Ls = line_vector[line].total_length - x_tdp;
		if (temp_Ls > L_s)	L_s = temp_Ls;
	}
	
	// Calculate parameters
	double fi = 8.25 - 11.42 * rot_fairlead + 8.56 * pow(rot_fairlead, 2) - 2.53 * pow(rot_fairlead, 3);
	double w_n = fi * sqrt(q / ( ( m_m + m_a ) * L_s ));
	double a_relax = zeta * 2.0 * w_n;
	moorsolution.alpha_relax = a_relax;
	unsigned int T_s = static_cast< unsigned int >( ceil(2.0 * PI / w_n * zeta) );
	moorsolution.TimeRelax = T_s;
}

inline bool MooringModel::Look4SharedLine()
{
	for (Line& line : line_vector)
	{
		if (line.isShared)
			return true;
		else
			return false;
	}
	return false;
}

//Generates vessel (node, element, nodeset and fairleads coupling)
void MooringModel::GenerateVessel()
{
	char comment[250];
	
	for (Vessel& vessel : vessel_vector)
	{
		unsigned int keypoint = vessel.GetKeypoint() - 1;
		unsigned int num = vessel.GetNumber();
		//Array with vessel coordinates
		std::array<double, 3> vessel_coord{ keypoint_vector[keypoint].GetCoordinate('x'), 
			keypoint_vector[keypoint].GetCoordinate('y'), keypoint_vector[keypoint].GetCoordinate('z') };

		sprintf(comment, "Vessel number %d", num);
		//Node
		gm.GenerateNode(cur_node_mesh, vessel_coord, comment);
		vessel.SetNode(cur_node_mesh);

		//Node Set (vessel)
		vessel.SetNodeset(cur_node_set);
		gm.GenerateNodeSet(vessel.GetNodeset(), cur_node_mesh, comment);
		++cur_node_set;

		//Vessel element (if there is no Platform object)
		if (platform_vector.empty())
		{
			//Check CAD name for the current vessel
			auto it_cad = std::find_if(gm.post.cads_vector.begin(), gm.post.cads_vector.end(),
									  [&](CADData& cadData) { return cadData.GetNumber() == ( size_t )num; });
			it_cad._Ptr ? gm.GenerateRigidBodyData(++cur_rbdata, vessel.GetMass(), vessel.GetInertiaTensor(), vessel_coord, it_cad->GetNumber(), std::string("Vessel of platform number ") + std::to_string(num))
				: gm.GenerateRigidBodyData(++cur_rbdata, vessel.GetMass(), vessel.GetInertiaTensor(), vessel_coord);
			
			
			//Rigid body element
			vessel.SetElement(cur_elem);
			gm.GenerateRigidBodyElement(cur_elem++, cur_rbdata, 1, cur_node_mesh++);

			//Coupling fairleads to vessel -> SameDisplacement (GIRAFFE special constraint)
			BoolTable bool_t(false, 2);

			//Searchs for the first line with the current vessel
			auto it = std::find(line_vector.begin(), line_vector.end(), num);
			while (it != line_vector.end() && it->vessel == num)
			{
				vessel.AddNode2RigidNodeset(cur_node_mesh);
				gm.GenerateNode(cur_node_mesh, keypoint_vector[it->keypoint_B - 1].GetCoordinate('x'), 
								keypoint_vector[it->keypoint_B - 1].GetCoordinate('y'), 
								keypoint_vector[it->keypoint_B - 1].GetCoordinate('z'));
				gm.GenerateSameDisplacement(++cur_special_constraint, cur_node_mesh++, it->node_B, bool_t);
				
				++it;
			}
			vessel.SetRigidNodeset(cur_node_set++);
			
		}
		//If at least "Platform" object have been defined
		else
		{
			for (Platform& platform : platform_vector)
			{
				//Nodes and elements of the lines must be generated before the vessel
				platform.GenerateCSNodesElements(cur_node_mesh, cur_elem, cur_cs, segment_property_vector);

				//Same displacement(s)
				platform.FairleadsConnections(cur_special_constraint, line_vector);

			}
		}

		//Monitor Vessel
		if ( gm.monitor.bool_nodes_vessel )
			gm.monitor.nodes.push_front(vessel.GetNode());
		if ( gm.monitor.bool_elements_vessel )
			gm.monitor.elements.push_front(vessel.GetElement());
	}

}

void MooringModel::GenerateRigidNodeSets()
{
	char comment[150];
	BoolTable bool_t(false, 2);

	/*If exist shared line(s), must check if the fairleads
		must be included to some rigid node set */
	if (existSharedLine)
		IncludeSharedLinesFaileads(bool_t);

	//Generate rigid nodesets
	if (platform_vector.empty())
	{
		bool_t.Set(1, true);
		for (Vessel& vessel : vessel_vector)
		{
			sprintf(comment, "Vessel Rigid Node Set");
			gm.GenerateNodeSet(vessel.GetRigidNodeset(), vessel.GetNodesRigidNodeset(), comment);
			gm.GenerateRigidNodeSet(++cur_special_constraint, vessel.GetNode(), vessel.GetRigidNodeset(), bool_t);
		}
	}
	else
	{
		for (Platform& platform : platform_vector)
			platform.VesselRigidNodeset(cur_node_set, cur_special_constraint, vessel_vector);
	}
}

void MooringModel::IncludeSharedLinesFaileads(BoolTable& bool_t)
{
	auto line_it = std::find(line_vector.begin(), line_vector.end(), 0);
	//Iterates through the shared lines
	while (line_it != line_vector.end() && line_it->isShared)
	{
		//Check if the extremities nodes is already in some rigid nodeset
		for (Vessel& vessel : vessel_vector)
		{
			auto& rigid_NS = vessel.GetNodesRigidNodeset();

			char comment[150];

			//First node												**not found**
			if (std::find(rigid_NS.begin(), rigid_NS.end(), line_it->node_A) == rigid_NS.end())
			{
				//Check if must be included
				if (line_it->vesselIDs[0] == vessel.GetNode())
				{
					rigid_NS.emplace(cur_node_mesh); //Include to vessel rigid nodeset

					sprintf(comment, "Node to couple line %d and vessel %d", line_it->number, vessel.GetNumber());

					gm.GenerateNode(cur_node_mesh, keypoint_vector[line_it->keypoint_A - 1].GetCoordinate('x'), 
									keypoint_vector[line_it->keypoint_A - 1].GetCoordinate('y'), 
									keypoint_vector[line_it->keypoint_A - 1].GetCoordinate('z'), comment);
					gm.GenerateSameDisplacement(++cur_special_constraint, cur_node_mesh++, line_it->node_A, bool_t);

					//coupled_nodeA = true;
				}
			}

			//Second node												**not found**
			if (std::find(rigid_NS.begin(), rigid_NS.end(), line_it->node_B) == rigid_NS.end())
			{
				//Check if must be included
				if (line_it->vesselIDs[1] == vessel.GetNumber())
				{
					rigid_NS.emplace(cur_node_mesh); //Include to vessel rigid nodeset

					sprintf(comment, "Node to couple line %d and vessel %d", line_it->number, vessel.GetNumber());

					gm.GenerateNode(cur_node_mesh, keypoint_vector[line_it->keypoint_B - 1].GetCoordinate('x'), 
									keypoint_vector[line_it->keypoint_B - 1].GetCoordinate('y'), 
									keypoint_vector[line_it->keypoint_B - 1].GetCoordinate('z'), comment);
					gm.GenerateSameDisplacement(++cur_special_constraint, cur_node_mesh++, line_it->node_B, bool_t);

					//coupled_nodeB = true;
				}
			}
		} //end for (vessel_vector)
		++line_it;
	} //end while (line_vector)
}

//Setting analysis general data
void MooringModel::GeneralSetting()
{
	/*============================*
	 * Post processing parameters *
	 *============================*/

	//If there is just one line, do not write rigid member coupling fairlead and vessel
	gm.post.write = { moorpost.write.mesh_flag, moorpost.write.renderMesh_flag, moorpost.write.rigidContactSurfaces_flag,
			moorpost.write.flexibleContactSurfaces_flag, moorpost.write.constraints_flag, moorpost.write.forces_flag,
			moorpost.write.specialConstraints_flag, moorpost.write.contactForces_flag, moorpost.write.renderParticles_flag, moorpost.write.renderRigidBodies_flag};

	//Monitor nodes
	for (Monitor::SequenceNodes& seq : gm.monitor.seq_nodes)
	{
		unsigned int temp = seq.begin;
		for (unsigned int cont = 0; cont < seq.nodes; ++cont)
		{
			gm.monitor.nodes.emplace_front(temp);
			temp += seq.increment;
		}
	}
	gm.monitor.nodes.sort();
	gm.monitor.nodes.unique();

	//Monitor elements
	for (Monitor::SequenceElements& seq : gm.monitor.seq_elements)
	{
		unsigned int temp = seq.begin;
		for (unsigned int cont = 0; cont < seq.elements; ++cont)
		{
			gm.monitor.elements.emplace_front(temp);
			temp += seq.increment;
		}
	}
	gm.monitor.elements.sort();
	gm.monitor.elements.unique();

	//Monitor contact
	if (gm.monitor.bool_contact_seabed_moor)	gm.monitor.contacts.push_front(1);


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
	if (!vessel_disp_vector.empty()) 
		GenerateVesselDisplacements();

	//Generate forces
	if (!moorload_vector.empty())	
		GenerateForces();
	
	//Generate displacement fields (harmonic)
	if (!disp_field_vector.empty())	
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

	//Time step when sea current will be included
	int seacurrent_booltable = 2;

	//Coupling fairlead(s)
	if (moorsolution.bool_DynamicRelax)
	{
		seacurrent_booltable += 2;

		//Dynamic relaxation
		gm.GenerateDynamicSolutionStep(++step, start, start + ( double )moorsolution.TimeRelax * ( double )moorsolution.dyn_relax_periods, 0.01, 0.1, 0.0000001, 15, 3, 4, 2, 1000000, moorsolution.alpha_relax, 0.0, 0, 0.6, 0.3);
		Summary::GetSteps().emplace_back(std::make_tuple(start, start + ( double )moorsolution.TimeRelax * ( double )moorsolution.dyn_relax_periods, "Coupling fairleads during a dynamic relaxation"));
		start += ( double )moorsolution.TimeRelax * ( double )moorsolution.dyn_relax_periods;

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

/*	//Stiffness matrix
	if (stiff_matrix && stiff_matrix->bool_num)
	{
		//Updates counter of steps before sea current
		++seacurrent_booltable;

		gm.GenerateStaticSolutionStep(++step, start, start + 24 * stiff_matrix->time_matrix, stiff_matrix->time_matrix, stiff_matrix->time_matrix, stiff_matrix->time_matrix, 20, 2, 1, 1, 100);
		Summary::Get().steps.emplace_back(std::make_tuple(start, start + 24 * stiff_matrix->time_matrix}] = "Offsets for stiffness matrix calculation";

		//Pointer to the table with displacement
		Table* ptr;

		//Checks if there is only one vessel and its time series has not been allocated yet
	//	if (vessel_vector.size() == 1 && !vessel_vector[cur_vessel].time_series)
	//	{
	//		vessel_vector[cur_vessel].time_series = new Table();
	//		ptr = vessel_vector[cur_vessel].time_series;
	//	}
	//	else
	//	{
	//		stiff_matrix->time_series = new Table();
	//		ptr = stiff_matrix->time_series;
	//	}

		//Include time to establishing sea current
		if (environment.seacurrent_exist)
			ptr->SetLineFront(start + 24 * stiff_matrix->time_matrix + moorsolution.seacurrent_timestep,
				stiff_matrix->disp_init_x, stiff_matrix->disp_init_y, stiff_matrix->disp_init_z, stiff_matrix->rot_init_x, stiff_matrix->rot_init_y, stiff_matrix->rot_init_z);

		//+rotz
		ptr->SetLineFront(start + 24 * stiff_matrix->time_matrix, stiff_matrix->disp_init_x, stiff_matrix->disp_init_y,
			stiff_matrix->disp_init_z, stiff_matrix->rot_init_x, stiff_matrix->rot_init_y, stiff_matrix->rot_init_z);
		ptr->SetLineFront(start + 23 * stiff_matrix->time_matrix, stiff_matrix->disp_init_x, stiff_matrix->disp_init_y,
			stiff_matrix->disp_init_z, stiff_matrix->rot_init_x, stiff_matrix->rot_init_y, stiff_matrix->rot_init_z + stiff_matrix->rot_matrix_z);
		//-rotz
		ptr->SetLineFront(start + 22 * stiff_matrix->time_matrix, stiff_matrix->disp_init_x, stiff_matrix->disp_init_y,
			stiff_matrix->disp_init_z, stiff_matrix->rot_init_x, stiff_matrix->rot_init_y, stiff_matrix->rot_init_z);
		ptr->SetLineFront(start + 21 * stiff_matrix->time_matrix, stiff_matrix->disp_init_x, stiff_matrix->disp_init_y,
			stiff_matrix->disp_init_z, stiff_matrix->rot_init_x, stiff_matrix->rot_init_y, stiff_matrix->rot_init_z - stiff_matrix->rot_matrix_z);

		//+roty
		ptr->SetLineFront(start + 20 * stiff_matrix->time_matrix, stiff_matrix->disp_init_x, stiff_matrix->disp_init_y,
			stiff_matrix->disp_init_z, stiff_matrix->rot_init_x, stiff_matrix->rot_init_y, stiff_matrix->rot_init_z);
		ptr->SetLineFront(start + 19 * stiff_matrix->time_matrix, stiff_matrix->disp_init_x, stiff_matrix->disp_init_y,
			stiff_matrix->disp_init_z, stiff_matrix->rot_init_x, (stiff_matrix->rot_init_y + stiff_matrix->rot_matrix_y), stiff_matrix->rot_init_z);
		//-roty
		ptr->SetLineFront(start + 18 * stiff_matrix->time_matrix, stiff_matrix->disp_init_x, stiff_matrix->disp_init_y,
			stiff_matrix->disp_init_z, stiff_matrix->rot_init_x, stiff_matrix->rot_init_y, stiff_matrix->rot_init_z);
		ptr->SetLineFront(start + 17 * stiff_matrix->time_matrix, stiff_matrix->disp_init_x, stiff_matrix->disp_init_y,
			stiff_matrix->disp_init_z, stiff_matrix->rot_init_x, (stiff_matrix->rot_init_y - stiff_matrix->rot_matrix_y), stiff_matrix->rot_init_z);

		//+rotx
		ptr->SetLineFront(start + 16 * stiff_matrix->time_matrix, stiff_matrix->disp_init_x, stiff_matrix->disp_init_y,
			stiff_matrix->disp_init_z, stiff_matrix->rot_init_x, stiff_matrix->rot_init_y, stiff_matrix->rot_init_z);
		ptr->SetLineFront(start + 15 * stiff_matrix->time_matrix, stiff_matrix->disp_init_x, stiff_matrix->disp_init_y,
			stiff_matrix->disp_init_z, (stiff_matrix->rot_init_x + stiff_matrix->rot_matrix_x), stiff_matrix->rot_init_y, stiff_matrix->rot_init_z);
		//-rotx
		ptr->SetLineFront(start + 14 * stiff_matrix->time_matrix, stiff_matrix->disp_init_x, stiff_matrix->disp_init_y,
			stiff_matrix->disp_init_z, stiff_matrix->rot_init_x, stiff_matrix->rot_init_y, stiff_matrix->rot_init_z);
		ptr->SetLineFront(start + 13 * stiff_matrix->time_matrix, stiff_matrix->disp_init_x, stiff_matrix->disp_init_y,
			stiff_matrix->disp_init_z, (stiff_matrix->rot_init_x - stiff_matrix->rot_matrix_x), stiff_matrix->rot_init_y, stiff_matrix->rot_init_z);

		//+z
		ptr->SetLineFront(start + 12 * stiff_matrix->time_matrix, stiff_matrix->disp_init_x, stiff_matrix->disp_init_y,
			stiff_matrix->disp_init_z, stiff_matrix->rot_init_x, stiff_matrix->rot_init_y, stiff_matrix->rot_init_z);
		ptr->SetLineFront(start + 11 * stiff_matrix->time_matrix, stiff_matrix->disp_init_x, stiff_matrix->disp_init_y,
			(stiff_matrix->disp_init_z + stiff_matrix->disp_matrix_z), stiff_matrix->rot_init_x, stiff_matrix->rot_init_y, stiff_matrix->rot_init_z);
		//-z
		ptr->SetLineFront(start + 10 * stiff_matrix->time_matrix, stiff_matrix->disp_init_x, stiff_matrix->disp_init_y,
			stiff_matrix->disp_init_z, stiff_matrix->rot_init_x, stiff_matrix->rot_init_y, stiff_matrix->rot_init_z);
		ptr->SetLineFront(start + 9 * stiff_matrix->time_matrix, stiff_matrix->disp_init_x, stiff_matrix->disp_init_y,
			(stiff_matrix->disp_init_z - stiff_matrix->disp_matrix_z), stiff_matrix->rot_init_x, stiff_matrix->rot_init_y, stiff_matrix->rot_init_z);

		//+y
		ptr->SetLineFront(start + 8 * stiff_matrix->time_matrix, stiff_matrix->disp_init_x, stiff_matrix->disp_init_y,
			stiff_matrix->disp_init_z, stiff_matrix->rot_init_x, stiff_matrix->rot_init_y, stiff_matrix->rot_init_z);
		ptr->SetLineFront(start + 7 * stiff_matrix->time_matrix, stiff_matrix->disp_init_x, (stiff_matrix->disp_init_y + stiff_matrix->disp_matrix_y),
			stiff_matrix->disp_init_z, stiff_matrix->rot_init_x, stiff_matrix->rot_init_y, stiff_matrix->rot_init_z);
		//-y
		ptr->SetLineFront(start + 6 * stiff_matrix->time_matrix, stiff_matrix->disp_init_x, stiff_matrix->disp_init_y,
			stiff_matrix->disp_init_z, stiff_matrix->rot_init_x, stiff_matrix->rot_init_y, stiff_matrix->rot_init_z);
		ptr->SetLineFront(start + 5 * stiff_matrix->time_matrix, stiff_matrix->disp_init_x, (stiff_matrix->disp_init_y - stiff_matrix->disp_matrix_y),
			stiff_matrix->disp_init_z, stiff_matrix->rot_init_x, stiff_matrix->rot_init_y, stiff_matrix->rot_init_z);

		//+x
		ptr->SetLineFront(start + 4 * stiff_matrix->time_matrix, stiff_matrix->disp_init_x, stiff_matrix->disp_init_y,
			stiff_matrix->disp_init_z, stiff_matrix->rot_init_x, stiff_matrix->rot_init_y, stiff_matrix->rot_init_z);
		ptr->SetLineFront(start + 3 * stiff_matrix->time_matrix, (stiff_matrix->disp_init_x + stiff_matrix->disp_matrix_x),
			stiff_matrix->disp_init_y, stiff_matrix->disp_init_z, stiff_matrix->rot_init_x, stiff_matrix->rot_init_y, stiff_matrix->rot_init_z);
		//-x
		ptr->SetLineFront(start + 2 * stiff_matrix->time_matrix, stiff_matrix->disp_init_x, stiff_matrix->disp_init_y,
			stiff_matrix->disp_init_z, stiff_matrix->rot_init_x, stiff_matrix->rot_init_y, stiff_matrix->rot_init_z);
		ptr->SetLineFront(start + 1 * stiff_matrix->time_matrix, (stiff_matrix->disp_init_x - stiff_matrix->disp_matrix_x),
			stiff_matrix->disp_init_y, stiff_matrix->disp_init_z, stiff_matrix->rot_init_x, stiff_matrix->rot_init_y, stiff_matrix->rot_init_z);

		//Starting position at the origin of the coordinate system or the new reference position
		ptr->SetLineFront(start, stiff_matrix->disp_init_x, stiff_matrix->disp_init_y, stiff_matrix->disp_init_z, stiff_matrix->rot_init_x, stiff_matrix->rot_init_y, stiff_matrix->rot_init_z);

		//Updates step and time
		start += 24 * stiff_matrix->time_matrix;
		stiff_matrix->stiff_matrix_step = step-1;
	}
*/

	//Platform -> forces releaf
	if (moorsolution.bool_ReleaseForces && !platform_vector.empty())
	{
		//sea current booltable
		seacurrent_booltable += 2;

		//Dynamic relaxation
		gm.GenerateDynamicSolutionStep(++step, start, start + moorsolution.release_timestep, moorsolution.release_timestep, moorsolution.release_timestep, moorsolution.release_timestep / 100.0, 10, 2, 4, 2, 1000000, 0.0, 0.0, 0, 0.6, 0.3);
		Summary::GetSteps().emplace_back(std::make_tuple(start, start + moorsolution.release_timestep, "Releasing platform DOFs dynamically"));
		start += moorsolution.release_timestep;

		//Static step
		gm.GenerateStaticSolutionStep(++step, start, start + 1., 1., 1., 0.00001, 20, 2, 4, 1.5, 100);
		Summary::GetSteps().emplace_back(std::make_tuple(start, start + 1., "Static step after release platform DOFs"));
		start += 1.;
	}

	//Includes sea current
	if (environment.CheckIfExistSeaCurrent())
	{
		//BoolTable
		for (int cont = 0; cont < seacurrent_booltable; cont++)
			gm.environment.GetSeaCurrentBooltable().Push_Back(false);
		gm.environment.GetSeaCurrentBooltable().Push_Back(true);

		//Solution step
		gm.GenerateStaticSolutionStep(++step, start, start + moorsolution.seacurrent_timestep, moorsolution.seacurrent_timestep, moorsolution.seacurrent_max_timestep, moorsolution.seacurrent_min_timestep, 20, 2, 3, 1.5, 100);
		Summary::GetSteps().emplace_back(std::make_tuple(start, start + moorsolution.seacurrent_timestep, "Establishing sea current"));
		start += moorsolution.seacurrent_timestep;
	}
	//Sea current bool table, just for Morison effects
	else
		gm.environment.GetSeaCurrentBooltable().Set(3, false, false, true);

	/*If there is no vessel time series, but offsets for calculate numerical stiffness matrix were defined,
		a displacement block must be created*/
	if (stiff_matrix && stiff_matrix->ExistNumericalStiffMat())
	{
		////With multiples vessels -> displaces the origin node
		//if (!vessel_vector.size())
		//	gm.GenerateNoda_lDisplacement(origem?.disp_step, origem?.nodeset, 1, stiff_matrix->time_series);
		////With a single vessel -> displaces it
		//else
		//	gm.GenerateNodal_Displacement(origem?.disp_step, origem?.nodeset, 1, stiff_matrix->time_series);
	}

	moorsolution.steps_to_set_model = step;
}

void MooringModel::GenerateAnalysisSteps(unsigned int& step, double& start)
{
	//Time increment (solution step total time)
	double dt = 0;

	for (size_t analysis_step = 0; analysis_step < moorsolution.solution_steps.size(); analysis_step++)
	{
		///"global_start" might be used to apply vessel displacements and/or nodal loads
		moorsolution.solution_steps[analysis_step].SetGlobalStart(start);
		dt = moorsolution.solution_steps[analysis_step].GetEndTime();
		
		//Static step
		if (moorsolution.solution_steps[analysis_step].CheckIfIsStatic())
		{
			gm.GenerateStaticSolutionStep(++step, start, start + dt,
										  moorsolution.solution_steps[analysis_step].GetTimestep(),
										  moorsolution.solution_steps[analysis_step].GetMaxTimestep(),
										  moorsolution.solution_steps[analysis_step].GetMinTimestep(), 20, 2, 4, 1.5,
										  moorsolution.solution_steps[analysis_step].GetSample());
			Summary::GetSteps().emplace_back(std::make_tuple(start, start + dt, "Static step"));
		}
		//Dynamic step
		else 
		{
			gm.GenerateDynamicSolutionStep(++step, start, start + dt,
										   moorsolution.solution_steps[analysis_step].GetTimestep(),
										   moorsolution.solution_steps[analysis_step].GetMaxTimestep(),
										   moorsolution.solution_steps[analysis_step].GetMinTimestep(), 15, 3, 2, 1.5,
										   moorsolution.solution_steps[analysis_step].GetSample(), 
										   moorsolution.solution_steps[analysis_step].GetAlpha_ray(),
										   moorsolution.solution_steps[analysis_step].GetBeta_ray(), 0,
										   moorsolution.solution_steps[analysis_step].GetGamma_new(),
										   moorsolution.solution_steps[analysis_step].GetBeta_new());
			Summary::GetSteps().emplace_back(std::make_tuple(start, start + dt, "Dynamic step"));
		}
		//Update initial time
		start += dt;
	}
}

void MooringModel::GenerateVesselDisplacements()
{
	for (VesselDisplacement& disp : vessel_disp_vector)
	{
		//Temporary auxiliary variables
		size_t ID = ( size_t )disp.GetVesselID() - 1;
		unsigned int analysis_step = disp.GetStep() - 1;
		unsigned int global_step = moorsolution.steps_to_set_model + analysis_step;
		double start = moorsolution.solution_steps[analysis_step].GetGlobalStart();

		//Displacement description (vessel number and type of displacement)
		std::string description2add;

		//MathCode
		if (disp.CheckIfIsMathCode())
		{
			auto ptr = disp.GetMathCode();

			//Changes 't0' to real value in the equation(s)
			ptr->SetEquationInitialTime(start);

			//Displacement
			gm.GenerateNodalDisplacement(++cur_disp, vessel_vector[ID].GetNodeset(), 1, ptr);
			description2add = "\n\t\t- Displacement of the vessel " + std::to_string(vessel_vector[ID].GetNumber()) + " with MathCode";
		}
		//External file
		else if (disp.CheckIfIsExternalFile())
		{
			//Displacement
			gm.GenerateNodalDisplacement(++cur_disp, vessel_vector[ID].GetNodeset(), 1, disp.GetFileName(), disp.GetFileHeaders(), disp.GetFileNTimes());
			description2add = "\n\t\t- Displacement of the vessel " + std::to_string(vessel_vector[ID].GetNumber()) + 
				" with data from file \"" + disp.GetFileName() + "\"";
		}
		//Time series
		else if (disp.CheckIfIsTable())
		{
			auto time_series = disp.GetTimeSeries();

			//Push a line with zeros in front of the table (initial position)
			if (stiff_matrix && !stiff_matrix->ExistNumericalStiffMat())
				time_series->SetLineFront(start, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);

			//Row of the table that starts to increment to match with Giraffe time
			size_t i = 0;

			//With stiffness matrix offsets
			if (stiff_matrix && stiff_matrix->ExistNumericalStiffMat())
				i = environment.CheckIfExistSeaCurrent() ? 26 : 25;
			//Without stiffness matrix offsets
			else if (!stiff_matrix || ( stiff_matrix && !stiff_matrix->ExistNumericalStiffMat() ))
				i = 1;

			for (; i < time_series->table.size(); i++)
				time_series->table[i][0] += start;

			//Generate displacement
			gm.GenerateNodalDisplacement(++cur_disp, vessel_vector[ID].GetNodeset(), 1, time_series);
			description2add = "\n\t\t- Applying time series to vessel " + std::to_string(vessel_vector[ID].GetNumber());
		}
		//Sine Wave
		else if (disp.CheckIfIsSineWave())
		{
			auto ptr = disp.GetSineWave();

			//Setting start time (mean drift or time series)
			ptr->SetStartTime(start);

			//Displacement
			gm.GenerateNodalDisplacement(++cur_disp, vessel_vector[ID].GetNodeset(), 1, ptr);
			description2add = "\n\t\t- Start of sinusoidal displacement with MathCode on vessel " + std::to_string(vessel_vector[ID].GetNumber());

			//Generates equations
			ptr->GenerateMathCode();
		}
		//Append description of the current step (after 'dynamic' or 'static' description)
		std::get<2>(Summary::GetSteps()[global_step]) += description2add;
	}
}

//Generate applied forces
void MooringModel::GenerateForces()
{
	for (MoorLoad& load : moorload_vector)
	{
		//Temporary auxiliary variables
		unsigned int analysis_step = load.GetStep() - 1;
		unsigned int global_step = moorsolution.steps_to_set_model + analysis_step;
		double start = moorsolution.solution_steps[analysis_step].GetGlobalStart();
		size_t line = load.GetLineID() - 1;
		unsigned int node = load.GetNodeID() - 1;
		unsigned int nodeset;
		unsigned int segID = load.GetSegmentID();

		//Updates load number
		++cur_load;

		//Displacement description (vessel number and type of displacement)
		std::string description2add = "\n\t\t- Applying load at ";

		//Vessel node
		if (load.GetDescription() == "vessel")
		{
			nodeset = vessel_vector[node].GetNodeset();
			description2add += "vessel " + std::to_string(vessel_vector[node].GetNumber());
		}
		//First node of a line
		else if (load.GetDescription() == "first" && segID == 1)
		{
			nodeset = line_vector[line].nodeset_A;
			description2add += "the first node of the line " + std::to_string(load.GetLineID());
		}
		//Last node of a line
		else if (load.GetDescription() == "last" && segID == line_vector[line].segments.size())
		{
			nodeset = line_vector[line].nodeset_B;
			description2add += "the last node of the line " + std::to_string(load.GetLineID());
		}
		// If is not a vessel or fairlead node, a new nodeset must be created
		else
		{
			unsigned int temp_node = line_vector[line].node_A - 1; //first node
			unsigned int add_nodes;

			for (unsigned int seg = 0; seg < segID; ++seg)
			{
				unsigned int nodes_seg = line_vector[line].segments[seg].GetNNodes();
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
						add_nodes = load.GetNodeID();
				}
				//Is not this segment yet
				else
					add_nodes = nodes_seg;

				temp_node += add_nodes; //Before exclude transition nodes (they may have been counted twice)
			}

			//Exclude nodes of transition between segments of the count
			temp_node -= ( unsigned int )line_vector[line].segments.size() - 1;

			//Node set
			char comment[500];
			nodeset = ++cur_node_set;
			sprintf(comment, "Nodeset to apply the nodal force number %d", cur_load);
			gm.GenerateNodeSet(nodeset, temp_node, comment);
		}

		//Matching start time with Giraffe time
		if (load.GetMathCode())
		{
			load.GetMathCode()->SetEquationInitialTime(start);
			gm.GenerateNodalForce(cur_load, nodeset, load.GetMathCode());
			description2add += " with MathCode";
		}
		else if (load.GetFileOption())
		{
			gm.GenerateNodalForce(cur_load, nodeset, load.GetFileName(), load.GetHeaderLines(), load.GetNTimes());
			description2add += " with data from file \"" + std::string(load.GetFileName()) + "\"";
		}
		else //Time series table
		{
			for (int i = 0; i < ( int )load.GetTable()->GetLines(); i++)
				load.GetTable()->table[i][0] += start;

			gm.GenerateNodalForce(cur_load, nodeset, load.GetTable());
			description2add += " with time series data";
		}

		//Append description of the current step (after 'dynamic' or 'static' description)
		std::get<2>(Summary::GetSteps()[global_step]) += description2add;
	}
}

void MooringModel::GenerateDisplacementFields()
{
	for (LineDisplacementField& disp_field : disp_field_vector)
	{
		//Temporary auxiliary variables
		unsigned int analysis_step = disp_field.GetStep() - 1;
		unsigned int global_step = moorsolution.steps_to_set_model + analysis_step;
		
		//Pointer to the current line
		Line* line = &line_vector[disp_field.GetNumber() - 1];
		
		//Displacement description (vessel number and type of displacement)
		std::string description2add = std::string("\n\t\t- Applying harmonic displacement field at the line number ") + std::to_string(line->number);

		//Generate harmonic displacement field for the current line
		gm.GenerateDisplacementField(++cur_disp, line->cs, global_step + 1, line->tot_nodes);

		unsigned int global_node = line->node_A;
		for (size_t seg = 0; seg < line->segments.size(); ++seg)
		{
			size_t seg_first_node = seg == 0 ? 1 : 0;
			size_t seg_last_node = line->segments[seg].GetNNodes() - 1;

			for (size_t node = seg_first_node; node < seg_last_node; ++node)
				static_cast< DisplacementField* >( gm.displacement_vector[cur_disp - 1] )->InsertDisplacement(
					++global_node,
					std::array{ 0.0,
					-disp_field.GetAmplitude() * std::sin(x0_n[seg][node] * PI / line->total_length * disp_field.GetMode()),
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

	for (const Line& moor : line_vector)
	{
		//Keypoints ID
		size_t pointA = ( size_t )moor.keypoint_A - 1;
		size_t pointB = ( size_t )moor.keypoint_B - 1;

		//Check X (min e max)
		if (keypoint_vector[pointA].GetCoordinate('x') < xmin)	xmin = keypoint_vector[pointA].GetCoordinate('x');
		if (keypoint_vector[pointB].GetCoordinate('x') < xmin)	xmin = keypoint_vector[pointB].GetCoordinate('x');
		if (keypoint_vector[pointA].GetCoordinate('x') > xmax)	xmax = keypoint_vector[pointA].GetCoordinate('x');
		if (keypoint_vector[pointB].GetCoordinate('x') > xmax)	xmax = keypoint_vector[pointB].GetCoordinate('x');

		//Check Y (min e max)
		if (keypoint_vector[pointA].GetCoordinate('y') < ymin)	ymin = keypoint_vector[pointA].GetCoordinate('y');
		if (keypoint_vector[pointB].GetCoordinate('y') < ymin)	ymin = keypoint_vector[pointB].GetCoordinate('y');
		if (keypoint_vector[pointA].GetCoordinate('y') > ymax)	ymax = keypoint_vector[pointA].GetCoordinate('y');
		if (keypoint_vector[pointB].GetCoordinate('y') > ymax)	ymax = keypoint_vector[pointB].GetCoordinate('y');
	}

	//Check Vessel keypoint
	for (Vessel& vessel : vessel_vector)
	{
		size_t keypoint = ( size_t )vessel.GetKeypoint() - 1;
		
		//Check X (min e max)
		if (keypoint_vector[keypoint].GetCoordinate('x') < xmin)	xmin = keypoint_vector[keypoint].GetCoordinate('x');
		if (keypoint_vector[keypoint].GetCoordinate('x') > xmax)	xmax = keypoint_vector[keypoint].GetCoordinate('x');

		//Check Y (min e max)
		if (keypoint_vector[keypoint].GetCoordinate('y') < ymin)	ymin = keypoint_vector[keypoint].GetCoordinate('y');
		if (keypoint_vector[keypoint].GetCoordinate('y') > ymax)	ymax = keypoint_vector[keypoint].GetCoordinate('y');
	}

	//Checks for null values and change they for half of water depth
	double depth = environment.GetWaterDepth();
	if (ymin == 0.0)	ymin = -depth / 2.0;
	if (ymax == 0.0)	ymax = depth / 2.0;
	if (xmin == 0.0)	xmin = -depth / 2.0;
	if (xmax == 0.0)	xmax = depth / 2.0;
	
	//Surface size (lambdas)
	double l1 = ceil(2.0 * 1.5 * max(fabs(xmax), fabs(xmin)));
	double l2 = ceil(2.0 * 1.5 * max(fabs(ymax), fabs(ymin)));
	
	//Pinball
	environment.GetSeabed().pinball = (xmax - xmin);
	//Radius to search contact
	environment.GetSeabed().radius = 0.0;

	//Pilot node (seabed)
	std::array<double, 3> pilot_p = { ( xmax + xmin ) / 2.0, ( ymax + ymin ) / 2.0, -depth };
	int pil = (int)gm.node_vector.size() + 1;
	gm.GenerateNode(pil, pilot_p, "Pilot Node (Seabed)");

	//Node Set (seabed)
	pil_node_set = cur_node_set++;
	gm.GenerateNodeSet(pil_node_set, pil, "Seabed");
	environment.GetSeabed().pilot_node = pil;

	//Establishing oscillatory surface
	gm.GenerateOscillatorySurf(1, 0.0, 0.0, 0.0, l1, l2, 0.0, 0.0, 1.0, 1.0, 1, pil);
	gm.GenerateSurfaceSet(1, {1});

	//Contact booltables
	BoolTable bool_c, bool_c2;
	bool_c.Clear();
	bool_c2.Clear();

	//Establishing contact
	if (stiff_matrix && stiff_matrix->ExistNumericalStiffMat() && environment.GetSeabed().mu > 0)
	{
		for (unsigned int step = 1; step < stiff_matrix->GetStep(); step++)
		{
			bool_c.Push_Back(true);
			bool_c2.Push_Back(false);
		}
		bool_c.Push_Back(false);
		bool_c.Push_Back(true);

		bool_c2.Push_Back(true);
		bool_c2.Push_Back(false);

		gm.GenerateNSSSContact(1, node_set_contact, 1, environment.GetSeabed().mu, environment.GetSeabed().stiffness, environment.GetSeabed().damping, environment.GetSeabed().stiffness * 0.1, 0.0, environment.GetSeabed().pinball, environment.GetSeabed().radius, 1, bool_c);
		gm.GenerateNSSSContact(2, node_set_contact, 1, 0.0, environment.GetSeabed().stiffness, environment.GetSeabed().damping, environment.GetSeabed().stiffness * 0.1, 0.0, environment.GetSeabed().pinball, environment.GetSeabed().radius, 1, bool_c2);
	}
	else
	{
		bool_c.Set(1, true);
		gm.GenerateNSSSContact(1, node_set_contact, 1, environment.GetSeabed().mu, environment.GetSeabed().stiffness, environment.GetSeabed().damping, environment.GetSeabed().stiffness * 0.1, 0.0, environment.GetSeabed().pinball, environment.GetSeabed().radius, 1, bool_c);
	}


	//Folder with post files
	std::string surfaces_folder = IO::folder_name + "post/";
	bool VTKseabedOk = false, VTKwaterOk; //indicate if seabed/water surface VTK files were created

	//Creates post files directory and seabed and water surface vtk files
	if ( !std::filesystem::is_directory(surfaces_folder) &&	  ///check if exist
		!std::filesystem::create_directory(surfaces_folder) ) ///if not, try to create it
		Log::AddWarning("\n   + Post files directory could not be created."); ///ERROR
	else
	{
		VTKseabedOk = gm.post.CreateSeabedVTK(surfaces_folder, { 2.0 * xmin, 2.0 * fabs(xmax) }, { 2.0 * ymin, 2.0 * fabs(ymax) }, -environment.GetWaterDepth());
		VTKwaterOk = gm.post.CreateWaterVTK(surfaces_folder, { 2.0 * xmin, 2.0 * fabs(xmax) }, { 2.0 * ymin, 2.0 * fabs(ymax) });
	}

	//Setting contact surface flag
	if (!VTKseabedOk && !gm.post.write.rigidContactSurfaces_flag)
		gm.post.write.rigidContactSurfaces_flag = true;
}

//Generates constraints
void MooringModel::GenerateConstraints()
{
	//Bool tables
	BoolTable U, ROT, ROTZ;
	U.Clear();
	ROT.Clear();

	//Lines (contact)
	U.Set(3, true, true, false);
	ROT.Set(3, true, true, false);
	gm.GenerateNodalConstraint(++cur_constraint, node_set_contact, U, U, U, ROT, ROT, ROT);

	//Anchors
	U.Set(3, true, true, true);
	ROT.Set(2, true, true);
	ROTZ.Set(2, true, false);

	//With different constraint definitions
	if (moor_constraint.ExistAnchorConstraint())
	{
		//First, anchors with different constraints
		for (const AnchorConstraint& anchor : moor_constraint.GetAnchorConstraints())
		{
			//Copies of the booltables for the first steps
			BoolTable ROTX2(ROT), ROTY2(ROT), ROTZ2(ROTZ);

			ROTX2.Push_Back(anchor.GetRot('x'));
			ROTY2.Push_Back(anchor.GetRot('y'));
			ROTZ2.Push_Back(anchor.GetRot('z'));

			gm.GenerateNodalConstraint(++cur_constraint, anchor.GetNodeSet(), U, U, U, ROTX2, ROTY2, ROTZ2);
		}
	}
	//Anchors with default constraints
	ROT.Push_Back(true);
	ROTZ.Push_Back(true);

	for (const unsigned int& nodeset : anchor_nodesets)
		gm.GenerateNodalConstraint(++cur_constraint, nodeset, U, U, U, ROT, ROT, ROTZ);


	//Fairleads
	U.Set(4, true, true, true, false);
	ROT.Set(4, false, true, true, false);
	for (const unsigned int& nodeset : fairlead_nodesets)
		gm.GenerateNodalConstraint(++cur_constraint, nodeset, U, U, U, ROT, ROT, ROT);

	//Lines
	if ( moor_constraint.ExistLineConstraint() )
	{
		//Default conditions (steps to set the FE model)
		std::list bool_list = {true, true, false};
		//Check for other steps after coupling fairleads
		if ( moorsolution.steps_to_set_model > 3 )
		{
			for ( unsigned int i = 3; i < moorsolution.steps_to_set_model; ++i )
				bool_list.push_back(false);
		}

		for ( LineConstraint& constr : moor_constraint.GetLineConstraints() )
		{
			//Booltables
			std::vector<BoolTable> bt_vec(6);
			std::fill(bt_vec.begin(), bt_vec.end(), bool_list);

			//Booltables
			for ( size_t i = 0; i < 6; i++ )
				bt_vec[i].Multiple_Push_Back(constr.GetDoFConstraints(i));

			gm.GenerateNodalConstraint(++cur_constraint, line_vector[constr.GetNumberID() - 1].nodeset_B + 1,
									   bt_vec[0], bt_vec[1], bt_vec[2], bt_vec[3], bt_vec[4], bt_vec[5]);
		}
	}
	else
	{
		for ( LineDisplacementField& disp_field : disp_field_vector )
		{
			BoolTable bool_table;

			//Default conditions (steps to set the FE model)
			std::list bool_list = {true, true, false};
			if ( moorsolution.steps_to_set_model > 3 )
				for ( unsigned int i = 3; i < moorsolution.steps_to_set_model; ++i )
					bool_list.push_back(false);

			//Other steps, until reach the step after the displacement field
			for ( unsigned int i = 1; i <= disp_field.GetStep() + 1; ++i )
				i == disp_field.GetStep() ? bool_list.emplace_back(true) : bool_list.emplace_back(false);
			bool_table.Multiple_Push_Back(bool_list);

			gm.GenerateNodalConstraint(++cur_constraint, line_vector[disp_field.GetNumber() - 1].nodeset_B + 1,
									   bool_table, bool_table, bool_table, bool_table, bool_table, bool_table);
		}
	}

	
	//Vessel
	///Default constraint (all fixed)
	if (!moor_constraint.ExistVesselConstraint())
	{
		//Vessel - fixed
		U.Set(1, true);
		ROT.Set(1, true);
		for (Vessel& vessel : vessel_vector)
			gm.GenerateNodalConstraint(++cur_constraint, vessel.GetNodeset(), U, U, U, ROT, ROT, ROT);
	}
	///Different constraint(s) defined in the input file
	else
	{
		int step0 = 3;

		//If there is a dynamic relaxation step
		if (moorsolution.bool_DynamicRelax)			++step0;
		//If there is a numerical stiffness matrix
		if (stiff_matrix && stiff_matrix->ExistNumericalStiffMat()) ++step0;
		//If there is a sea current 
		if (environment.CheckIfExistSeaCurrent())			++step0;

		//Creates booltables
		BoolTable boolX(true, step0, false), boolY(true, step0, false), boolZ(true, step0, false),
			boolROTX(true, step0, false), boolROTY(true, step0, false), boolROTZ(true, step0, false);

		//Platform releasing
		if (moorsolution.bool_ReleaseForces)
		{
			boolX.Push_Back(0);
			boolY.Push_Back(0);
			boolZ.Push_Back(0);
			boolROTX.Push_Back(0);
			boolROTY.Push_Back(0);
			boolROTZ.Push_Back(0);
		}

		//Vessels with constraint defined
		std::unordered_set<unsigned int> constrainted_vessels;

		for (VesselConstraint& constr : moor_constraint.GetVesselConstraints())
		{
			constrainted_vessels.insert(constr.GetNumberID());
			 
			//BoolTables for the current vessel 
			BoolTable vessel_X(boolX), vessel_Y(boolY), vessel_Z(boolZ),
				vessel_ROTX(boolROTX), vessel_ROTY(boolROTY), vessel_ROTZ(boolROTZ);

			//Booltables
			for (size_t i = 0; i < 6; i++)
			{
				auto const& c = constr.GetDoFConstraints(i);
				if (i == 0)			vessel_X.Multiple_Push_Back(c);
				else if (i == 1)	vessel_Y.Multiple_Push_Back(c);
				else if (i == 2)	vessel_Z.Multiple_Push_Back(c);
				else if (i == 3)	vessel_ROTX.Multiple_Push_Back(c);
				else if (i == 4)	vessel_ROTY.Multiple_Push_Back(c);
				else if (i == 5)	vessel_ROTZ.Multiple_Push_Back(c);
			}

			gm.GenerateNodalConstraint(++cur_constraint, vessel_vector[constr.GetNumberID() - 1].GetNodeset(), 
									   vessel_X, vessel_Y, vessel_Z, vessel_ROTX, vessel_ROTY, vessel_ROTZ);
		}

		//Iterate through the vessels while still exist vessels to constraint
		if (constrainted_vessels.size() != vessel_vector.size())
		{
			//Vessel - fixed
			U.Set(1, true);
			ROT.Set(1, true);
			for (Vessel& vessel : vessel_vector)
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
	U.Set(1, true);
	ROT.Set(1, true);
	gm.GenerateNodalConstraint(++cur_constraint, pil_node_set, U, U, U, ROT, ROT, ROT);
}

//Creates platform object(s)
void MooringModel::GeneratePlatform()
{
	for (Platform& platform : platform_vector)
	{
		platform.GenerateRigidBodyElements(cur_elem, cur_node_set, cur_rbdata, cur_special_constraint, cur_constraint);
		platform.GenerateNodeSetsSpecialConstraints(cur_node_set, cur_constraint, cur_special_constraint);
	}
}

//Create segments for lines with 'SegmentSet' defined 
void MooringModel::GenerateSegments()
{
	//Iterates through the lines
	for (Line& line : line_vector)
	{
		if (line.usingSegmentSet)
		{
			//Iterates through the 'LineSegment' objects in 'SegmentSet', 
			//copying it to the 'segments' vector in the current line
			size_t setID = line.segment_set - 1;
			for (size_t i = 0; i < segment_set_vector[setID].GetSegmentSetSize(); ++i)
				line.segments.emplace_back(segment_set_vector[setID].GetSegment(i));
		}
	}
}
