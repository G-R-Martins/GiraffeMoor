#pragma once
#include "Element.h"


class RigidBody : public Element
{
public:
	RigidBody();
	~RigidBody();

	//Writes Giraffe file
	void WriteGiraffeModelFile(FILE *f) override;
};

