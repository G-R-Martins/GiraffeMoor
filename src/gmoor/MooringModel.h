#pragma once

//Database headers
#include "GiraffeModel.h"

//MooringModel classes with mirror in GiraffeModel database
#include "MoorEnvironment.h"
#include "MoorSolution.h"
#include "MoorPost.h"
#include "MoorLoad.h"
#include "MoorConstraint.h"

//Mooring model classes
#include "Keypoint.h"
#include "Line.h"
#include "Vessel.h"
#include "Platform.h"
#include "LineDisplacementField.h"
#include "VesselDisplacement.h"
#include "StiffnessMatrix.h"
#include "SegmentSet.h"
#include "SegmentProperty.h"

#include "MathCode.h"

class MooringModel
{
public:
	//============================================================================

					/*+-+-+-+-+-+-+-+
					|               |
					|   Variables   |
					|               |
					+-+-+-+-+-+-+-+-*/

	/*---------------------------
	Parameters used to track data
	----------------------------*/

	size_t cur_line;
	unsigned int tot_elem;			//per line

	size_t cur_node_mesh;
	size_t cur_elem;
	size_t cur_cs;			//Start with '2', because the first one will be the global coordinate system
	size_t cur_node_set;
	size_t cur_vessel;
	size_t cur_special_constraint;
	size_t cur_node_set_constraint;
	size_t cur_constraint;
	size_t cur_load;
	size_t cur_disp;
	size_t cur_rbdata;
	unsigned int node_set_contact;	//nodes of all lines
	unsigned int pil_node_set;		//seabed nodeset
	bool TDZ;
	bool existSharedLine;
	

	/*------------
	TDP parameters
	------------*/

	//Inidicates if exist a TDP
	bool existTDP; 

	//Reference coordinate of the TDP(touchdown point)
	double x_tdp;

	//Reference coordinate of the TDP, considering extensibility
	double x_tdp_ext;

	//Number of elements in the TDZ
	unsigned int elem_tdp;

	//============================================================================

	/*-----------------------------------
	Auxiliar tables, matrices and vectors
	------------------------------------*/


	//Tables with values of lines penetration in the seabed 
	std::forward_list<Table> penetration;
	
	//Auxiliar matrix to mount line mesh
	std::vector<std::vector<double>> x0_n;

	//Tensions at extremities points (used in summary file)
	std::array<double, 2> extrem_tensions;

	//Number of nodesets
	std::forward_list<unsigned int> anchor_nodesets, fairlead_nodesets;

	//Epsilons used to establish contact with line(s) and seabed
	std::vector<double> line_seabed_epsilon;

	// Dynamic relaxation data
	std::vector<double> rho_eq;		// equivalent specific mass for each  line
	std::vector<double> area_eq;	// equivalent cross section area for each line
	double rot_fairlead;			// fairlead rotation

	//============================================================================

					/*-+-+-+-+-+-+-+-+
					|                |
					|     Objects    |
					|                |
					+-+-+-+-+-+-+-+-+*/

	/*------------------------------------
	Objects composing the program Database
	-------------------------------------*/

	MoorEnvironment environment;
	MoorSolution moorsolution;
	MoorPost moorpost;
	

	/*-------------
	Object pointers
	--------------*/

	//Stiffness matrix object (analytical or numerical)
	std::unique_ptr<StiffnessMatrix> stiff_matrix;
	
	//============================================================================

	/*-----------------------------------------------------
	Containers with objects composing the programa Database
	-----------------------------------------------------*/

	std::vector<Line> line_vector;
	std::vector<Vessel> vessel_vector;
	std::vector<Keypoint> keypoint_vector;
	std::vector<SegmentProperty> segment_property_vector;
	std::deque<MoorLoad> moorload_vector;
	std::vector<Platform> platform_vector;
	std::deque<VesselDisplacement> vessel_disp_vector;
	std::vector<SegmentSet> segment_set_vector;
	std::vector<LineDisplacementField> disp_field_vector;

	std::vector<MoorConstraint> anchor_constraints;
	std::vector<MoorConstraint> vessel_constraints;
	std::vector<MoorConstraint> line_constraints;

	//============================================================================

	
public:
			
	//============================================================================
	
					/*+-+-+-+-+-+-+-+
					|               |
					|   Functions   |
					|               |
					+-+-+-+-+-+-+-+-*/

	/*----------------------------
	MooringModel General Functions
	-----------------------------*/
	

	MooringModel();
	~MooringModel();

	//Generates all Giraffe input data
	bool GenerateGiraffeModel();

	//Computes data from entered Segment Properties
	void PreCalcSegmentPropertiesData();

	//Copia dados da base do MooringModel ao GiraffeModel
	void CopyData();

	/*Catenary functions 
	  -> 'GenerateCatenary' calls other functions*/
	bool GenerateCatenary();

	void Catenary_GeneralSetting(Line& line,
								 Matrix& A, Matrix& B, Matrix& Fairleads_StiffnessMatrix);

	bool SolveCatenaryEquations(Line& line, Matrix& A, Matrix& B,
								double& Hf, double& Vf, Matrix& F, std::vector <double>& FV,
								Matrix& Fairleads_StiffnessMatrix);

	void SetLinesConfiguration(Line& line, Matrix& F, std::vector<double>& FV);

	void GenerateCatenaryTDZ(Line& line, unsigned int& seg_init);

	void CheckSegmentsSize(Line& line, const unsigned int& seg_init);

	void SetMeshProperties(Line& line);

	void GenerateMesh(Line& line, Matrix& A, Matrix& F, double& Hf, double& Vf);

	void ImposePenetration(Line& line);

	void GenerateCatenaryDisplacement(Line& line, Matrix& F, std::vector <double>& FV, unsigned int& cur_node, 
									  std::vector<std::vector<double>>& xcat_n, std::vector<std::vector<double>>& zcat_n, std::vector<std::vector<double>>& roty_n);


	//Checks for dummy elements
	void CheckDummyElements();

	//Generates contact between line(s) and seabed
	void GenerateContacts();

	void GenerateDynamicRelaxation();

	inline bool Look4SharedLine();

	//Generates vessel (node, element, nodeset and fairleads coupling)
	void GenerateVessels();

	void GenerateRigidNodeSets();
	void IncludeSharedLinesFaileads(BoolTable& bool_t);

	//Seta dados gerais para a analise
	void GeneralSetting();

	//Initial steps to set model (catenary, sea current...)
	void SettingModelSteps(unsigned int& step, double& start);
	
	//Analysis steps 
	void GenerateAnalysisSteps(unsigned int& step, double& start);

	//Vessel(s) nodal displacement(s)
	void GenerateVesselDisplacements();
	
	//Creates applied forces
	void GenerateForces();

	//Line(s) displacement field(s) defined in the input file
	void GenerateDisplacementFields();

	//Gera fundo do mar (superficie de contato)
	void GenerateSeabed();

	//Generates constraints
	void GenerateConstraints();

	//Creates platform object(s)
	void GeneratePlatform();


	//Generate segments from 'SegmentSet', if needed
	void GenerateSegments();
};
