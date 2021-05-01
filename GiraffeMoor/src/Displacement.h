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

	//Booleans to indicate if current nodal force uses math code or an external file
	///otherwise, must be defined in the GiraffeMoor input file after 'TimeSeries' keyword
	bool isMathCode, extFile;
};

