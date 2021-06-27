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
#include "SineWaveDisplacement.h"

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

	unsigned int cur_line;
	unsigned int tot_elem;			//per line

	unsigned int cur_node_mesh;
	unsigned int cur_elem;
	unsigned int cur_cs;			//Start with '2', because the first one will be the global coordinate system
	unsigned int cur_node_set;
	unsigned int cur_vessel;
	unsigned int cur_special_constraint;
	unsigned int cur_node_set_constraint;
	unsigned int cur_constraint;
	unsigned int cur_load;
	unsigned int cur_disp;
	unsigned int cur_rbdata;
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

	//Segment number that contains the TDZ (if exists).
	 //The TDZ is restricted to a single segment
	unsigned int seg_tdp;

	//============================================================================

	/*-----------------------------------
	Auxiliar tables, matrices and vectors
	------------------------------------*/

	//Table with values of lines penetration in the seabed 
	Table* penetration;
	
	//Auxiliar matrix to mount line mesh
	std::vector<std::vector<double>> x0_n;

	//Tensions at extremities points (used in summary file)
	std::array<double, 2> extrem_tensions;

	//Number of nodesets
	std::forward_list<unsigned int> anchor_nodesets, fairlead_nodesets;

	// Dynamic relaxation data
	std::vector<double> rho_eq;	///equivalent specific mass for each  line
	std::vector<double> area_eq;	///equivalent cross section area for each line
	double rot_fairlead;			///fairlead rotation

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
	MoorConstraint moor_constraint;
		

	/*-------------
	Object pointers
	--------------*/

	//Stiffness matrix object (analytical or numerical)
	std::unique_ptr<StiffnessMatrix> stiff_matrix;
	//============================================================================

	/*-----------------------------------------------------
	Containers with objects composing the programa Database
	-----------------------------------------------------*/

	//Vector with line objects (before move assignments)
	std::vector<Line> line_vector;

	//Vector with vessel objects
	std::vector<Vessel> vessel_vector;

	//Vector with keypoints objects
	std::vector<Keypoint> keypoint_vector;

	//Vector with segment properties objects
	std::vector<SegmentProperty> segment_property_vector;

	//Deque with nodal force objects
	std::deque<MoorLoad> moorload_vector;

	//Vector with platform objects
	std::vector<Platform> platform_vector;

	//Deque with vessel displacements
	std::deque<VesselDisplacement> vessel_disp_vector;

	//Vector with segment sets
	std::vector<SegmentSet> segment_set_vector;

	//Vector with displacement fields
	std::vector<LineDisplacementField> disp_field_vector;


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

	void Catenary_GeneralSetting(Line& line, const unsigned int& n_segs, Matrix& A, Matrix& B,
								 double& Hf, double& Vf, Matrix& Fairleads_StiffnessMatrix);

	bool SolveCatenaryEquations(Line& line, const unsigned int& n_segs, Matrix& A, Matrix& B,
								double& Hf, double& Vf, Matrix& F, std::vector <double>& FV,
								Matrix& Fairleads_StiffnessMatrix);

	void SetLinesConfiguration(Line& line, Matrix& F, std::vector <double>& FV, const unsigned int& n_segs);

	void GenerateCatenaryTDZ(Line& line, const unsigned int& n_segs, unsigned int& seg_init);

	void CheckSegmentsSize(Line& line, const unsigned int& n_segs, const unsigned int& seg_init);

	void SetMeshProperties(Line& line, const unsigned int& n_segs);

	//Gera a malha das linhas
	void GenerateMesh(Line& line, Matrix& A, Matrix& F, double& Hf, double& Vf);

	void GenerateCatenaryDisplacement(Line& line, const unsigned int& n_segs, Matrix& F, std::vector <double>& FV, unsigned int& cur_node, 
									  std::vector<std::vector<double>>& xcat_n, std::vector<std::vector<double>>& zcat_n, std::vector<std::vector<double>>& roty_n);


	//Checks for dummy elements
	void CheckDummyElements();

	//Generates contact
	void GenerateContact();

	void GenerateDynamicRelaxation();

	inline bool Look4SharedLine();

	//Generates vessel (node, element, nodeset and fairleads coupling)
	void GenerateVessel();

	void GenerateRigidNodeSets();
	void IncludeSharedLinesFaileads(BoolTable& bool_t);

	//Seta dados gerais para a analise
	void GeneralSetting();

	//Initial steps to set model (catenary, sea current...)
	void SettingModelSteps(unsigned int& step, double& start);
	
	//Analysis steps 
	void GenerateAnalysisSteps(unsigned int& step, double& start);

	//Vessel(s) nodal displacement(s)
	void GenerateVesselDisplacements(unsigned int& step);
	
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
