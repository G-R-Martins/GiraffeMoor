#include "PCH.h"
#include "Load.h"

Load::Load()
	: m_id(0), m_cs_id(1), m_is_math_code(false), m_is_external_file(false)
{}

Load::~Load()
{}



/// 
/// SETTERS
/// 

void Load::SetIDNumber(unsigned int id)
{
	m_id = id;
}
void Load::SetCoordinateSystem(unsigned int cs_id)
{
	m_cs_id = cs_id;
}
void Load::SetMathCodeOpt(bool option)
{
	m_is_math_code = option;
}
void Load::SetExternalFileOpt(bool option)
{
	m_is_external_file = option;
}

