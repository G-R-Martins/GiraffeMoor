#include "PCH.h"
#include "Log.h"
#include "CADData.h"


CADData::CADData()
	: m_number(0), m_name("\0")
{}

CADData::~CADData()
{}




/// 
/// SETTERS
/// 

void CADData::SetIDNumber(size_t number)
{
	this->m_number = number;
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
	return obj1.m_number < obj2.m_number;
}

bool operator>(const CADData& obj1, const CADData& obj2)
{
	return !(obj1 < obj2);
}

bool operator==(const CADData& obj1, const CADData& obj2)
{
	return obj1.m_number == obj2.m_number;
}

bool operator!=(const CADData& obj1, const CADData& obj2)
{
	return !(obj1 == obj2);
}



std::ostream& operator<<(std::ostream& out, const CADData& obj)
{
	out << "\tSTLSurface " << obj.m_number << 
		"\t" << obj.m_name << "\n";

	return out;
}