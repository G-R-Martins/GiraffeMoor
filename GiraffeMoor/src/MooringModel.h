#pragma once

//Database headers
#include "IO.h"
#include "GiraffeModel.h"

//Mooring model Objets -> read and manipulate data
#include "MoorEnvironment.h"
#include "MoorSolution.h"
#include "MoorPost.h"
#include "MoorLoad.h"

#include "VesselDisplacement.h"
#include "AnchorConstraint.h"
#include "StiffnessMatrix.h"
#include "SegmentSet.h"

//Mooring and Giraffe models -> read, manipulate and write data
#include "Vessel.h"
#include "Line.h"
#include "Keypoint.h"
#include "SegmentProperty.h"
#include "Platform.h"
#include "VesselConstraint.h"
#include "SineWaveDisplacement.h"
#include "MathCode.h"
#include "Monitor.h"
#include "ConvergenceCriteria.h"

#include "BoolTable.h"

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
	unsigned int tot_elem;  //1 line

	unsigned int cur_node_mesh;
	unsigned int cur_elem;
	unsigned int cur_cs;		//Start with '2', because the first one will be the global coordinate system
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
	std::array <double, 2> extrem_tensions;

	//Number of nodesets
	std::forward_list<unsigned int> anchor_nodesets, fairlead_nodesets;

	/* Dynamic relaxation data */

	//Equivalent specific mass for each  line
	std::vector <double> rho_eq;
	//Equivalent cross section area for each line
	std::vector <double> area_eq; //equivalent cross section area for each line
	//Fairlead rotation
	double rot_fairlead;

	//============================================================================

					/*-+-+-+-+-+-+-+-+
					|                |
					|    Database    |
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
	StiffnessMatrix* stiff_matrix;

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

	//Vector with pointers to anchor/vessel constraints
	MoorConstraint moor_constraint;

	//Vector with anchor constraints objects (constraint data)
	std::vector<AnchorConstraint> anc_constraint;

	//Vector with vessel constraints objects (constraint data)
	std::vector<VesselConstraint> vessel_constraint;
	
	//Vector with segment sets
	std::vector<SegmentSet> segment_set_vector;


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

	void GenerateCatenaryTDZ(Line& line, const unsigned int& n_segs, unsigned int& max_nodes, unsigned int& seg_init);

	void CheckSegmentsSize(Line& line, const unsigned int& n_segs, unsigned int& max_nodes, const unsigned int& seg_init);

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

	bool Look4SharedLine();

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

	void GenerateVesselDisplacements(unsigned int& step, double& start);
	//Creates applied forces
	void GenerateForces();



	//Gera fundo do mar (superficie de contato)
	void GenerateSeaBed();

	//Generates constraints
	void GenerateConstraints();

	//Creates platform object(s)
	void GeneratePlatform();


	//Generate segments from 'SegmentSet', if needed
	void GenerateSegments();
};
