#pragma once


class Constraint
{
public:
	Constraint();
	virtual ~Constraint();
	virtual void WriteGiraffeModelFile(std::ostream& fout) const = 0;

	unsigned int number;				//element ID
};

