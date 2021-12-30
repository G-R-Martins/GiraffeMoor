#include "PCH.h"
#include "GiraffeModel.h"


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

void GiraffeModel::GenerateNode(const unsigned int& id, Matrix& pos, const std::string& comment)
{
	node_vector.emplace_back(id, std::array{ pos(0, 0), pos(1, 0), pos(2, 0) }, comment);
}
void GiraffeModel::GenerateNode(const unsigned int& id, Matrix &pos)
{
	node_vector.emplace_back(id, std::array{ pos(0, 0), pos(1, 0), pos(2, 0) });
}
void GiraffeModel::GenerateNode(const unsigned int& id, double X, double Y, double Z, const std::string& comment)
{
	node_vector.emplace_back(id, std::array{ X, Y, Z }, comment);
}
void GiraffeModel::GenerateNode(const unsigned int& id, double X, double Y, double Z)
{
	node_vector.emplace_back(id, std::array{ X, Y, Z });
}
void GiraffeModel::GenerateNode(const unsigned int& id, const std::array<double,3>& coord, const std::string& comment)
{
	node_vector.emplace_back(id, coord, comment);
}
void GiraffeModel::GenerateNode(const unsigned int& id, const std::array<double, 3>& coord)
{
	node_vector.emplace_back(id, coord);
}
void GiraffeModel::GenerateNode(const unsigned int& id, const std::vector<double>& coord, const std::string& comment)
{
	node_vector.emplace_back(id, std::array{coord[0], coord[1], coord[2] }, comment);
}
void GiraffeModel::GenerateNode(const unsigned int& id, const std::vector<double>& coord)
{
	node_vector.emplace_back(id, std::array{ coord[0], coord[1], coord[2] });
}
void GiraffeModel::GenerateOscillatorySurf(const unsigned int& id, const double& A1, const double& A2, const double& A12, const double& lambda1, const double& lambda2, const double& phi1, const double& phi2, const double& waves1, const double& waves2, const unsigned int& cs_id, const unsigned int& pilot_node_id)
{
	oscillatory_vector.emplace_back(id, A1, A2, A12, lambda1, lambda2, phi1, phi2, waves1, waves2, cs_id, pilot_node_id);
}
void GiraffeModel::GenerateTrussElement(const unsigned int& id, const bool& segment_begin, const unsigned int& section_id, const unsigned int& node1, const unsigned int& node2)
{
	element_vector.emplace_back(new Truss());
	auto ptr = element_vector.back();
	ptr->SetIDNumber(id);
	ptr->SetFirstElementOpt(segment_begin);
	ptr->SetSection(section_id);
	ptr->SetNodes(std::vector{node1,node2});
}
void GiraffeModel::GenerateTrussElement(const unsigned int& id, const bool& segment_begin, const unsigned int& section_id, const unsigned int& node1, const unsigned int& node2, const std::string& comment)
{
	element_vector.emplace_back(new Truss());
	auto ptr = element_vector.back();
	ptr->SetIDNumber(id);
	ptr->SetFirstElementOpt(segment_begin);
	ptr->SetSection(section_id);
	ptr->SetNodes(std::vector{node1,node2});
	ptr->SetLabel(comment);
}
void  GiraffeModel::GenerateRigidBodyElement(const unsigned int& id, const unsigned int& RB_data_material_id, const unsigned int& cs_id, const unsigned int& node)
{
	element_vector.emplace_back(new RigidBody());
	auto ptr = element_vector.back();
	ptr->SetIDNumber(id);
	ptr->SetMaterial(RB_data_material_id);
	ptr->SetCS(cs_id);
	ptr->SetNodes(std::vector{node});
}
void  GiraffeModel::GenerateRigidBodyElement(const unsigned int& id, const unsigned int& RB_data_material_id, const unsigned int& cs_id, const unsigned int& node, const std::string& comment)
{
	element_vector.emplace_back(new RigidBody());
	auto ptr = element_vector.back();
	ptr->SetIDNumber(id);
	ptr->SetMaterial(RB_data_material_id);
	ptr->SetCS(cs_id);
	ptr->SetNodes(std::vector{node});
	ptr->SetLabel(comment);
}
void GiraffeModel::GeneratePipeElement(const unsigned int& id, const bool& segment_begin, const unsigned int& section_id, const unsigned int& cs_id, const unsigned int& node1, const unsigned int& node2, const unsigned int& node3)
{
	element_vector.emplace_back(new Pipe());
	auto ptr = element_vector.back();
	ptr->SetIDNumber(id);
	ptr->SetFirstElementOpt(segment_begin);
	ptr->SetSection(section_id);
	ptr->SetCS(cs_id);
	ptr->SetNodes(std::vector{node1,node2,node3});
}
void GiraffeModel::GeneratePipeElement(const unsigned int& id, const unsigned int& section_id, const unsigned int& cs_id, const unsigned int& node1, const unsigned int& node2, const unsigned int& node3, std::string& comment)
{
	element_vector.emplace_back(new Pipe());
	auto ptr = element_vector.back();
	ptr->SetIDNumber(id);
	ptr->SetFirstElementOpt(false);
	ptr->SetSection(section_id);
	ptr->SetCS(cs_id);
	ptr->SetNodes(std::vector{node1,node2,node3});
	ptr->SetLabel(comment);
}
void GiraffeModel::GenerateCoordinateSystem(const unsigned int& id, Matrix& E1, Matrix& E3)
{
	cs_vector.emplace_back(id, std::array{ E1(0, 0), E1(1, 0), E1(2, 0) }, std::array{ E3(0, 0), E3(1, 0), E3(2, 0) });
}
void GiraffeModel::GenerateCoordinateSystem(const unsigned int& id, const std::array<double,3>& E1, const std::array<double, 3>& E3)
{
	cs_vector.emplace_back(CoordinateSystem(id, E1, E3));
}
void GiraffeModel::GenerateRigidBodyData(const unsigned int& id, double mass, const std::array<double, 6>& J_G, const std::array<double, 3>& G)
{
	rbdata_vector.emplace_back(id, mass, J_G, G);
}
void GiraffeModel::GenerateRigidBodyData(const unsigned int& id, double mass, const std::array<double, 6>& J_G, const std::array<double, 3>& G, std::string&& comment)
{
	rbdata_vector.emplace_back(id, mass, J_G, G, 0, std::move(comment));
}
void GiraffeModel::GenerateRigidBodyData(const unsigned int& id, double mass, const std::array<double, 6>& J_G, const std::array<double, 3>& G, const std::string& comment)
{
	rbdata_vector.emplace_back(id, mass, J_G, G, 0, comment);
}
void GiraffeModel::GenerateRigidBodyData(const unsigned int& id, double mass, const std::array<double, 6>& J_G, const std::array<double, 3>& G, unsigned int cadID)
{
	rbdata_vector.emplace_back(id, mass, J_G, G, cadID);
}
void GiraffeModel::GenerateRigidBodyData(const unsigned int& id, double mass, const std::array<double, 6>& J_G, const std::array<double, 3>& G, unsigned int cadID, std::string&& comment)
{
	rbdata_vector.emplace_back(id, mass, J_G, G, cadID, std::move(comment));
}
void GiraffeModel::GenerateRigidBodyData(const unsigned int& id, double mass, const std::array<double, 6>& J_G, const std::array<double, 3>& G, unsigned int cadID, const std::string& comment)
{
	rbdata_vector.emplace_back(id, mass, J_G, G, cadID, comment);
}
void GiraffeModel::GenerateNSSSContact(const unsigned int& id, const unsigned int& nodeset_id, const unsigned int& surface_set_id,
	double mu, double epn, double cn, double ept, double ct, double pinball, double radius, unsigned int max_interactions, BoolTable&& bool_table)
{
	contact_vector.emplace_back(new NSSS(id, nodeset_id, 
		surface_set_id, mu, epn, cn, ept, ct, pinball, radius, max_interactions, std::move(bool_table)));
}
void GiraffeModel::GenerateNSSSContact(const unsigned int& id, const unsigned int& nodeset_id, const unsigned int& surface_set_id, 
	double mu, double epn, double cn, double ept, double ct, double pinball, double radius, 
	unsigned int max_interactions, BoolTable&& bool_table, const std::string& comment)
{
	contact_vector.emplace_back(new NSSS(id, nodeset_id, surface_set_id, mu, epn, cn, ept, ct, 
		pinball, radius, max_interactions, std::move(bool_table), comment));
}
void GiraffeModel::GenerateRigidNodeSet(const unsigned int& id, const unsigned int& pilot_node_id, const unsigned int& nodeset_id, BoolTable& bool_table)
{
	special_constraint_vector.emplace_back(new RigidNodeSet(pilot_node_id, nodeset_id));

	//Pointer to the RigidNodeSet
	auto ptr = special_constraint_vector.back();
	ptr->SetIDNumber(id);
	ptr->SetBoolTable(bool_table);
}
void GiraffeModel::GenerateRigidNodeSet(const unsigned int& id, const unsigned int& pilot_node_id, const unsigned int& nodeset_id, BoolTable& bool_table, const std::string& comment)
{
	special_constraint_vector.emplace_back(new RigidNodeSet(pilot_node_id, nodeset_id, comment));
	//Pointer to the RigidNodeSet
	auto ptr = special_constraint_vector.back();
	ptr->SetIDNumber(id);
	ptr->SetBoolTable(bool_table);
}
void GiraffeModel::GenerateSameDisplacement(const unsigned int& id, const unsigned int& node_A, const unsigned int& node_B, BoolTable& bool_table)
{
	special_constraint_vector.emplace_back(new SameDisplacement(node_A,node_B));
	//Pointer to the SameDisplacement
	auto ptr = special_constraint_vector.back();
	ptr->SetIDNumber(id);
	ptr->SetBoolTable(bool_table);
}
void GiraffeModel::GenerateSameRotation(const unsigned int& id, const unsigned int& node_A, const unsigned int& node_B, BoolTable& bool_table)
{
	special_constraint_vector.emplace_back(new SameRotation(node_A, node_B));
	//Pointer to the SameDisplacement
	auto ptr = special_constraint_vector.back();
	ptr->SetIDNumber(id);
	ptr->SetBoolTable(bool_table);
}
void GiraffeModel::GenerateNodalDisplacement(const unsigned int& id, const unsigned int& nodeset_id, const unsigned int& cs_id, Table* values)
{
	displacement_vector.emplace_back(new NodalDisplacement(nodeset_id, cs_id, values));
	//Pointer to the NodalDisplacement
	auto ptr = displacement_vector.back();
	ptr->SetIDNumber(id);
}
void GiraffeModel::GenerateNodalDisplacement(const unsigned int& id, const unsigned int& nodeset_id, const unsigned int& cs_id, MathCode* math_code)
{
	displacement_vector.emplace_back(new NodalDisplacement(nodeset_id, cs_id, math_code));
	//Pointer to the NodalDisplacement
	auto ptr = displacement_vector.back();
	ptr->SetIDNumber(id);
}
void GiraffeModel::GenerateNodalDisplacement(const unsigned int& id, const unsigned int& nodeset_id, const unsigned int& cs_id,
											 const std::string& file_name, const unsigned int& header_lines, const unsigned int& n_times)
{
	displacement_vector.emplace_back(new NodalDisplacement(nodeset_id, cs_id, file_name, header_lines, n_times));
	//Pointer to the NodalDisplacement
	auto ptr = displacement_vector.back();
	ptr->SetIDNumber(id);
}
void GiraffeModel::GenerateDisplacementField(const unsigned int& id, const unsigned int& cs_id, const unsigned int& solution_step)
{
	displacement_vector.emplace_back(new DisplacementField(cs_id,solution_step));
	displacement_vector.back()->SetIDNumber(id);
}
void GiraffeModel::GenerateNodeSet(const unsigned int& id, const std::vector<unsigned int>& list, const std::string& comment)
{
	node_set_vector.emplace_back(id, list, comment);
}
void GiraffeModel::GenerateNodeSet(const unsigned int& id, const std::unordered_set<unsigned int>& list, const std::string& comment)
{	
	std::vector<unsigned int> nodes_vec(list.size());
	size_t i = 0;
	for (const unsigned int& node : list)
	{
		nodes_vec[i] = node;
		++i;
	}
	node_set_vector.emplace_back(id, nodes_vec, comment);
}
void GiraffeModel::GenerateNodeSet(const unsigned int& id, unsigned int node, const std::string& comment)
{
	node_set_vector.emplace_back(id, std::vector{ node }, comment);
}
void GiraffeModel::GenerateNodeSet(const unsigned int& id, unsigned int tot_nodes, unsigned int node_init,
	unsigned int increment, const std::string& comment)
{
	node_set_vector.emplace_back(id, tot_nodes, node_init, increment, comment);
}
void GiraffeModel::GenerateSurfaceSet(const unsigned int& id, const std::vector<unsigned int>& list)
{
	surface_set_vector.emplace_back(SurfaceSet(id, list));
}
void GiraffeModel::GenerateStaticSolutionStep(const unsigned int& id, const double& start_time, const double& end_time, const double& i_time_step, const double& max_time_step, const double& min_time_step, const unsigned int& max_it, const unsigned int& min_it, const unsigned int& conv_increase, const double& inc_factor, const unsigned int& sample)
{
	solution_vector.emplace_back(new Static());

	auto ptr = solution_vector.back();
	ptr->SetIDNumber(id);
	ptr->SetStartTime(start_time);
	ptr->SetEndTime(end_time);
	ptr->SetTimeStep(i_time_step, min_time_step, max_time_step);
	ptr->SetIterations(max_it, min_it);
	ptr->SetIncrese(conv_increase, inc_factor);
	ptr->SetSample(sample);
}
void GiraffeModel::GenerateDynamicSolutionStep(const unsigned int& id, const double& start_time, const double& end_time, const double& i_time_step, const double& max_time_step, const double& min_time_step, const unsigned int& max_it, const unsigned int& min_it, const unsigned int& conv_increase, const double& inc_factor, const unsigned int& sample, const double& alpha, const double& beta, const unsigned int& update, const double& gamma_new, const double& beta_new)
{
	solution_vector.emplace_back(new Dynamic(alpha, beta, gamma_new, beta_new, update));

	auto ptr = solution_vector.back();
	ptr->SetIDNumber(id);
	ptr->SetStartTime(start_time);
	ptr->SetEndTime(end_time);
	ptr->SetTimeStep(i_time_step, min_time_step, max_time_step);
	ptr->SetIterations(max_it, min_it);
	ptr->SetIncrese(conv_increase, inc_factor);
	ptr->SetSample(sample);
}
void GiraffeModel::GenerateNodalForce(const unsigned int& id, const unsigned int& nodeset_id, Table* time_series)
{
	load_vector.emplace_back(new NodalForce(nodeset_id, time_series));
	load_vector.back()->SetIDNumber(id);
}
void GiraffeModel::GenerateNodalForce(const unsigned int& id, const unsigned int& nodeset_id,
						  const std::string& file_name, const unsigned int& header_lines, const unsigned int& n_times)
{
	load_vector.emplace_back(new NodalForce(nodeset_id, file_name, header_lines, n_times));
	load_vector.back()->SetIDNumber(id);
}
void GiraffeModel::GenerateNodalForce(const unsigned int& id, const unsigned int& nodeset_id,
						  std::string_view file_name, const unsigned int& header_lines, const unsigned int& n_times)
{
	load_vector.emplace_back(new NodalForce(nodeset_id, std::string(file_name), header_lines, n_times));
	load_vector.back()->SetIDNumber(id);
}
void GiraffeModel::GenerateNodalForce(const unsigned int& id, const unsigned int& nodeset_id, MathCode* mathCode)
{
	load_vector.emplace_back(new NodalForce(nodeset_id, mathCode));
	load_vector.back()->SetIDNumber(id);
}
void GiraffeModel::GenerateNodalConstraint(unsigned int id, unsigned int nodeset_id, BoolTable const& e_UX, BoolTable const& e_UY, BoolTable const& e_UZ, BoolTable const& e_ROTX, BoolTable const& e_ROTY, BoolTable const& e_ROTZ)
{
	constraint_vector.emplace_back(new NodalConstraint(nodeset_id, e_UX, e_UY, e_UZ, e_ROTX, e_ROTY, e_ROTZ));
	constraint_vector.back()->SetIDNumber(id);
}

