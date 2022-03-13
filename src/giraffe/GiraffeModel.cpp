#include "PCH.h"
#include "GiraffeModel.h"


GiraffeModel::GiraffeModel()
{}

GiraffeModel::~GiraffeModel()
{}

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
void GiraffeModel::GenerateTrussElement(unsigned int id, bool segment_begin, unsigned int section_id, unsigned int node1, unsigned int node2)
{
	element_vector.emplace_back(
		std::make_unique<Truss>(id, segment_begin, section_id, node1, node2)
	);
}
void GiraffeModel::GenerateTrussElement(unsigned int id, bool segment_begin, unsigned int section_id, unsigned int node1, unsigned int node2, const std::string& comment)
{
	element_vector.emplace_back(
		std::make_unique<Truss>(id, segment_begin, section_id, node1, node2, comment)
	);
}
void  GiraffeModel::GenerateRigidBodyElement(unsigned int id, unsigned int RB_data_material_id, unsigned int cs_id, unsigned int node)
{
	element_vector.emplace_back(
		std::make_unique<RigidBody>(id, RB_data_material_id, cs_id, node)
	);
}
void  GiraffeModel::GenerateRigidBodyElement(unsigned int id, unsigned int RB_data_material_id, unsigned int cs_id, unsigned int node, const std::string& comment)
{
	element_vector.emplace_back(
		std::make_unique<RigidBody>(id, RB_data_material_id, cs_id, node, comment)
	);
}
void GiraffeModel::GeneratePipeElement(unsigned int id, bool segment_begin, unsigned int section_id, unsigned int cs_id, unsigned int node1, unsigned int node2, unsigned int node3)
{
	element_vector.emplace_back(
		std::make_unique<Pipe>(id, segment_begin, section_id, cs_id, std::vector{ node1,node2,node3 })
	);
}
void GiraffeModel::GeneratePipeElement(unsigned int id, unsigned int section_id, unsigned int cs_id, unsigned int node1, unsigned int node2, unsigned int node3, const std::string& comment)
{
	element_vector.emplace_back(
		std::make_unique<Pipe>(id, false, section_id, cs_id, std::vector{ node1,node2,node3 }, comment)
	);
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
void GiraffeModel::GenerateNSSSContact(unsigned int id, unsigned int nodeset_id, unsigned int surface_set_id,
	double mu, double epn, double cn, double ept, double ct, double pinball, double radius, unsigned int max_interactions, BoolTable const& bool_table)
{
	contact_vector.emplace_back(
		std::make_unique<NSSS>(
			id, nodeset_id, surface_set_id, mu, epn, cn, ept, ct, pinball, radius, 
			max_interactions, bool_table
		)
	);
}
void GiraffeModel::GenerateNSSSContact(unsigned int id, unsigned int nodeset_id, unsigned int surface_set_id, 
	double mu, double epn, double cn, double ept, double ct, double pinball, double radius, 
	unsigned int max_interactions, BoolTable const& bool_table, const std::string& comment)
{
	contact_vector.emplace_back(
		std::make_unique<NSSS>(
			id, nodeset_id, surface_set_id, mu, epn, cn, ept, ct, 
			pinball, radius, max_interactions, bool_table, comment
		)
	);
}

void GiraffeModel::GenerateNSSSContact(const NSSS& nsss, double mu)
{
	contact_vector.emplace_back(std::make_unique<NSSS>(nsss, mu));
}

void GiraffeModel::GenerateRigidNodeSet(unsigned int id, unsigned int pilot_node_id, unsigned int nodeset_id, const BoolTable& bool_table)
{
	special_constraint_vector.emplace_back(
		std::make_unique<RigidNodeSet>(id, pilot_node_id, nodeset_id, bool_table)
	);
}
void GiraffeModel::GenerateRigidNodeSet(unsigned int id, unsigned int pilot_node_id, unsigned int nodeset_id, const BoolTable& bool_table, const std::string& comment)
{
	special_constraint_vector.emplace_back(
		std::make_unique<RigidNodeSet>(id, pilot_node_id, nodeset_id, bool_table, comment)
	);
}
void GiraffeModel::GenerateSameDisplacement(unsigned int id, unsigned int node_A, unsigned int node_B, const BoolTable& bool_table)
{
	special_constraint_vector.emplace_back(
		std::make_unique<SameDisplacement>(id, node_A, node_B, bool_table)
	);
}
void GiraffeModel::GenerateSameRotation(unsigned int id, unsigned int node_A, unsigned int node_B, const BoolTable& bool_table)
{
	special_constraint_vector.emplace_back(
		std::make_unique<SameRotation>(id, node_A, node_B, bool_table)
	);
}
void GiraffeModel::GenerateNodalDisplacement(unsigned int id, unsigned int nodeset_id, unsigned int cs_id, Table* values)
{
	displacement_vector.emplace_back(
		std::make_shared<NodalDisplacement>(id, nodeset_id, cs_id, values)
	);
}
void GiraffeModel::GenerateNodalDisplacement(unsigned int id, unsigned int nodeset_id, unsigned int cs_id, Table* values, const BoolTable& booltable)
{
	displacement_vector.emplace_back(
		std::make_shared<NodalDisplacement>(id, nodeset_id, cs_id, values, booltable)
	);
}
void GiraffeModel::GenerateNodalDisplacement(unsigned int id, unsigned int nodeset_id, unsigned int cs_id, MathCode* math_code)
{
	displacement_vector.emplace_back(
		std::make_shared<NodalDisplacement>(id, nodeset_id, cs_id, math_code)
	);
}
void GiraffeModel::GenerateNodalDisplacement(unsigned int id, unsigned int nodeset_id, unsigned int cs_id, MathCode* math_code, const BoolTable& booltable)
{
	displacement_vector.emplace_back(
		std::make_shared<NodalDisplacement>(id, nodeset_id, cs_id, math_code, booltable)
	);
}
void GiraffeModel::GenerateNodalDisplacement(unsigned int id, unsigned int nodeset_id, unsigned int cs_id,
											 const std::string& file_name, unsigned int header_lines, unsigned int n_times)
{
	displacement_vector.emplace_back(
		std::make_shared<NodalDisplacement>(id, nodeset_id, cs_id, file_name, header_lines, n_times)
	);
}
void GiraffeModel::GenerateNodalDisplacement(unsigned int id, unsigned int nodeset_id, unsigned int cs_id, const std::string& file_name, unsigned int header_lines, unsigned int n_times, const BoolTable& booltable)
{
	displacement_vector.emplace_back(
		std::make_shared<NodalDisplacement>(id, nodeset_id, cs_id, file_name, header_lines, n_times, booltable)
	);
}
void GiraffeModel::GenerateDisplacementField(unsigned int id, unsigned int cs_id, unsigned int solution_step)
{
	displacement_vector.emplace_back(
		std::make_shared<DisplacementField>(id, cs_id, solution_step)
	);
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
void GiraffeModel::GenerateStaticSolutionStep(unsigned int id, double start_time, double end_time, double i_time_step, double max_time_step, double min_time_step, unsigned int max_it, unsigned int min_it, unsigned int conv_increase, double inc_factor, unsigned int sample)
{
	solution_vector.emplace_back(
		std::make_unique<Static>(
			id, start_time, end_time, i_time_step, min_time_step, max_time_step, 
			max_it, min_it, conv_increase, inc_factor, sample
		)
	);
}
void GiraffeModel::GenerateDynamicSolutionStep(unsigned int id, double start_time, double end_time, double i_time_step, double max_time_step, double min_time_step, unsigned int max_it, unsigned int min_it, unsigned int conv_increase, double inc_factor, unsigned int sample, 
	double alpha, double beta, unsigned int update, double gamma_new, double beta_new, bool zero_ic)
{
	solution_vector.emplace_back(
		std::make_unique<Dynamic>(
			id, start_time, end_time, i_time_step, min_time_step, max_time_step, 
			max_it, min_it, conv_increase, inc_factor, sample, 
			alpha, beta, gamma_new, beta_new, update, zero_ic
		)
	);
}
void GiraffeModel::GenerateNodalForce(unsigned int id, unsigned int nodeset_id, Table* time_series)
{
	load_vector.emplace_back(
		std::make_unique<NodalForce>(id, nodeset_id, time_series)
	);
}
void GiraffeModel::GenerateNodalForce(unsigned int id, unsigned int nodeset_id,
						  std::string& file_name, unsigned int header_lines, unsigned int n_times)
{
	load_vector.emplace_back(
		std::make_unique<NodalForce>(id, nodeset_id, file_name, header_lines, n_times)
	);
}
void GiraffeModel::GenerateNodalForce(unsigned int id, unsigned int nodeset_id,
						  std::string_view file_name, unsigned int header_lines, unsigned int n_times)
{
	load_vector.emplace_back(
		std::make_unique<NodalForce>(id, nodeset_id, std::string(file_name), header_lines, n_times)
	);
}
void GiraffeModel::GenerateNodalForce(unsigned int id, unsigned int nodeset_id, MathCode* mathCode)
{
	load_vector.emplace_back(
		std::make_unique<NodalForce>(id, nodeset_id, mathCode)
	);
}
void GiraffeModel::GenerateNodalConstraint(unsigned int id, unsigned int nodeset_id, BoolTable const& e_UX, BoolTable const& e_UY, BoolTable const& e_UZ, BoolTable const& e_ROTX, BoolTable const& e_ROTY, BoolTable const& e_ROTZ)
{
	constraint_vector.emplace_back(
		std::make_unique<NodalConstraint>(id, nodeset_id, e_UX, e_UY, e_UZ, e_ROTX, e_ROTY, e_ROTZ)
	);
}

