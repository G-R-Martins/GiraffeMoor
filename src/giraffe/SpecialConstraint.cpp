#include "PCH.h"
#include "SpecialConstraint.h"


SpecialConstraint::SpecialConstraint()
	: m_id(0)
{
	m_booltable.Clear();
}

SpecialConstraint::SpecialConstraint(unsigned int id, const BoolTable& booltable)
	: m_id(id), m_booltable(booltable)
{}

SpecialConstraint::~SpecialConstraint()
{}



/// 
/// SETTERS
/// 

void SpecialConstraint::SetIDNumber(unsigned int id)
{
	m_id = id;
}

void SpecialConstraint::SetBoolTable(const BoolTable& booltable)
{
	m_booltable = booltable;
}
