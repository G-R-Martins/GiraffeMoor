#pragma once


class Contact
{
public:
	Contact();
	virtual ~Contact();
	virtual void WriteGiraffeModelFile(std::ostream& fout) const = 0;
};

