#pragma once
#include "Constraint.h"
#include "BoolTable.h"

class NodalConstraint :
	public Constraint
{
public:
	NodalConstraint();
	~NodalConstraint();

	//Writes output file
	void WriteGiraffeModelFile(std::ostream& fout) const override;
	
	//============================================================================

	/*-------
	Variables
	--------*/

	//Node set ID
	int node_set;

	//BoolTables for each kind of DOF
	BoolTable UX_table;
	BoolTable UY_table;
	BoolTable UZ_table;
	BoolTable ROTX_table;
	BoolTable ROTY_table;
	BoolTable ROTZ_table;
};

