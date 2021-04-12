#pragma once
#include "SpecialConstraint.h"


class SameRotation : public SpecialConstraint
{
public:
	SameRotation();
	~SameRotation();

	//Writes Giraffe file
	void WriteGiraffeModelFile(FILE *f) override;

	//============================================================================

	/*---
	Nodes
	-----*/

	unsigned int node_A;
	unsigned int node_B;
};

