#pragma once
#include "Displacement.h"


struct DispStruct
{
	std::array<double, 6> disp;
	size_t node;
};


class DisplacementField : public Displacement
{
private:
	size_t m_cs;
	size_t m_solution_step;

	std::vector<DispStruct> m_disp_data;

public:
	DisplacementField();
	DisplacementField(size_t cs, size_t solution_step);
	~DisplacementField();

	//============================================================================
	
	//Inserts displacement field (from a matrix of translations) in the vector of displacements
	void InsertDisplacement(const int& node, Matrix& e_disp);
	void InsertDisplacement(const unsigned int& node, Matrix& e_disp);

	//Inserts displacement field (from a matrix of translations and a matrix of rotations) in the vector of displacements
	void InsertDisplacement(const int& node, Matrix& e_disp, Matrix& e_rot);
	void InsertDisplacement(const unsigned int& node, Matrix& e_disp, Matrix& e_rot);

	//Inserts displacement field (from an array) in the vector of displacements
	void InsertDisplacement(const unsigned int& node, std::array<double,6>& e_disp);


	/// 
	/// SETTERS
	/// 


	void SetCoordinateSystem(size_t cs);
	void SetSolutionStep(size_t solution_step);
	

	/// 
	/// GETTERS
	/// 

	size_t GetCoordinateSystem() const { return m_cs; }
	size_t GetSolutionStep() const { return m_solution_step; }


	/// 
	/// Overloaded operators
	/// 

	friend std::ostream& operator<<(std::ostream& out, const DisplacementField& obj);
	inline std::ofstream& WriteGiraffeFile(std::ofstream& out) override { operator<<(out, *this); return out; }

};

