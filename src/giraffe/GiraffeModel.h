#pragma once


//GiraffeModel classes with mirror in MooringModel database
#include "Environment.h"
#include "Solution.h"
#include "Post.h"
#include "Load.h"
#include "Constraint.h"

#include "Monitor.h"
#include "ConvergenceCriteria.h"
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
	
	std::vector <Displacement*> displacement_vector;
	std::vector <Constraint*> constraint_vector;
	std::vector <Element*> element_vector;
	std::vector <SpecialConstraint*> special_constraint_vector;
	std::vector <Contact*> contact_vector;
	std::vector <Solution*> solution_vector;
	std::vector <Load*> load_vector;

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
	
	void GenerateNode(const size_t& number, Matrix& pos, std::string_view comment);
	void GenerateNode(const size_t& number, Matrix& pos);
	void GenerateNode(const size_t& number, double X, double Y, double Z, std::string_view comment);
	void GenerateNode(const size_t& number, double X, double Y, double Z);
	void GenerateNode(const size_t& number, const std::array<double, 3>& coord, std::string_view comment);
	void GenerateNode(const size_t& number, const std::array<double, 3>& coord);
	void GenerateNode(const size_t& number, const std::vector<double>& coord, std::string_view comment);
	void GenerateNode(const size_t& number, const std::vector<double>& coord);
	
	//--------------------------------------------------------------------------------------------------------------------------

	/*------
	Elements
	-------*/

	void GenerateTrussElement(const size_t& number, const bool& segment_begin, const size_t& section, const unsigned int& node1, const unsigned int& node2);
	void GenerateTrussElement(const size_t& number, const bool& segment_begin, const size_t& section, const unsigned int& node1, const unsigned int& node2, const std::string& comment);
	void GeneratePipeElement(const size_t& number, const bool& segment_begin, const size_t& section, const unsigned int& cs, const unsigned int& node1, const unsigned int& node2, const unsigned int& node3);
	void GeneratePipeElement(const size_t& number, const size_t& section, const size_t& cs, const unsigned int& node1, const unsigned int& node2, const unsigned int& node3, std::string& comment);
	void GenerateRigidBodyElement(const size_t& number, const unsigned int& RB_data, const size_t& cs, const unsigned int& node);
	void GenerateRigidBodyElement(const size_t& number, const unsigned int& RB_data, const size_t& cs, const unsigned int& node, const std::string& comment);
	
	//--------------------------------------------------------------------------------------------------------------------------

	/*---------
	Constraints
	----------*/

	void GenerateNodalConstraint(size_t number, unsigned int node_set, BoolTable const& e_UX, BoolTable const& e_UY, BoolTable const& e_UZ, BoolTable const& e_ROTX, BoolTable const& e_ROTY, BoolTable const& e_ROTZ);
	void GenerateSameDisplacement(const size_t& number, const unsigned int& node_A, const unsigned int& node_B, BoolTable& bool_table);
	void GenerateSameRotation(const size_t& number, const unsigned int& node_A, const unsigned int& node_B, BoolTable& bool_table);
	
	//--------------------------------------------------------------------------------------------------------------------------

	/*-----------
	Displacements
	------------*/
	
	void GenerateNodalDisplacement(const size_t& number, const size_t& node_set, const size_t& cs, Table* values);
	void GenerateNodalDisplacement(const size_t& number, const size_t& node_set, const size_t& cs, MathCode* math_code);
	void GenerateNodalDisplacement(const size_t& number, const size_t& node_set, const size_t& cs, const std::string& file_name, const unsigned int& header_lines, const unsigned int& n_times);
	void GenerateDisplacementField(const size_t& number, const size_t& cs, const size_t& solution_step);
	void GenerateDisplacementField(const size_t& number, const size_t& cs, const size_t& solution_step, const unsigned int& nodes);
	
	//--------------------------------------------------------------------------------------------------------------------------

	/*-------
	Node sets
	--------*/

	void GenerateNodeSet(const size_t& number, const std::vector<unsigned int>& list, const std::string& comment);
	void GenerateNodeSet(const size_t& number, const std::unordered_set<unsigned int>& list, const std::string& comment);
	void GenerateNodeSet(const size_t& number, unsigned int node, const std::string& comment);
	void GenerateNodeSet(const size_t& number, size_t tot_nodes, size_t node_init, unsigned int increment, const std::string& comment);
	void GenerateRigidNodeSet(const size_t& number, const unsigned int& pilot_node, const size_t& node_set, BoolTable& bool_table);
	void GenerateRigidNodeSet(const size_t& number, const unsigned int& pilot_node, const size_t& node_set, BoolTable& bool_table, const std::string& comment);

	//--------------------------------------------------------------------------------------------------------------------------

	/*------------------
	Surfaces and contact
	-------------------*/

	void GenerateOscillatorySurf(const size_t& number, const double& A1, const double& A2, const double& A12, const double& lambda1, const double& lambda2, const double& phi1, const double& phi2, const double& waves1, const double& waves2, const unsigned int& cs, const unsigned int& pilot_node);
	void GenerateSurfaceSet(const size_t& number, const std::vector<size_t>& list);
	void GenerateNSSSContact(const size_t& number, const size_t& node_set, const size_t& surface_set,
		double mu, double epn, double cn, double ept, double ct, double pinball, double radius, unsigned int max_interactions, BoolTable&& bool_table);
	void GenerateNSSSContact(const size_t& number, const size_t& node_set, const size_t& surface_set,
		double mu, double epn, double cn, double ept, double ct, double pinball, double radius, unsigned int max_interactions, BoolTable&& bool_table, const std::string& comment);
	
	//--------------------------------------------------------------------------------------------------------------------------

	/*------
	Solution
	-------*/

	void GenerateStaticSolutionStep(const size_t& number, const double& start_time, const double& end_time, const double& i_time_step, const double& max_time_step, const double& min_time_step, const unsigned int& max_it, const unsigned int& min_it, const unsigned int& conv_increase, const double& inc_factor, const unsigned int& sample);
	void GenerateDynamicSolutionStep(const size_t& number, const double& start_time, const double& end_time, const double& i_time_step, const double& max_time_step, const double& min_time_step, const unsigned int& max_it, const unsigned int& min_it, const unsigned int& conv_increase, const double& inc_factor, const unsigned int& sample, const double& alpha, const double& beta, const unsigned int& update, const double& gamma_new, const double& beta_new);

	//--------------------------------------------------------------------------------------------------------------------------

	/*----
	Forces
	-----*/

	void GenerateNodalForce(const size_t& number, const size_t& nodeset, Table* time_series);
	void GenerateNodalForce(const size_t& number, const size_t& nodeset, const std::string& file_name, const unsigned int& header_lines, const unsigned int& n_times);
	void GenerateNodalForce(const size_t& number, const size_t& nodeset, std::string_view file_name, const unsigned int& header_lines, const unsigned int& n_times);
	void GenerateNodalForce(const size_t& number, const size_t& nodeset, MathCode* mathCode);
	
	//--------------------------------------------------------------------------------------------------------------------------

	/*-------------
	Other functions
	--------------*/
	
	//Rigid body data
	void GenerateRigidBodyData(const size_t& number, double mass, const std::array<double, 6>& J_G, const std::array<double, 3>& G);
	void GenerateRigidBodyData(const size_t& number, double mass, const std::array<double, 6>& J_G, const std::array<double, 3>& G, std::string&& comment);
	void GenerateRigidBodyData(const size_t& number, double mass, const std::array<double, 6>& J_G, const std::array<double, 3>& G, const std::string& comment);
	void GenerateRigidBodyData(const size_t& number, double mass, const std::array<double, 6>& J_G, const std::array<double, 3>& G, size_t cadID);
	void GenerateRigidBodyData(const size_t& number, double mass, const std::array<double, 6>& J_G, const std::array<double, 3>& G, size_t cadID, std::string&& comment);
	void GenerateRigidBodyData(const size_t& number, double mass, const std::array<double, 6>& J_G, const std::array<double, 3>& G, size_t cadID, const std::string& comment);
	
	//Coordinate system
	void GenerateCoordinateSystem(const size_t& number, Matrix& E1, Matrix& E3);
	void GenerateCoordinateSystem(const size_t& number, const std::array<double, 3>& E1, const std::array<double, 3>& E3);
	
	//==========================================================================================================================
	
};

