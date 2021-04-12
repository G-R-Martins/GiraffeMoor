#pragma once


class Contact
{
public:
	Contact();
	virtual ~Contact();
	virtual void WriteGiraffeModelFile(FILE *f) = 0;
};

