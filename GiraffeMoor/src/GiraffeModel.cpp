#include "PCH.h"
#include "GiraffeModel.h"
#include "Log.h"


GiraffeModel::GiraffeModel()
{
	run_giraffe = false;
}

GiraffeModel::~GiraffeModel()
{
	//Cleaning element_vector
	for (int i = 0; i < (int)element_vector.size(); i++)
		delete[] element_vector[i];
	element_vector.clear();

	//Cleaning special_constraint_vector
	for (int i = 0; i < (int)special_constraint_vector.size(); i++)
		delete[] special_constraint_vector[i];
	special_constraint_vector.clear();

	//Cleaning contact_vector
	for (int i = 0; i < (int)contact_vector.size(); i++)
		delete[] contact_vector[i];
	contact_vector.clear();

	//Cleaning constraint_vector
	for (int i = 0; i < (int)constraint_vector.size(); i++)
		delete[] constraint_vector[i];
	constraint_vector.clear();

	//Cleaning displacement_vector
	for (int i = 0; i < (int)displacement_vector.size(); i++)
		delete[] displacement_vector[i];
	displacement_vector.clear(); 

	//Cleaning solution_vector
	for (int i = 0; i < (int)solution_vector.size(); i++)
		delete[] solution_vector[i];
	solution_vector.clear();

}

void GiraffeModel::GenerateNode(const unsigned int& number, Matrix& pos, const char* comment)
{
	node_vector.emplace_back();
	node_vector.back().number = number;
	node_vector.back().mark_comment = true;
	strcpy(node_vector.back().comment, comment);
	node_vector.back().ref_coordinates[0] = pos(0, 0);
	node_vector.back().ref_coordinates[1] = pos(1, 0);
	node_vector.back().ref_coordinates[2] = pos(2, 0);
}
void GiraffeModel::GenerateNode(const unsigned int& number, Matrix &pos)
{
	node_vector.emplace_back();
	node_vector.back().number = number;
	node_vector.back().mark_comment = false;
	node_vector.back().ref_coordinates[0] = pos(0, 0);
	node_vector.back().ref_coordinates[1] = pos(1, 0);
	node_vector.back().ref_coordinates[2] = pos(2, 0);
}
void GiraffeModel::GenerateNode(const unsigned int& number, const double& X, const double& Y, const double& Z, const char* comment)
{
	node_vector.emplace_back();
	node_vector.back().number = number;
	node_vector.back().mark_comment = true;
	strcpy(node_vector.back().comment, comment);
	node_vector.back().ref_coordinates[0] = X;
	node_vector.back().ref_coordinates[1] = Y;
	node_vector.back().ref_coordinates[2] = Z;
}
void GiraffeModel::GenerateNode(const unsigned int& number, const double& X, const double& Y, const double& Z)
{
	node_vector.emplace_back();
	node_vector.back().number = number;
	node_vector.back().mark_comment = false;
	node_vector.back().ref_coordinates[0] = X;
	node_vector.back().ref_coordinates[1] = Y;
	node_vector.back().ref_coordinates[2] = Z;
}
void GiraffeModel::GenerateNode(const unsigned int& number, const std::array<double,3>& coord, const char* comment)
{
	node_vector.emplace_back();
	node_vector.back().number = number;
	node_vector.back().mark_comment = true;
	strcpy(node_vector.back().comment, comment);
	node_vector.back().ref_coordinates = coord;
}
void GiraffeModel::GenerateNode(const unsigned int& number, const std::array<double, 3>& coord)
{
	node_vector.emplace_back();
	node_vector.back().number = number;
	node_vector.back().mark_comment = false;
	node_vector.back().ref_coordinates = coord;
}
void GiraffeModel::GeneratePoint(const unsigned int& number, Matrix& pos)
{
	point_vector.emplace_back();
	point_vector.back().number = number;
	point_vector.back().coordinates = pos;
}
void GiraffeModel::GenerateTriangle(const unsigned int& number, const unsigned int& point1, const unsigned int& point2, const unsigned int& point3, const unsigned int& pilot_node)
{
	triangle_vector.emplace_back();
	triangle_vector.back().number = number;
	triangle_vector.back().points[0] = point1;
	triangle_vector.back().points[1] = point2;
	triangle_vector.back().points[2] = point3;
	triangle_vector.back().pilot_node = pilot_node;
}
void GiraffeModel::GenerateOscillatorySurf(const unsigned int& number, const double& A1, const double& A2, const double& A12, const double& lambda1, const double& lambda2, const double& phi1, const double& phi2, const double& waves1, const double& waves2, const unsigned int& cs, const unsigned int& pilot_node)
{
	oscillatory_vector.emplace_back();
	oscillatory_vector.back().number = number;
	oscillatory_vector.back().A1 = A1;
	oscillatory_vector.back().A2 = A2;
	oscillatory_vector.back().A12 = A12;
	oscillatory_vector.back().lambda1 = lambda1;
	oscillatory_vector.back().lambda2 = lambda2;
	oscillatory_vector.back().phi1 = phi1;
	oscillatory_vector.back().phi2 = phi2;
	oscillatory_vector.back().waves1 = waves1;
	oscillatory_vector.back().waves2 = waves2;
	oscillatory_vector.back().cs = cs;
	oscillatory_vector.back().pilot_node = pilot_node;
}
void GiraffeModel::GenerateTrussElement(const unsigned int& number, const bool& segment_begin, const unsigned int& section, const unsigned int& node1, const unsigned int& node2)
{
	element_vector.emplace_back(new Truss());
	element_vector.back()->number = number;
	element_vector.back()->mark_segment_begin = segment_begin;
	element_vector.back()->section = section;
	element_vector.back()->nodes[0] = node1;
	element_vector.back()->nodes[1] = node2;
}
void GiraffeModel::GenerateTrussElement(const unsigned int& number, const bool& segment_begin, const unsigned int& section, const unsigned int& node1, const unsigned int& node2, const std::string& comment)
{
	element_vector.emplace_back(new Truss());
	element_vector.back()->number = number;
	element_vector.back()->mark_segment_begin = segment_begin;
	element_vector.back()->section = section;
	element_vector.back()->nodes[0] = node1;
	element_vector.back()->nodes[1] = node2;
	Truss* ptr = static_cast< Truss* >( element_vector.back() );
	ptr->label = comment;
}
void  GiraffeModel::GenerateRigidBodyElement(const unsigned int& number, const unsigned int& RB_data, const unsigned int& cs, const unsigned int& node)
{
	element_vector.emplace_back(new RigidBody());
	element_vector.back()->number = number;
	element_vector.back()->material = RB_data;
	element_vector.back()->cs = cs;
	element_vector.back()->nodes[0] = node;
}
void  GiraffeModel::GenerateRigidBodyElement(const unsigned int& number, const unsigned int& RB_data, const unsigned int& cs, const unsigned int& node, const std::string& comment)
{
	element_vector.emplace_back(new RigidBody());
	element_vector.back()->number = number;
	element_vector.back()->material = RB_data;
	element_vector.back()->cs = cs;
	element_vector.back()->nodes[0] = node;
	RigidBody* ptr = static_cast< RigidBody* >( element_vector.back() );
	ptr->label = comment;
}
void GiraffeModel::GeneratePipeElement(const unsigned int& number, const bool& segment_begin, const unsigned int& section, const unsigned int& cs, const unsigned int& node1, const unsigned int& node2, const unsigned int& node3)
{
	element_vector.emplace_back(new Pipe());
	element_vector.back()->number = number;
	element_vector.back()->mark_segment_begin = segment_begin;
	element_vector.back()->section = section;
	element_vector.back()->cs = cs;
	element_vector.back()->nodes[0] = node1;
	element_vector.back()->nodes[1] = node2;
	element_vector.back()->nodes[2] = node3;
}
void GiraffeModel::GeneratePipeElement(const unsigned int& number, const unsigned int& section, const unsigned int& cs, const unsigned int& node1, const unsigned int& node2, const unsigned int& node3, std::string& comment)
{
	element_vector.emplace_back(new Pipe());
	element_vector.back()->number = number;
	element_vector.back()->mark_segment_begin = false;
	element_vector.back()->section = section;
	element_vector.back()->cs = cs;
	element_vector.back()->nodes[0] = node1;
	element_vector.back()->nodes[1] = node2;
	element_vector.back()->nodes[2] = node3;
	Pipe* ptr = static_cast< Pipe* >( element_vector.back() );
	ptr->label = comment;
}
void GiraffeModel::GenerateCoordinateSystem(unsigned int number, Matrix& E1, Matrix& E3)
{
	cs_vector.emplace_back();// CoordinateSystem());
	cs_vector.back().number = number;
	cs_vector.back().E1[0] = E1(0,0);
	cs_vector.back().E1[1] = E1(1,0);
	cs_vector.back().E1[2] = E1(2,0);
	cs_vector.back().E3[0] = E3(0,0);
	cs_vector.back().E3[1] = E3(1,0);
	cs_vector.back().E3[2] = E3(2,0);
}
void GiraffeModel::GenerateCoordinateSystem(unsigned int number, const std::array<double,3>& E1, const std::array<double, 3>& E3)
{
	cs_vector.emplace_back();// CoordinateSystem());
	cs_vector.back().number = number;
	cs_vector.back().E1 = E1;
	cs_vector.back().E3 = E3;
}
void GiraffeModel::GenerateRigidBodyData(const unsigned int& number, const double& mass, const std::array<double, 6>& J_G, const std::array<double, 3>& G, const std::string& file)
{
	rbdata_vector.emplace_back();
	rbdata_vector.back().number = number;
	rbdata_vector.back().mass = mass;
	rbdata_vector.back().J_G = J_G;
	rbdata_vector.back().G = G;
	rbdata_vector.back().platform_name = file;
}
void GiraffeModel::GenerateRigidBodyData(const unsigned int& number, const double& mass, const std::array<double, 6>& J_G, const std::array<double, 3>& G, const std::string& file, const std::string& comment)
{
	rbdata_vector.emplace_back();
	rbdata_vector.back().number = number;
	rbdata_vector.back().mass = mass;
	rbdata_vector.back().J_G = J_G;
	rbdata_vector.back().G = G;
	rbdata_vector.back().platform_name = file;
	rbdata_vector.back().comment = comment;
}
void GiraffeModel::GenerateNSSSContact(const unsigned int& number, const unsigned int& node_set, const unsigned int& surface_set, const double& mu, const double& epn, const double& cn, const double& ept, const double& ct, const double& pinball, const double& radius, const unsigned int& max_interactions, BoolTable& bool_table)
{
	contact_vector.emplace_back(new NSSS());
	//Pointer to the NSSS Contact
	NSSS* ptr = static_cast<NSSS*>(contact_vector.back());
	ptr->number = number;
	ptr->node_set = node_set;
	ptr->surface_set = surface_set;
	ptr->mu = mu;
	ptr->epn = epn;
	ptr->cn = cn;
	ptr->ept = ept;
	ptr->ct = ct;
	ptr->pinball = pinball;
	ptr->radius = radius;
	ptr->max_interactions = max_interactions;
	ptr->bool_table = bool_table;
}
void GiraffeModel::GenerateRigidNodeSet(const unsigned int& number, const unsigned int& pilot_node, const unsigned int& node_set, BoolTable& bool_table)
{
	special_constraint_vector.emplace_back(new RigidNodeSet());
	//Pointer to the RigidNodeSet
	RigidNodeSet* ptr = static_cast<RigidNodeSet*>(special_constraint_vector.back());
	ptr->number = number;
	ptr->pilot_node = pilot_node;
	ptr->node_set = node_set;
	ptr->bool_table = bool_table;
}
void GiraffeModel::GenerateRigidNodeSet(const unsigned int& number, const unsigned int& pilot_node, const unsigned int& node_set, BoolTable& bool_table, const std::string& comment)
{
	special_constraint_vector.emplace_back(new RigidNodeSet());
	//Pointer to the RigidNodeSet
	RigidNodeSet* ptr = static_cast<RigidNodeSet*>(special_constraint_vector.back());
	ptr->number = number;
	ptr->pilot_node = pilot_node;
	ptr->node_set = node_set;
	ptr->bool_table = bool_table;
	ptr->comment = comment;
}
void GiraffeModel::GenerateSameDisplacement(const unsigned int& number, const unsigned int& node_A, const unsigned int& node_B, BoolTable& bool_table)
{
	special_constraint_vector.emplace_back(new SameDisplacement());
	//Pointer to the SameDisplacement
	SameDisplacement* ptr = static_cast<SameDisplacement*>(special_constraint_vector.back());
	ptr->number = number;
	ptr->node_A = node_A;
	ptr->node_B = node_B;
	ptr->bool_table = bool_table;
}
void GiraffeModel::GenerateSameRotation(const unsigned int& number, const unsigned int& node_A, const unsigned int& node_B, BoolTable& bool_table)
{
	special_constraint_vector.emplace_back(new SameRotation());
	//Pointer to the SameDisplacement
	SameRotation* ptr = static_cast<SameRotation*>(special_constraint_vector.back());
	ptr->number = number;
	ptr->node_A = node_A;
	ptr->node_B = node_B;
	ptr->bool_table = bool_table;
}
void GiraffeModel::GenerateNodalDisplacement(const unsigned int& number, const unsigned int& node_set, const unsigned int& cs, Table* values)
{
	displacement_vector.emplace_back(new NodalDisplacement());
	//displacement_vector.emplace_back(values);
	//Pointer to the NodalDisplacement
	NodalDisplacement* ptr = static_cast<NodalDisplacement*>(displacement_vector.back());
	ptr->number = number;
	ptr->node_set = node_set;
	ptr->cs = cs;
	ptr->table = values;
}
void GiraffeModel::GenerateNodalDisplacement(const unsigned int& number, const unsigned int& node_set, const unsigned int& cs, MathCode* math_code)
{
	displacement_vector.emplace_back(new NodalDisplacement(math_code));
	//displacement_vector.emplace_back(math_code);
	//Pointer to the displacement
	NodalDisplacement* ptr = static_cast< NodalDisplacement*>(displacement_vector.back());
	ptr->number = number;
	ptr->node_set = node_set;
	ptr->cs = cs;
}
void GiraffeModel::GenerateNodalDisplacement(const unsigned int& number, const unsigned int& node_set, const unsigned int& cs, SineWaveDisplacement* wavedisp_ob)
{
	displacement_vector.emplace_back(wavedisp_ob);
	//Pointer to the NodalDisplacement
	SineWaveDisplacement* ptr = static_cast< SineWaveDisplacement* >( displacement_vector.back() );
	ptr->number = number;
	ptr->node_set = node_set;
	ptr->cs = cs;
}
void GiraffeModel::GenerateNodalDisplacement(const unsigned int& number, const unsigned int& node_set, const unsigned int& cs, 
											 const std::string& file_name, const unsigned int& header_lines, const unsigned int& n_times)
{
	displacement_vector.emplace_back(new NodalDisplacement(file_name, header_lines, n_times));
	NodalDisplacement* ptr = static_cast< NodalDisplacement* >( displacement_vector.back() );
	ptr->number = number;
	ptr->node_set = node_set;
	ptr->cs = cs;
}
void GiraffeModel::GenerateDisplacementField(const unsigned int& number, const unsigned int& cs, const unsigned int& solution_step)
{
	displacement_vector.emplace_back(new DisplacementField());
	//Pointer to the DisplacementField
	DisplacementField* ptr = static_cast<DisplacementField*>(displacement_vector.back());
	ptr->number = number;
	ptr->solution_step = solution_step;
	ptr->cs = cs;
}
void GiraffeModel::GenerateNodeSet(const unsigned int& number, std::vector<unsigned int>& list, const char* comment)
{
	node_set_vector.emplace_back(NodeSet());
	node_set_vector.back().number = number;
	node_set_vector.back().nodes.resize(list.size());
	//node_set_vector.back().nodes.reserve(list.size());
	for (int i = 0; i < (int)list.size(); i++)
		node_set_vector.back().nodes[i] = list[i];
	strcpy(node_set_vector.back().comment, comment);
}
void GiraffeModel::GenerateNodeSet(const unsigned int& number, const std::unordered_set<unsigned int>& list, const char* comment)
{
	node_set_vector.emplace_back(NodeSet());
	node_set_vector.back().number = number;
	node_set_vector.back().nodes.resize(list.size());
	//node_set_vector.back().nodes.reserve(list.size());
	size_t i = 0;
	for (const unsigned int& node : list)
	{
		node_set_vector.back().nodes[i] = node; 
		++i;
	}
	strcpy(node_set_vector.back().comment, comment);
}
void GiraffeModel::GenerateNodeSet(const unsigned int& number, const unsigned int& node, const char* comment)
{
	node_set_vector.emplace_back();
	node_set_vector.back().number = number;
	node_set_vector.back().nodes.resize(1);
	//node_set_vector.back().nodes.reserve(1);
	node_set_vector.back().nodes[0] = node;
	strcpy(node_set_vector.back().comment, comment);
}
void GiraffeModel::GenerateNodeSet(const unsigned int& number, const unsigned int& tot_nodes, const unsigned int& node_init, const unsigned int& increment, const char* comment)
{
	node_set_vector.emplace_back(NodeSet(tot_nodes, node_init, increment));
	node_set_vector.back().number = number;
	strcpy(node_set_vector.back().comment, comment);
}
void GiraffeModel::GenerateSurfaceSet(const unsigned int& number, const std::vector<unsigned int>& list)
{
	surface_set_vector.emplace_back(SurfaceSet());
	surface_set_vector.back().number = number;
	surface_set_vector.back().surfaces.resize(list.size());
	//surface_set_vector.back().surfaces.reserve(list.size());
	for (int i = 0; i < (int)list.size(); i++)
		surface_set_vector.back().surfaces[i] = list[i];
}
void GiraffeModel::GenerateStaticSolutionStep(const unsigned int& number, const double& start_time, const double& end_time, const double& i_time_step, const double& max_time_step, const double& min_time_step, const unsigned int& max_it, const unsigned int& min_it, const unsigned int& conv_increase, const double& inc_factor, const unsigned int& sample)
{
	solution_vector.emplace_back(new Static());
	//Pointer to the Static
	Static* ptr = static_cast<Static*>(solution_vector.back());
	ptr->solution_number = number;
	ptr->start_time = start_time;
	ptr->end_time = end_time;
	ptr->i_time_step = i_time_step;
	ptr->max_time_step = max_time_step;
	ptr->min_time_step = min_time_step;
	ptr->max_it = max_it;
	ptr->min_it = min_it;
	ptr->conv_increase = conv_increase;
	ptr->inc_factor = inc_factor;
	ptr->sample = sample;
}
void GiraffeModel::GenerateDynamicSolutionStep(const unsigned int& number, const double& start_time, const double& end_time, const double& i_time_step, const double& max_time_step, const double& min_time_step, const unsigned int& max_it, const unsigned int& min_it, const unsigned int& conv_increase, const double& inc_factor, const unsigned int& sample, const double& alpha, const double& beta, const unsigned int& update, const double& gamma_new, const double& beta_new)
{
	solution_vector.emplace_back(new Dynamic());
	//Pointer to the Dynamic
	Dynamic* ptr = static_cast<Dynamic*>(solution_vector.back());
	ptr->solution_number = number;
	ptr->start_time = start_time;
	ptr->end_time = end_time;
	ptr->i_time_step = i_time_step;
	ptr->max_time_step = max_time_step;
	ptr->min_time_step = min_time_step;
	ptr->max_it = max_it;
	ptr->min_it = min_it;
	ptr->conv_increase = conv_increase;
	ptr->inc_factor = inc_factor;
	ptr->sample = sample;
	ptr->alpha = alpha;
	ptr->beta = beta;
	ptr->update = update;
	ptr->gamma_new = gamma_new;
	ptr->beta_new = beta_new;
}
void GiraffeModel::GenerateNodalForce(const unsigned int& number, const unsigned int& nodeset, Table* time_series)
{
	load_vector.emplace_back(new NodalForce(time_series));
	//Pointer to the NodalForce
	NodalForce* ptr = static_cast< NodalForce* >( load_vector.back() );
	ptr->number = number;
	ptr->nodeset = nodeset;
}
void GiraffeModel::GenerateNodalForce(const unsigned int& number, const unsigned int& nodeset, 
						  const std::string& file_name, const unsigned int& header_lines, const unsigned int& n_times)
{
	load_vector.emplace_back(new NodalForce(file_name, header_lines, n_times));
	//Pointer to the NodalForce
	NodalForce* ptr = static_cast< NodalForce* >( load_vector.back() );
	ptr->number = number;
	ptr->nodeset = nodeset;
}
void GiraffeModel::GenerateNodalForce(const unsigned int& number, const unsigned int& nodeset, MathCode* mathCode)
{
	load_vector.emplace_back(new NodalForce(mathCode));
	//Pointer to the NodalForce
	NodalForce* ptr = static_cast< NodalForce* >( load_vector.back() );
	ptr->number = number;
	ptr->nodeset = nodeset;
}
void GiraffeModel::GenerateNodalConstraint(const unsigned int& number, const unsigned int& node_set, BoolTable& e_UX, BoolTable& e_UY, BoolTable& e_UZ, BoolTable& e_ROTX, BoolTable& e_ROTY, BoolTable& e_ROTZ)
{
	constraint_vector.emplace_back(new NodalConstraint());
	//Pointer to the NodalConstraint
	NodalConstraint* ptr = static_cast<NodalConstraint*>(constraint_vector.back());
	ptr->number = number;
	ptr->node_set = node_set;
	ptr->UX_table = e_UX;
	ptr->UY_table = e_UY;
	ptr->UZ_table = e_UZ;
	ptr->ROTX_table = e_ROTX;
	ptr->ROTY_table = e_ROTY;
	ptr->ROTZ_table = e_ROTZ;
}

bool GiraffeModel::ReadGiraffeAddress(FILE *f)
{
	char str[10];
	if (fscanf(f, "%s", str) != EOF && !strcmp(str, "run"))
		run_giraffe = true;
	else
	{
		Log::AddWarning("\n   + Error reading keyword to call Giraffe. It must be 'run'.");
		return false;
	}
	
	return true;
}


