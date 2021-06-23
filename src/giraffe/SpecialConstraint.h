#pragma once
#include "BoolTable.h"


class SpecialConstraint
{
public:
	SpecialConstraint();
	virtual ~SpecialConstraint();

	//Interface
	virtual void WriteGiraffeModelFile(FILE *f) = 0;
	
	//============================================================================

	/*-------
	Variables
	--------*/

	//Special constraint ID
	unsigned int number;

	//Special constraint booltable
	BoolTable bool_table;
};
