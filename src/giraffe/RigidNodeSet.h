#pragma once
#include "SpecialConstraint.h"


class RigidNodeSet : public SpecialConstraint
{
public:
	RigidNodeSet();
	~RigidNodeSet();

	//Writes Giraffe file
	void WriteGiraffeModelFile(FILE *f) override;

	//============================================================================

	/*-------
	Variables
	--------*/

	//Rigid NS -> pilot node ID
	unsigned int pilot_node;

	//Rigid NS -> node set ID
	unsigned int node_set;
	
	std::string comment;
};

