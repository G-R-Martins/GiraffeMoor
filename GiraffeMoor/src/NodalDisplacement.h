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
};

