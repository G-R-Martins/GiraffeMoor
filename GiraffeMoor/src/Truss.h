#pragma once
#include "Element.h"


class Truss :
	public Element
{
public:
	Truss();
	~Truss();

	//Writes Giraffe file
	void WriteGiraffeModelFile(FILE *f) override;

	//Label (comment)
	std::string label;
};


