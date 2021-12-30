#pragma once
#include "Displacement.h"


struct DispStruct
{
	std::array<double, 6> disp;
	unsigned int node_id;
};


class DisplacementField : public Displacement
{
private:
	unsigned int m_cs_id;
	unsigned int m_solution_step_id;

	std::vector<DispStruct> m_disp_data;

public:
	DisplacementField();
	DisplacementField(unsigned int cs_id, unsigned int solution_step_id);
	~DisplacementField();

	//============================================================================
	
	//Inserts displacement field (from a matrix of translations) in the vector of displacements
	void InsertDisplacement(const unsigned int& node_id, Matrix& e_disp);

	//Inserts displacement field (from a matrix of translations and a matrix of rotations) in the vector of displacements
	void InsertDisplacement(const unsigned int& node_id, Matrix& e_disp, Matrix& e_rot);

	//Inserts displacement field (from an array) in the vector of displacements
	void InsertDisplacement(const unsigned int& node_id, std::array<double, 6>& e_disp);


	/// 
	/// SETTERS
	/// 


	void SetCoordinateSystem(unsigned int cs);
	void SetSolutionStep(unsigned int solution_step);
	

	/// 
	/// GETTERS
	/// 

	unsigned int GetCoordinateSystem() const { return m_cs_id; }
	unsigned int GetSolutionStep() const { return m_solution_step_id; }


	/// 
	/// Overloaded operators
	/// 

	friend std::ostream& operator<<(std::ostream& out, const DisplacementField& obj);
	inline std::ofstream& WriteGiraffeFile(std::ofstream& out) override { operator<<(out, *this); return out; }

};

