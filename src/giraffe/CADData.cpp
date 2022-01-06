#include "PCH.h"
#include "CADData.h"


CADData::CADData()
	: m_id(0), m_name("\0")
{}

CADData::~CADData()
{}




/// 
/// SETTERS
/// 

void CADData::SetIDNumber(unsigned int id)
{
	this->m_id = id;
}

void CADData::SetName(const std::string& name)
{
	this->m_name = name;
}



/// 
/// Overloaded operators
/// 

bool operator<(const CADData& obj1, const CADData& obj2)
{
	return obj1.m_id < obj2.m_id;
}

bool operator>(const CADData& obj1, const CADData& obj2)
{
	return !(obj1 < obj2);
}

bool operator==(const CADData& obj1, const CADData& obj2)
{
	return obj1.m_id == obj2.m_id;
}

bool operator!=(const CADData& obj1, const CADData& obj2)
{
	return !(obj1 == obj2);
}



std::ostream& operator<<(std::ostream& out, const CADData& obj)
{
	out << "\tSTLSurface " << obj.m_id <<
		"\t" << obj.m_name << "\n";

	return out;
}