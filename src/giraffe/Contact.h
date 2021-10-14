#pragma once


class Contact
{
public:
	Contact();
	virtual ~Contact();

	virtual inline std::ofstream& WriteGiraffeFile(std::ofstream& out) = 0;

};

