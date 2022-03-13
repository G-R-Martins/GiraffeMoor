#include "PCH.h"
#include "NodalConstraint.h"

NodalConstraint::NodalConstraint()
	: m_node_set_id(0)
{}

NodalConstraint::NodalConstraint(unsigned int node_set_id, const BoolTable & UX, const BoolTable & UY, const BoolTable & UZ, const BoolTable & ROTX, const BoolTable & ROTY, const BoolTable & ROTZ)
	: m_node_set_id(node_set_id), m_UX(UX), m_UY(UY), m_UZ(UZ), m_ROTX(ROTX), m_ROTY(ROTY), m_ROTZ(ROTZ)
{}

NodalConstraint::NodalConstraint(unsigned int id, unsigned int node_set_id, const BoolTable & UX, const BoolTable & UY, const BoolTable & UZ, const BoolTable & ROTX, const BoolTable & ROTY, const BoolTable & ROTZ)
	: m_node_set_id(node_set_id), m_UX(UX), m_UY(UY), m_UZ(UZ), m_ROTX(ROTX), m_ROTY(ROTY), m_ROTZ(ROTZ)
{
	this->SetIDNumber(id);
}

NodalConstraint::~NodalConstraint()
{}


/// 
/// Overloaded operators
/// 

std::ostream& operator<<(std::ostream& out, NodalConstraint const& obj)
{
	out << "\tNodalConstraint " << obj.GetNumber()
		<< "\tNodeSet "			<< obj.m_node_set_id
		<< "\n\t\tUX\t\t"		<< obj.m_UX
		<< "\n\t\tUY\t\t"		<< obj.m_UY
		<< "\n\t\tUZ\t\t"		<< obj.m_UZ
		<< "\n\t\tROTY\t"		<< obj.m_ROTY
		<< "\n\t\tROTX\t"		<< obj.m_ROTX
		<< "\n\t\tROTZ\t"		<< obj.m_ROTZ
		<< "\n";

	return out;
}

void NodalConstraint::SetNodeset(unsigned int node_set_id)
{
	m_node_set_id = node_set_id;
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
