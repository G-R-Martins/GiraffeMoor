#include "PCH.h"
#include "Displacement.h"


Displacement::Displacement()
	: m_number(0), m_is_math_code(false), m_is_external_file(false)
{}
Displacement::Displacement(size_t number, bool is_math_code, bool is_external_file)
	: m_number(number), m_is_math_code(is_math_code), m_is_external_file(is_external_file)
{}

Displacement::~Displacement()
{}

void Displacement::SetIDNumber(size_t number)
{
	m_number = number;
}

void Displacement::SetMathCodeOpt(bool option)
{
	m_is_math_code = option;
}

void Displacement::SetExternalFileOpt(bool option)
{
	m_is_external_file = option;
}

