#pragma once
#include "Element.h"


class Pipe : public Element
{
public:
	Pipe();
	~Pipe();

	//Writes GIRAFFE input file
	void WriteGiraffeModelFile(FILE *f) override;
};

