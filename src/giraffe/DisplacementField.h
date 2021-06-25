#pragma once
#include "Displacement.h"

struct DispStruct
{
	std::array<double, 6> disp;
	unsigned int node;
};

class DisplacementField : public Displacement
{
public:
	DisplacementField();
	DisplacementField(unsigned int n_nodes);
	~DisplacementField();

	//============================================================================

	/*-------
	Functions
	--------*/

	//Writes Giraffe file
	void WriteGiraffeModelFile(std::ostream& fout) const override;
	
	//Inserts displacement field (from a matrix of translations) in the vector of displacements
	void InsertDisplacement(const int& node, Matrix& e_disp);
	void InsertDisplacement(const unsigned int& node, Matrix& e_disp);

	//Inserts displacement field (from a matrix of translations and a matrix of rotations) in the vector of displacements
	void InsertDisplacement(const int& node, Matrix& e_disp, Matrix& e_rot);
	void InsertDisplacement(const unsigned int& node, Matrix& e_disp, Matrix& e_rot);

	//Inserts displacement field (from an array) in the vector of displacements
	void InsertDisplacement(const unsigned int& node, std::array<double,6>& e_disp);

	//============================================================================

	/*-------
	Variables
	--------*/

	//Vector with data
	std::vector<DispStruct> disp_data;
	
	//Coordinate system
	unsigned int cs;

	//Solution step
	unsigned int solution_step;
};


