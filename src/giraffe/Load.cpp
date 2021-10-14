#include "PCH.h"
#include "Load.h"

Load::Load()
	: m_number(0), m_cs(1), m_is_math_code(false), m_is_external_file(false)
{}

Load::~Load()
{}



/// 
/// SETTERS
/// 

void Load::SetNumber(size_t number)
{
	m_number = number;
}
void Load::SetCoordinateSystem(size_t cs)
{
	m_cs = cs;
}
void Load::SetMathCodeOpt(bool option)
{
	m_is_math_code = option;
}
void Load::SetExternalFileOpt(bool option)
{
	m_is_external_file = option;
}

