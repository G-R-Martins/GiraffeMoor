#pragma once


class Constraint
{
public:
	Constraint();
	virtual ~Constraint();
	virtual void WriteGiraffeModelFile(FILE *f) = 0;

	unsigned int number;				//element ID
};

