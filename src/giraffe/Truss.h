#pragma once
#include "Element.h"


class Truss : public Element
{
public:
	Truss();
	~Truss();

	//Writes Giraffe file
	void WriteGiraffeModelFile(std::ostream& fout) const override;

};


