#include "PCH.h"
#include "Log.h"
#include "CADData.h"


CADData::CADData()
	: m_number(0), m_name("\0")
{}

CADData::~CADData()
{}



void CADData::WriteGiraffeModelFile(std::ostream& fout) const
{
	fout << "\tSTLSurface " << m_number << 
		"\t" << m_name << "\n";
}


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


