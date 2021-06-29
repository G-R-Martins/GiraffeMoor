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
#include "SineWaveDisplacement.h"

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
	ConvergenceCriteria conv_criteria;
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
	
	void GenerateNode(unsigned int number, Matrix& pos, const char* comment);
	void GenerateNode(unsigned int number, Matrix& pos);
	void GenerateNode(unsigned int number, double X, double Y, double Z, const char* comment);
	void GenerateNode(unsigned int number, double X, double Y, double Z);
	void GenerateNode(unsigned int number, const std::array<double, 3>& coord, const char* comment);
	void GenerateNode(unsigned int number, const std::array<double, 3>& coord);
	
	//--------------------------------------------------------------------------------------------------------------------------

	/*------
	Elements
	-------*/

	void GenerateTrussElement(const unsigned int& number, const bool& segment_begin, const unsigned int& section, const unsigned int& node1, const unsigned int& node2);
	void GenerateTrussElement(const unsigned int& number, const bool& segment_begin, const unsigned int& section, const unsigned int& node1, const unsigned int& node2, const std::string& comment);
	void GeneratePipeElement(const unsigned int& number, const bool& segment_begin, const unsigned int& section, const unsigned int& cs, const unsigned int& node1, const unsigned int& node2, const unsigned int& node3);
	void GeneratePipeElement(const unsigned int& number, const unsigned int& section, const unsigned int& cs, const unsigned int& node1, const unsigned int& node2, const unsigned int& node3, std::string& comment);
	void GenerateRigidBodyElement(const unsigned int& number, const unsigned int& RB_data, const unsigned int& cs, const unsigned int& node);
	void GenerateRigidBodyElement(const unsigned int& number, const unsigned int& RB_data, const unsigned int& cs, const unsigned int& node, const std::string& comment);
	
	//--------------------------------------------------------------------------------------------------------------------------

	/*---------
	Constraints
	----------*/

	void GenerateNodalConstraint(const unsigned int& number, const unsigned int& node_set, BoolTable& e_UX, BoolTable& e_UY, BoolTable& e_UZ, BoolTable& e_ROTX, BoolTable& e_ROTY, BoolTable& e_ROTZ);
	void GenerateSameDisplacement(const unsigned int& number, const unsigned int& node_A, const unsigned int& node_B, BoolTable& bool_table);
	void GenerateSameRotation(const unsigned int& number, const unsigned int& node_A, const unsigned int& node_B, BoolTable& bool_table);
	
	//--------------------------------------------------------------------------------------------------------------------------

	/*-----------
	Displacements
	------------*/
	
	void GenerateNodalDisplacement(const unsigned int& number, const unsigned int& node_set, const unsigned int& cs, Table* values);
	void GenerateNodalDisplacement(const unsigned int& number, const unsigned int& node_set, const unsigned int& cs, MathCode* math_code);
	void GenerateNodalDisplacement(const unsigned int& number, const unsigned int& node_set, const unsigned int& cs, SineWaveDisplacement* wavedisp_ob);
	void GenerateNodalDisplacement(const unsigned int& number, const unsigned int& node_set, const unsigned int& cs, const std::string& file_name, const unsigned int& header_lines, const unsigned int& n_times);
	void GenerateDisplacementField(const unsigned int& number, const unsigned int& cs, const unsigned int& solution_step);
	void GenerateDisplacementField(const unsigned int& number, const unsigned int& cs, const unsigned int& solution_step, const unsigned int& nodes);
	
	//--------------------------------------------------------------------------------------------------------------------------

	/*-------
	Node sets
	--------*/

	void GenerateNodeSet(const unsigned int& number, std::vector<unsigned int>& list, const char* comment);
	void GenerateNodeSet(const unsigned int& number, const std::unordered_set<unsigned int>& list, const char* comment);
	void GenerateNodeSet(const unsigned int& number, const unsigned int& node, const char* comment);
	void GenerateNodeSet(const unsigned int& number, const unsigned int& tot_nodes, const unsigned int& node_init, const unsigned int& increment, const char* comment);
	void GenerateRigidNodeSet(const unsigned int& number, const unsigned int& pilot_node, const unsigned int& node_set, BoolTable& bool_table);
	void GenerateRigidNodeSet(const unsigned int& number, const unsigned int& pilot_node, const unsigned int& node_set, BoolTable& bool_table, const std::string& comment);

	//--------------------------------------------------------------------------------------------------------------------------

	/*------------------
	Surfaces and contact
	-------------------*/

	void GenerateOscillatorySurf(const unsigned int& number, const double& A1, const double& A2, const double& A12, const double& lambda1, const double& lambda2, const double& phi1, const double& phi2, const double& waves1, const double& waves2, const unsigned int& cs, const unsigned int& pilot_node);
	void GenerateSurfaceSet(const unsigned int& number, const std::vector<unsigned int>& list);
	void GenerateNSSSContact(const unsigned int& number, const unsigned int& node_set, const unsigned int& surface_set, const double& mu, const double& epn, const double& cn, const double& ept, const double& ct, const double& pinball, const double& radius, const unsigned int& max_interactions, BoolTable& bool_table);
	
	//--------------------------------------------------------------------------------------------------------------------------

	/*------
	Solution
	-------*/

	void GenerateStaticSolutionStep(const unsigned int& number, const double& start_time, const double& end_time, const double& i_time_step, const double& max_time_step, const double& min_time_step, const unsigned int& max_it, const unsigned int& min_it, const unsigned int& conv_increase, const double& inc_factor, const unsigned int& sample);
	void GenerateDynamicSolutionStep(const unsigned int& number, const double& start_time, const double& end_time, const double& i_time_step, const double& max_time_step, const double& min_time_step, const unsigned int& max_it, const unsigned int& min_it, const unsigned int& conv_increase, const double& inc_factor, const unsigned int& sample, const double& alpha, const double& beta, const unsigned int& update, const double& gamma_new, const double& beta_new);

	//--------------------------------------------------------------------------------------------------------------------------

	/*----
	Forces
	-----*/

	void GenerateNodalForce(const unsigned int& number, const unsigned int& nodeset, Table* time_series);
	void GenerateNodalForce(const unsigned int& number, const unsigned int& nodeset, const std::string& file_name, const unsigned int& header_lines, const unsigned int& n_times);
	void GenerateNodalForce(const unsigned int& number, const unsigned int& nodeset, std::string_view file_name, const unsigned int& header_lines, const unsigned int& n_times);
	void GenerateNodalForce(const unsigned int& number, const unsigned int& nodeset, MathCode* mathCode);
	
	//--------------------------------------------------------------------------------------------------------------------------

	/*-------------
	Other functions
	--------------*/
	
	//Rigid body data
	void GenerateRigidBodyData(const unsigned int& number, const double& mass, const std::array<double, 6>& J_G, const std::array<double, 3>& G);
	void GenerateRigidBodyData(const unsigned int& number, const double& mass, const std::array<double, 6>& J_G, const std::array<double, 3>& G, std::string&& comment);
	void GenerateRigidBodyData(const unsigned int& number, const double& mass, const std::array<double, 6>& J_G, const std::array<double, 3>& G, const std::string& comment);
	void GenerateRigidBodyData(const unsigned int& number, const double& mass, const std::array<double, 6>& J_G, const std::array<double, 3>& G, const size_t& cadID);
	void GenerateRigidBodyData(const unsigned int& number, const double& mass, const std::array<double, 6>& J_G, const std::array<double, 3>& G, const size_t& cadID, std::string&& comment);
	void GenerateRigidBodyData(const unsigned int& number, const double& mass, const std::array<double, 6>& J_G, const std::array<double, 3>& G, const size_t& cadID, const std::string& comment);
	
	//Coordinate system
	void GenerateCoordinateSystem(unsigned int number, Matrix& E1, Matrix& E3);
	void GenerateCoordinateSystem(unsigned int number, const std::array<double, 3>& E1, const std::array<double, 3>& E3);
	
	//==========================================================================================================================
	
};

