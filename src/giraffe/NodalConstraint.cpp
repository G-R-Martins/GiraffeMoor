#include "PCH.h"
#include "NodalConstraint.h"

NodalConstraint::NodalConstraint()
	: m_node_set(0)
{}

NodalConstraint::NodalConstraint(size_t node_set, const BoolTable & UX, const BoolTable & UY, const BoolTable & UZ, const BoolTable & ROTX, const BoolTable & ROTY, const BoolTable & ROTZ)
	: m_node_set(node_set), m_UX(UX), m_UY(UY), m_UZ(UZ), m_ROTX(ROTX), m_ROTY(ROTY), m_ROTZ(ROTZ)
{}

NodalConstraint::~NodalConstraint()
{}


/// 
/// Overloaded operators
/// 

std::ostream& operator<<(std::ostream& out, NodalConstraint const& obj)
{
	out << "\tNodalConstraint " << obj.GetNumber()
		<< "\tNodeSet "			<< obj.m_node_set
		<< "\n"
		<< "\t\tUX\t\t"			<< obj.m_UX
		<< "\t\tUY\t\t"			<< obj.m_UY
		<< "\t\tUZ\t\t"			<< obj.m_UZ
		<< "\t\tROTY\t"			<< obj.m_ROTY
		<< "\t\tROTX\t"			<< obj.m_ROTX
		<< "\t\tROTZ\t"			<< obj.m_ROTZ;
	
	return out;
}

void NodalConstraint::SetNodeset(size_t node_set)
{
	m_node_set = node_set;
}

void NodalConstraint::SetUX(const BoolTable& UX)
{
	m_UX = UX;
}
void NodalConstraint::SetUY(const BoolTable& UY)
{
	m_UY = UY;
}
void NodalConstraint::SetUZ(const BoolTable& UZ)
{
	m_UZ = UZ;
}
void NodalConstraint::SetROTX(const BoolTable& ROTX)
{
	m_ROTX = ROTX;
}
void NodalConstraint::SetROTY(const BoolTable& ROTY)
{
	m_ROTY = ROTY;
}
void NodalConstraint::SetROTZ(const BoolTable& ROTZ)
{
	m_ROTZ = ROTZ;
}
