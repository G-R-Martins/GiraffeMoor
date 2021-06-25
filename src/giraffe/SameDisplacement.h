#pragma once
#include "SpecialConstraint.h"


class SameDisplacement : public SpecialConstraint
{
public:
	SameDisplacement();
	~SameDisplacement();

	//Writes Giraffe file
	void WriteGiraffeModelFile(std::ostream& fout) const override;

	unsigned int node_A;
	unsigned int node_B;
	unsigned int initial_load_step;
};

