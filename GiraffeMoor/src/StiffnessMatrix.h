#pragma once
#include "Table.h"

class StiffnessMatrix
{
public:
	StiffnessMatrix();
	~StiffnessMatrix();

	//============================================================================

					/*-------
					Functions
					--------*/
	
	//Reads input file
	bool Read(FILE *f);
	
	//Calculates current line contribution to the analytical stiffness matrix
	void calc_Kaux(Matrix &fairlead, const std::vector<double>& eul_ang, const double& hf, const double& vf, const double& alpha, Matrix& Fi, Matrix& Ki);
	
	//Setting numbers less than "MIN_NON_ZERO" to zero
	void check_Ktan();
	
	//============================================================================

					/*-------
					Variables
					--------*/

	/*--------------------------------------------------------------------
	Booleans to indicate which type of stiffness matrix will be calculated
	---------------------------------------------------------------------*/

	bool bool_ana;	//Analytical stiffness matrix boolean
	bool bool_num;	//Numerical stiffness matrix boolean

	/*-----------------------------------
	Numerical stiffness matrix parameters
	------------------------------------*/

	///TODO: Displacement to a new reference position before evaluate stiffness matrix

	double time_init;
	double disp_init_x;
	double disp_init_y;
	double disp_init_z;
	double rot_init_x;
	double rot_init_y;
	double rot_init_z;
	
	/*Offsets to calculate numerical stiffness matrix*/
	unsigned int stiff_matrix_step;	//Stiffness matrix solution -> step
	double time_matrix;		//Stiffness matrix solution -> time step
	double disp_matrix_x;	//Stiffness matrix offset X
	double disp_matrix_y;	//Stiffness matrix offset Y
	double disp_matrix_z;	//Stiffness matrix offset Z
	double rot_matrix_x;	//Stiffness matrix offset ROTX
	double rot_matrix_y;	//Stiffness matrix offset ROTY
	double rot_matrix_z;	//Stiffness matrix offset ROTZ

	Table* time_series;

	/*-------------------------
	Analytical stiffness matrix
	--------------------------*/
	
	Matrix K_tan;
	static const int MIN_NON_ZERO = 1;
};

