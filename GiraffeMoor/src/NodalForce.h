#pragma once
#include "Force.h"
#include "MathCode.h"


class NodalForce : public Load
{
public:
	NodalForce();
	~NodalForce();
	NodalForce(Table* time_series);
	NodalForce(MathCode* mc);

	//============================================================================

			/*-------
			Functions
			--------*/

	//Writes Giraffe file
	void WriteGiraffeModelFile(FILE* f) override;
	
	//============================================================================

			/*-------
			Variables
			--------*/
		
	//Data pointer
	Table* table;
	MathCode* mathCode;
	
	//Node set
	unsigned int nodeset;
};

