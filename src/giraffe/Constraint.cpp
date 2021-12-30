#include "PCH.h"
#include "Constraint.h"

Constraint::Constraint()
	: m_id(0)
{
}


Constraint::~Constraint()
{}

void Constraint::SetIDNumber(unsigned int id)
{
	m_id = id;
}
