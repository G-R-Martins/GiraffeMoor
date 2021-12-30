#include "PCH.h"
#include "Displacement.h"


Displacement::Displacement()
	: m_id(0), m_is_math_code(false), m_is_external_file(false)
{}
Displacement::Displacement(unsigned int id, bool is_math_code, bool is_external_file)
	: m_id(id), m_is_math_code(is_math_code), m_is_external_file(is_external_file)
{}

Displacement::~Displacement()
{}

void Displacement::SetIDNumber(unsigned int id)
{
	m_id = id;
}

void Displacement::SetMathCodeOpt(bool option)
{
	m_is_math_code = option;
}

void Displacement::SetExternalFileOpt(bool option)
{
	m_is_external_file = option;
}

