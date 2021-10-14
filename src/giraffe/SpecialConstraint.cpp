#include "PCH.h"
#include "SpecialConstraint.h"


SpecialConstraint::SpecialConstraint()
	: m_number(0)
{
	m_booltable.Clear();
}

SpecialConstraint::SpecialConstraint(size_t number, const BoolTable& booltable)
	: m_number(number), m_booltable(booltable)
{}

SpecialConstraint::~SpecialConstraint()
{}

void SpecialConstraint::SetIDNumber(size_t number)
{
	m_number = number;
}

void SpecialConstraint::SetBoolTable(const BoolTable& booltable)
{
	m_booltable = booltable;
}


/// 
/// SETTERS
/// 