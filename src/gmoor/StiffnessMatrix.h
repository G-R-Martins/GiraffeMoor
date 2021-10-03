#pragma once
#include "Table.h"

class StiffnessMatrix
{
	// Booleans to indicate which type of stiffness matrix will be calculated
	bool m_exist_analytical;
	bool m_exist_numerical;

	//Numerical stiffness matrix parameters
	///TODO: Displacement to a new reference position before evaluate stiffness matrix
	double m_time_init;
	double m_disp_init_x;
	double m_disp_init_y;
	double m_disp_init_z;
	double m_rot_init_x;
	double m_rot_init_y;
	double m_rot_init_z;

	// Offsets to calculate numerical stiffness matrix
	unsigned int m_stiff_matrix_step;	//Stiffness matrix solution -> step
	double m_time_matrix;		//Stiffness matrix solution -> time step
	double m_disp_matrix_x;
	double m_disp_matrix_y;
	double m_disp_matrix_z;
	double m_rot_matrix_x;
	double m_rot_matrix_y;
	double m_rot_matrix_z;

	std::unique_ptr<Table> m_time_series;

	// Analytical stiffness matrix
	Matrix m_K_tan;
	static const int MIN_NON_ZERO = 1;
	
	//============================================================================

public:
	StiffnessMatrix();
	~StiffnessMatrix();
	
	
	//Calculates current line contribution to the analytical stiffness matrix
	void calc_Kaux(Matrix &fairlead, const std::vector<double>& eul_ang, const double& hf, const double& vf, const double& alpha, Matrix& Fi, Matrix& Ki);
	
	//Setting numbers less than "MIN_NON_ZERO" to zero
	void check_Ktan();	

	//Print stiffness matrix to file
	void FprintKtan(const std::string& file);


	// 
	// SETTERS
	// 
	
	void SetAnalyticalStiffnessOpt(bool option);
	void SetNumericalStiffnessOpt(bool option);


	// 
	// GETTERS
	// 
	
	inline unsigned int GetStep() const { return this->m_stiff_matrix_step; }
	
	//Check if stiffness matrix is defined
	inline bool ExistAnalyticalStiffMat() const { return this->m_exist_analytical; }
	inline bool ExistNumericalStiffMat() const { return this->m_exist_numerical; }


	///
	/// Overloaded operators
	/// 

	friend std::ostream& operator<<(std::ostream& out, const StiffnessMatrix& mat);
	friend std::ostream& operator<<(std::ostream& out, StiffnessMatrix* mat);
};

