#pragma once


//GiraffeModel classes with mirror in MooringModel database
#include "Environment.h"
#include "Solution.h"
#include "Post.h"
#include "Load.h"
#include "Constraint.h"

#include "Monitor.h"
#include "CADData.h"
#include "GiraffeSolver.h"
#include "CoordinateSystem.h"
#include "PipeSection.h"

#include "Node.h"
#include "NodeSet.h"

#include "NodalConstraint.h"

#include "Element.h"
#include "Pipe.h"
#include "Truss.h"
#include "RigidBody.h"
#include "RigidBodyData.h"

#include "OscillatorySurf.h"
#include "SurfaceSet.h"

#include "Displacement.h"
#include "NodalDisplacement.h"
#include "DisplacementField.h"

#include "Static.h"
#include "Dynamic.h"

#include "Contact.h"
#include "NSSS.h"

#include "SpecialConstraint.h"
#include "RigidNodeSet.h"
#include "SameDisplacement.h"
#include "SameRotation.h"

#include "NodalForce.h"

#include "BoolTable.h"

class GiraffeModel
{
public:
	GiraffeModel();
	~GiraffeModel();
	
	//==========================================================================================================================

							/*+-+-+-+-+-+-+-+-+-+-+-+
							|						|
							|		Variables		|
							|						|
							+-+-+-+-+-+-+-+-+-+-+-+-*/

	
	/*--------------------
	Giraffe Model Database
	---------------------*/

	Post post;
	Monitor monitor;
	Environment environment;
	GiraffeSolver gir_solver;

	//--------------------------------------------------------------------------------------------------------------------------

	/*---------------------
	Containers with objects
	----------------------*/

	std::deque <Node> node_vector;
	std::vector <CoordinateSystem> cs_vector;
	std::vector <OscillatorySurf> oscillatory_vector;
	std::vector <NodeSet> node_set_vector;
	std::vector <SurfaceSet> surface_set_vector;
	std::vector <PipeSection> pipe_section_vector;
	std::vector <RigidBodyData> rbdata_vector;

	//--------------------------------------------------------------------------------------------------------------------------
	
	/*-----------------------------
	Containers with object pointers
	------------------------------*/
	
	std::vector <std::shared_ptr<Displacement>> displacement_vector;
	std::vector <std::unique_ptr<Constraint>> constraint_vector;
	std::vector <std::unique_ptr<Element>> element_vector;
	std::vector <std::unique_ptr<SpecialConstraint>> special_constraint_vector;
	std::vector <std::unique_ptr<Contact>> contact_vector;
	std::vector <std::unique_ptr<Solution>> solution_vector;
	std::vector < std::unique_ptr<Load>> load_vector;

	//==========================================================================================================================
	//==========================================================================================================================

							/*+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-++-+-+-+-
							|										    |
							|		Giraffe Model General Functions	    |
							|										    |
							+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+*/
	
	/*--------------
	Nodes and points
	---------------*/
	
	void GenerateNode(const unsigned int& id, Matrix& pos, const std::string& comment);
	void GenerateNode(const unsigned int& id, Matrix& pos);
	void GenerateNode(const unsigned int& id, double X, double Y, double Z, const std::string& comment);
	void GenerateNode(const unsigned int& id, double X, double Y, double Z);
	void GenerateNode(const unsigned int& id, const std::array<double, 3>& coord, const std::string& comment);
	void GenerateNode(const unsigned int& id, const std::array<double, 3>& coord);
	void GenerateNode(const unsigned int& id, const std::vector<double>& coord, const std::string& comment);
	void GenerateNode(const unsigned int& id, const std::vector<double>& coord);
	
	//--------------------------------------------------------------------------------------------------------------------------

	/*------
	Elements
	-------*/

	void GenerateTrussElement(unsigned int id, bool segment_begin, unsigned int section_id, unsigned int node1, unsigned int node2);
	void GenerateTrussElement(unsigned int id, bool segment_begin, unsigned int section_id, unsigned int node1, unsigned int node2, const std::string& comment);
	void GeneratePipeElement(unsigned int id, bool segment_begin, unsigned int section_id, unsigned int cs_id, unsigned int node1, unsigned int node2, unsigned int node3);
	void GeneratePipeElement(unsigned int id, unsigned int section_id, unsigned int cs_id, unsigned int node1, unsigned int node2, unsigned int node3, const std::string& comment);
	void GenerateRigidBodyElement(unsigned int id, unsigned int RB_data_material_id, unsigned int cs_id, unsigned int node);
	void GenerateRigidBodyElement(unsigned int id, unsigned int RB_data_material_id, unsigned int cs_id, unsigned int node, const std::string& comment);
	
	//--------------------------------------------------------------------------------------------------------------------------

	/*---------
	Constraints
	----------*/

	void GenerateNodalConstraint(unsigned int id, unsigned int nodeset_id, BoolTable const& e_UX, BoolTable const& e_UY, BoolTable const& e_UZ, BoolTable const& e_ROTX, BoolTable const& e_ROTY, BoolTable const& e_ROTZ);
	void GenerateSameDisplacement(unsigned int id, unsigned int node_A, unsigned int node_B, const BoolTable& bool_table);
	void GenerateSameRotation(unsigned int id, unsigned int node_A, unsigned int node_B, const BoolTable& bool_table);
	void GenerateRigidNodeSet(unsigned int id, unsigned int pilot_node_id, unsigned int nodeset_id, const BoolTable& bool_table);
	void GenerateRigidNodeSet(unsigned int id, unsigned int pilot_node_id, unsigned int nodeset_id, const BoolTable& bool_table, const std::string& comment);

	//--------------------------------------------------------------------------------------------------------------------------

	/*-----------
	Displacements
	------------*/
	
	void GenerateNodalDisplacement(unsigned int id, unsigned int nodeset_id, unsigned int cs_id, Table* values);
	void GenerateNodalDisplacement(unsigned int id, unsigned int nodeset_id, unsigned int cs_id, Table* values, const BoolTable& booltable);
	void GenerateNodalDisplacement(unsigned int id, unsigned int nodeset_id, unsigned int cs_id, MathCode* math_code);
	void GenerateNodalDisplacement(unsigned int id, unsigned int nodeset_id, unsigned int cs_id, MathCode* math_code, const BoolTable& booltable);
	void GenerateNodalDisplacement(unsigned int id, unsigned int nodeset_id, unsigned int cs_id, const std::string& file_name, unsigned int header_lines, unsigned int n_times);
	void GenerateNodalDisplacement(unsigned int id, unsigned int nodeset_id, unsigned int cs_id, const std::string& file_name, unsigned int header_lines, unsigned int n_times, const BoolTable& booltable);
	void GenerateDisplacementField(unsigned int id, unsigned int cs_id, unsigned int solution_step);
	
	//--------------------------------------------------------------------------------------------------------------------------

	/*-------
	Node sets
	--------*/

	void GenerateNodeSet(const unsigned int& id, const std::vector<unsigned int>& list, const std::string& comment);
	void GenerateNodeSet(const unsigned int& id, const std::unordered_set<unsigned int>& list, const std::string& comment);
	void GenerateNodeSet(const unsigned int& id, unsigned int node, const std::string& comment);
	void GenerateNodeSet(const unsigned int& id, unsigned int tot_nodes, unsigned int node_init, unsigned int increment, const std::string& comment);
	
	//--------------------------------------------------------------------------------------------------------------------------

	/*------------------
	Surfaces and contact
	-------------------*/

	void GenerateOscillatorySurf(const unsigned int& id, const double& A1, const double& A2, const double& A12, const double& lambda1, const double& lambda2, const double& phi1, const double& phi2, const double& waves1, const double& waves2, const unsigned int& cs_id, const unsigned int& pilot_node_id);
	void GenerateSurfaceSet(const unsigned int& id, const std::vector<unsigned int>& list);
	void GenerateNSSSContact(unsigned int id, unsigned int nodeset_id, unsigned int surface_set_id, 
		double mu, double epn, double cn, double ept, double ct, double pinball, double radius, 
		unsigned int max_interactions, BoolTable const& bool_table);
	void GenerateNSSSContact(unsigned int id, unsigned int nodeset_id, unsigned int surface_set_id, 
		double mu, double epn, double cn, double ept, double ct, double pinball, double radius, 
		unsigned int max_interactions, BoolTable const& bool_table, const std::string& comment);
	void GenerateNSSSContact(const NSSS& nsss, double mu);

	//--------------------------------------------------------------------------------------------------------------------------

	/*------
	Solution
	-------*/

	void GenerateStaticSolutionStep(unsigned int id, double start_time, double end_time, double i_time_step, double max_time_step, double min_time_step, unsigned int max_it, unsigned int min_it, unsigned int conv_increase, double inc_factor, unsigned int sample);
	void GenerateDynamicSolutionStep(unsigned int id, double start_time, double end_time, double i_time_step, double max_time_step, double min_time_step, unsigned int max_it, unsigned int min_it, unsigned int conv_increase, double inc_factor, unsigned int sample, 
		double alpha, double beta, unsigned int update, double gamma_new, double beta_new, bool zero_ic=false);

	//--------------------------------------------------------------------------------------------------------------------------

	/*----
	Forces
	-----*/

	void GenerateNodalForce(unsigned int id, unsigned int nodeset_id, Table* time_series);
	void GenerateNodalForce(unsigned int id, unsigned int nodeset_id, std::string& file_name, unsigned int header_lines, unsigned int n_times);
	void GenerateNodalForce(unsigned int id, unsigned int nodeset_id, std::string_view file_name, unsigned int header_lines, unsigned int n_times);
	void GenerateNodalForce(unsigned int id, unsigned int nodeset_id, MathCode* mathCode);
	
	//--------------------------------------------------------------------------------------------------------------------------

	/*-------------
	Other functions
	--------------*/
	
	//Rigid body data
	void GenerateRigidBodyData(const unsigned int& id, double mass, const std::array<double, 6>& J_G, const std::array<double, 3>& G);
	void GenerateRigidBodyData(const unsigned int& id, double mass, const std::array<double, 6>& J_G, const std::array<double, 3>& G, std::string&& comment);
	void GenerateRigidBodyData(const unsigned int& id, double mass, const std::array<double, 6>& J_G, const std::array<double, 3>& G, const std::string& comment);
	void GenerateRigidBodyData(const unsigned int& id, double mass, const std::array<double, 6>& J_G, const std::array<double, 3>& G, unsigned int cadID);
	void GenerateRigidBodyData(const unsigned int& id, double mass, const std::array<double, 6>& J_G, const std::array<double, 3>& G, unsigned int cadID, std::string&& comment);
	void GenerateRigidBodyData(const unsigned int& id, double mass, const std::array<double, 6>& J_G, const std::array<double, 3>& G, unsigned int cadID, const std::string& comment);
	
	//Coordinate system
	void GenerateCoordinateSystem(const unsigned int& id, Matrix& E1, Matrix& E3);
	void GenerateCoordinateSystem(const unsigned int& id, const std::array<double, 3>& E1, const std::array<double, 3>& E3);
	
	//==========================================================================================================================
	
};

