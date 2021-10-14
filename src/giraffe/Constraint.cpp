#include "PCH.h"
#include "Constraint.h"

Constraint::Constraint()
	: m_number(0)
{
}


Constraint::~Constraint()
{}

void Constraint::SetIDNumber(size_t number)
{
	m_number = number;
}
