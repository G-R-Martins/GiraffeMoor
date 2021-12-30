#include "PCH.h"
#include "MoorConstraint.h"
#include "AuxFunctions.h"


MoorConstraint::MoorConstraint()
	: m_id(0), m_nodeset_id(0), m_constraints(6)
{}

MoorConstraint::~MoorConstraint()
{}


/// 
/// SETTERS
/// 

void MoorConstraint::SetIDNumber(unsigned int id)
{
	m_id = id;
}
void MoorConstraint::SetNodeset(unsigned int nodeset_id)
{
	m_nodeset_id = nodeset_id;
}

void MoorConstraint::SetDof(unsigned int dof_id, const std::list<bool>& constraints)
{
	m_constraints[dof_id] = constraints;
}
void MoorConstraint::PushToDof(unsigned int dof, bool constraint)
{
	m_constraints[dof].push_back(constraint);
}
void MoorConstraint::PushX(bool constraint)
{
	m_constraints[0].push_back(constraint);
}
void MoorConstraint::PushY(bool constraint)
{
	m_constraints[1].push_back(constraint);
}
void MoorConstraint::PushZ(bool constraint)
{
	m_constraints[2].push_back(constraint);
}
void MoorConstraint::PushRotX(bool constraint)
{
	m_constraints[3].push_back(constraint);
}
void MoorConstraint::PushRotY(bool constraint)
{
	m_constraints[4].push_back(constraint);
}
void MoorConstraint::PushRotZ(bool constraint)
{
	m_constraints[5].push_back(constraint);
}


/// 
/// Overloaded Operators
/// 

bool operator<(const MoorConstraint& obj1, const MoorConstraint& obj2)
{
	return obj1.m_id < obj2.m_id;
}
bool operator>(const MoorConstraint& obj1, const MoorConstraint& obj2)
{
	return !(obj1 < obj2);
}
bool operator==(const MoorConstraint& obj1, const MoorConstraint& obj2)
{
	return obj1.m_id == obj2.m_id;
}
bool operator!=(const MoorConstraint& obj1, const MoorConstraint& obj2)
{
	return !(obj1 == obj2);
}
