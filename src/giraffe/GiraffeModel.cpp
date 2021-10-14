#include "PCH.h"
#include "GiraffeModel.h"
#include "Log.h"


GiraffeModel::GiraffeModel()
{}

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

void GiraffeModel::GenerateNode(const size_t& number, Matrix& pos, std::string_view comment)
{
	node_vector.emplace_back(number, std::array{ pos(0, 0), pos(1, 0), pos(2, 0) }, comment);
}
void GiraffeModel::GenerateNode(const size_t& number, Matrix &pos)
{
	node_vector.emplace_back(number, std::array{ pos(0, 0), pos(1, 0), pos(2, 0) });
}
void GiraffeModel::GenerateNode(const size_t& number, double X, double Y, double Z, std::string_view comment)
{
	node_vector.emplace_back(number, std::array{ X, Y, Z }, comment);
}
void GiraffeModel::GenerateNode(const size_t& number, double X, double Y, double Z)
{
	node_vector.emplace_back(number, std::array{ X, Y, Z });
}
void GiraffeModel::GenerateNode(const size_t& number, const std::array<double,3>& coord, std::string_view comment)
{
	node_vector.emplace_back(number, coord, comment);
}
void GiraffeModel::GenerateNode(const size_t& number, const std::array<double, 3>& coord)
{
	node_vector.emplace_back(number, coord);
}
void GiraffeModel::GenerateNode(const size_t& number, const std::vector<double>& coord, std::string_view comment)
{
	node_vector.emplace_back(number, std::array{coord[0], coord[1], coord[2] }, comment);
}
void GiraffeModel::GenerateNode(const size_t& number, const std::vector<double>& coord)
{
	node_vector.emplace_back(number, std::array{ coord[0], coord[1], coord[2] });
}
void GiraffeModel::GenerateOscillatorySurf(const size_t& number, const double& A1, const double& A2, const double& A12, const double& lambda1, const double& lambda2, const double& phi1, const double& phi2, const double& waves1, const double& waves2, const unsigned int& cs, const unsigned int& pilot_node)
{
	oscillatory_vector.emplace_back(number, A1, A2, A12, lambda1, lambda2, phi1, phi2, waves1, waves2, cs, pilot_node);
}
void GiraffeModel::GenerateTrussElement(const size_t& number, const bool& segment_begin, const size_t& section, const unsigned int& node1, const unsigned int& node2)
{
	element_vector.emplace_back(new Truss());
	auto ptr = element_vector.back();
	ptr->SetIDNumber(number);
	ptr->SetFirstElementOpt(segment_begin);
	ptr->SetSection(section);
	ptr->SetNodes({node1,node2});
}
void GiraffeModel::GenerateTrussElement(const size_t& number, const bool& segment_begin, const size_t& section, const unsigned int& node1, const unsigned int& node2, const std::string& comment)
{
	element_vector.emplace_back(new Truss());
	auto ptr = element_vector.back();
	ptr->SetIDNumber(number);
	ptr->SetFirstElementOpt(segment_begin);
	ptr->SetSection(section);
	ptr->SetNodes({node1,node2});
	ptr->SetLabel(comment);
}
void  GiraffeModel::GenerateRigidBodyElement(const size_t& number, const unsigned int& RB_data, const size_t& cs, const unsigned int& node)
{
	element_vector.emplace_back(new RigidBody());
	auto ptr = element_vector.back();
	ptr->SetIDNumber(number);
	ptr->SetMaterial(RB_data);
	ptr->SetCS(cs);
	ptr->SetNodes({node});
}
void  GiraffeModel::GenerateRigidBodyElement(const size_t& number, const unsigned int& RB_data, const size_t& cs, const unsigned int& node, const std::string& comment)
{
	element_vector.emplace_back(new RigidBody());
	auto ptr = element_vector.back();
	ptr->SetIDNumber(number);
	ptr->SetMaterial(RB_data);
	ptr->SetCS(cs);
	ptr->SetNodes({node});
	ptr->SetLabel(comment);
}
void GiraffeModel::GeneratePipeElement(const size_t& number, const bool& segment_begin, const size_t& section, const unsigned int& cs, const unsigned int& node1, const unsigned int& node2, const unsigned int& node3)
{
	element_vector.emplace_back(new Pipe());
	auto ptr = element_vector.back();
	ptr->SetIDNumber(number);
	ptr->SetFirstElementOpt(segment_begin);
	ptr->SetSection(section);
	ptr->SetCS(cs);
	ptr->SetNodes({node1,node2,node3});
}
void GiraffeModel::GeneratePipeElement(const size_t& number, const size_t& section, const size_t& cs, const unsigned int& node1, const unsigned int& node2, const unsigned int& node3, std::string& comment)
{
	element_vector.emplace_back(new Pipe());
	auto ptr = element_vector.back();
	ptr->SetIDNumber(number);
	ptr->SetFirstElementOpt(false);
	ptr->SetSection(section);
	ptr->SetCS(cs);
	ptr->SetNodes({node1,node2,node3});
	ptr->SetLabel(comment);
}
void GiraffeModel::GenerateCoordinateSystem(const size_t& number, Matrix& E1, Matrix& E3)
{
	cs_vector.emplace_back(number, std::array{ E1(0, 0), E1(1, 0), E1(2, 0) }, std::array{ E3(0, 0), E3(1, 0), E3(2, 0) });
}
void GiraffeModel::GenerateCoordinateSystem(const size_t& number, const std::array<double,3>& E1, const std::array<double, 3>& E3)
{
	cs_vector.emplace_back(CoordinateSystem(number, E1, E3));
}
void GiraffeModel::GenerateRigidBodyData(const size_t& number, double mass, const std::array<double, 6>& J_G, const std::array<double, 3>& G)
{
	rbdata_vector.emplace_back(number, mass, J_G, G);
}
void GiraffeModel::GenerateRigidBodyData(const size_t& number, double mass, const std::array<double, 6>& J_G, const std::array<double, 3>& G, std::string&& comment)
{
	rbdata_vector.emplace_back(number, mass, J_G, G, 0, std::move(comment));
}
void GiraffeModel::GenerateRigidBodyData(const size_t& number, double mass, const std::array<double, 6>& J_G, const std::array<double, 3>& G, const std::string& comment)
{
	rbdata_vector.emplace_back(number, mass, J_G, G, 0, comment);
}
void GiraffeModel::GenerateRigidBodyData(const size_t& number, double mass, const std::array<double, 6>& J_G, const std::array<double, 3>& G, size_t cadID)
{
	rbdata_vector.emplace_back(number, mass, J_G, G, cadID);
}
void GiraffeModel::GenerateRigidBodyData(const size_t& number, double mass, const std::array<double, 6>& J_G, const std::array<double, 3>& G, size_t cadID, std::string&& comment)
{
	rbdata_vector.emplace_back(number, mass, J_G, G, cadID, std::move(comment));
}
void GiraffeModel::GenerateRigidBodyData(const size_t& number, double mass, const std::array<double, 6>& J_G, const std::array<double, 3>& G, size_t cadID, const std::string& comment)
{
	rbdata_vector.emplace_back(number, mass, J_G, G, cadID, comment);
}
void GiraffeModel::GenerateNSSSContact(const size_t& number, const size_t& node_set, const size_t& surface_set,
	double mu, double epn, double cn, double ept, double ct, double pinball, double radius, unsigned int max_interactions, BoolTable&& bool_table)
{
	contact_vector.emplace_back(new NSSS(number, node_set, 
		surface_set, mu, epn, cn, ept, ct, pinball, radius, max_interactions, std::move(bool_table)));
}
void GiraffeModel::GenerateNSSSContact(const size_t& number, const size_t& node_set, const size_t& surface_set, 
	double mu, double epn, double cn, double ept, double ct, double pinball, double radius, 
	unsigned int max_interactions, BoolTable&& bool_table, const std::string& comment)
{
	contact_vector.emplace_back(new NSSS(number, node_set, surface_set, mu, epn, cn, ept, ct, 
		pinball, radius, max_interactions, std::move(bool_table), comment));
}
void GiraffeModel::GenerateRigidNodeSet(const size_t& number, const unsigned int& pilot_node, const size_t& node_set, BoolTable& bool_table)
{
	special_constraint_vector.emplace_back(new RigidNodeSet(pilot_node, node_set));

	//Pointer to the RigidNodeSet
	auto ptr = special_constraint_vector.back();
	ptr->SetIDNumber(number);
	ptr->SetBoolTable(bool_table);
}
void GiraffeModel::GenerateRigidNodeSet(const size_t& number, const unsigned int& pilot_node, const size_t& node_set, BoolTable& bool_table, const std::string& comment)
{
	special_constraint_vector.emplace_back(new RigidNodeSet(pilot_node, node_set, comment));
	//Pointer to the RigidNodeSet
	auto ptr = special_constraint_vector.back();
	ptr->SetIDNumber(number);
	ptr->SetBoolTable(bool_table);
}
void GiraffeModel::GenerateSameDisplacement(const size_t& number, const unsigned int& node_A, const unsigned int& node_B, BoolTable& bool_table)
{
	special_constraint_vector.emplace_back(new SameDisplacement(node_A,node_B));
	//Pointer to the SameDisplacement
	auto ptr = special_constraint_vector.back();
	ptr->SetIDNumber(number);
	ptr->SetBoolTable(bool_table);
}
void GiraffeModel::GenerateSameRotation(const size_t& number, const unsigned int& node_A, const unsigned int& node_B, BoolTable& bool_table)
{
	special_constraint_vector.emplace_back(new SameRotation(node_A, node_B));
	//Pointer to the SameDisplacement
	auto ptr = special_constraint_vector.back();
	ptr->SetIDNumber(number);
	ptr->SetBoolTable(bool_table);
}
void GiraffeModel::GenerateNodalDisplacement(const size_t& number, const size_t& node_set, const size_t& cs, Table* values)
{
	displacement_vector.emplace_back(new NodalDisplacement(node_set, cs, values));
	//Pointer to the NodalDisplacement
	auto ptr = displacement_vector.back();
	ptr->SetIDNumber(number);
}
void GiraffeModel::GenerateNodalDisplacement(const size_t& number, const size_t& node_set, const size_t& cs, MathCode* math_code)
{
	displacement_vector.emplace_back(new NodalDisplacement(node_set, cs, math_code));
	//Pointer to the NodalDisplacement
	auto ptr = displacement_vector.back();
	ptr->SetIDNumber(number);
}
void GiraffeModel::GenerateNodalDisplacement(const size_t& number, const size_t& node_set, const size_t& cs,
											 const std::string& file_name, const unsigned int& header_lines, const unsigned int& n_times)
{
	displacement_vector.emplace_back(new NodalDisplacement(node_set, cs, file_name, header_lines, n_times));
	//Pointer to the NodalDisplacement
	auto ptr = displacement_vector.back();
	ptr->SetIDNumber(number);
}
void GiraffeModel::GenerateDisplacementField(const size_t& number, const size_t& cs, const size_t& solution_step)
{
	displacement_vector.emplace_back(new DisplacementField(cs,solution_step));
	displacement_vector.back()->SetIDNumber(number);
}
void GiraffeModel::GenerateDisplacementField(const size_t& number, const size_t& cs, const size_t& solution_step, const unsigned int& nodes)
{
	displacement_vector.emplace_back(new DisplacementField(cs, solution_step));
	displacement_vector.back()->SetIDNumber(number);
}
void GiraffeModel::GenerateNodeSet(const size_t& number, const std::vector<unsigned int>& list, const std::string& comment)
{
	node_set_vector.emplace_back(number, list, comment);
}
void GiraffeModel::GenerateNodeSet(const size_t& number, const std::unordered_set<unsigned int>& list, const std::string& comment)
{	
	std::vector<unsigned int> nodes_vec(list.size());
	size_t i = 0;
	for (const unsigned int& node : list)
	{
		nodes_vec[i] = node;
		++i;
	}
	node_set_vector.emplace_back(number, nodes_vec, comment);
}
void GiraffeModel::GenerateNodeSet(const size_t& number, unsigned int node, const std::string& comment)
{
	node_set_vector.emplace_back(number, std::vector{ node }, comment);
}
void GiraffeModel::GenerateNodeSet(const size_t& number, size_t tot_nodes, size_t node_init,
	unsigned int increment, const std::string& comment)
{
	node_set_vector.emplace_back(number, tot_nodes, node_init, increment, comment);
}
void GiraffeModel::GenerateSurfaceSet(const size_t& number, const std::vector<size_t>& list)
{
	surface_set_vector.emplace_back(SurfaceSet(number, list));
}
void GiraffeModel::GenerateStaticSolutionStep(const size_t& number, const double& start_time, const double& end_time, const double& i_time_step, const double& max_time_step, const double& min_time_step, const unsigned int& max_it, const unsigned int& min_it, const unsigned int& conv_increase, const double& inc_factor, const unsigned int& sample)
{
	solution_vector.emplace_back(new Static());

	auto ptr = solution_vector.back();
	ptr->SetIDNumber(number);
	ptr->SetStartTime(start_time);
	ptr->SetEndTime(end_time);
	ptr->SetTimeStep(i_time_step, min_time_step, max_time_step);
	ptr->SetIterations(max_it, min_it);
	ptr->SetIncrese(conv_increase, inc_factor);
	ptr->SetSample(sample);
}
void GiraffeModel::GenerateDynamicSolutionStep(const size_t& number, const double& start_time, const double& end_time, const double& i_time_step, const double& max_time_step, const double& min_time_step, const unsigned int& max_it, const unsigned int& min_it, const unsigned int& conv_increase, const double& inc_factor, const unsigned int& sample, const double& alpha, const double& beta, const unsigned int& update, const double& gamma_new, const double& beta_new)
{
	solution_vector.emplace_back(new Dynamic(alpha, beta, gamma_new, beta_new, update));

	auto ptr = solution_vector.back();
	ptr->SetIDNumber(number);
	ptr->SetStartTime(start_time);
	ptr->SetEndTime(end_time);
	ptr->SetTimeStep(i_time_step, min_time_step, max_time_step);
	ptr->SetIterations(max_it, min_it);
	ptr->SetIncrese(conv_increase, inc_factor);
	ptr->SetSample(sample);
}
void GiraffeModel::GenerateNodalForce(const size_t& number, const size_t& nodeset, Table* time_series)
{
	load_vector.emplace_back(new NodalForce(nodeset, time_series));
	load_vector.back()->SetNumber(number);
}
void GiraffeModel::GenerateNodalForce(const size_t& number, const size_t& nodeset,
						  const std::string& file_name, const unsigned int& header_lines, const unsigned int& n_times)
{
	load_vector.emplace_back(new NodalForce(nodeset, file_name, header_lines, n_times));
	load_vector.back()->SetNumber(number);
}
void GiraffeModel::GenerateNodalForce(const size_t& number, const size_t& nodeset,
						  std::string_view file_name, const unsigned int& header_lines, const unsigned int& n_times)
{
	load_vector.emplace_back(new NodalForce(nodeset, std::string(file_name), header_lines, n_times));
	load_vector.back()->SetNumber(number);
}
void GiraffeModel::GenerateNodalForce(const size_t& number, const size_t& nodeset, MathCode* mathCode)
{
	load_vector.emplace_back(new NodalForce(nodeset, mathCode));
	load_vector.back()->SetNumber(number);
}
void GiraffeModel::GenerateNodalConstraint(size_t number, unsigned int node_set, BoolTable const& e_UX, BoolTable const& e_UY, BoolTable const& e_UZ, BoolTable const& e_ROTX, BoolTable const& e_ROTY, BoolTable const& e_ROTZ)
{
	constraint_vector.emplace_back(new NodalConstraint(node_set, e_UX, e_UY, e_UZ, e_ROTX, e_ROTY, e_ROTZ));
	constraint_vector.back()->SetIDNumber(number);
}

