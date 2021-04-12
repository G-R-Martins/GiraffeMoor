#pragma once


class Displacement
{
public:
	Displacement();
	virtual ~Displacement();

	//Interface
	virtual void WriteGiraffeModelFile(FILE *f) = 0;

	//Element ID
	unsigned int number;

	//Boolean to indicate if current displacement uses math code
	bool isMathCode;
};

