#pragma once
#include "Displacement.h"
#include "MathCode.h"

class NodalDisplacement : public Displacement
{
public:
	NodalDisplacement();
	~NodalDisplacement();

	NodalDisplacement(Table* tbl);
	NodalDisplacement(MathCode* mc);
	NodalDisplacement(const std::string& f_name, const unsigned int& h_lines, const unsigned int& ntimes);

	//Writes Giraffe file
	void WriteGiraffeModelFile(FILE *f) override;
	
	//============================================================================

	/*-------
	Variables
	-------*/

	//Node set ID
	unsigned int node_set;

	//Coordinate system ID
	unsigned int cs;

	//Number of values (columns) on table
	unsigned int n_values;

	//Table with displacement data
	Table* table;

	//MathCode with displacement equations
	MathCode* mathCode;

	//External file
	std::string file_name;
	unsigned int header_lines, n_times;
};

///TODO: unique ptr