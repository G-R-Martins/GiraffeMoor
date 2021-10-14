#include "PCH.h"
#include "SameRotation.h"


SameRotation::SameRotation()
	: m_node_A(0), m_node_B(0)
{}
SameRotation::SameRotation(size_t node_A, size_t node_B)
	: m_node_A(node_A), m_node_B(node_B)
{}

SameRotation::~SameRotation()
{
	m_booltable.Clear();
}


/// 
/// Overloaded operators
/// 

std::ostream& operator<<(std::ostream& out, const SameRotation& obj) {
	out << "\tSameRotation " << obj.GetIDNumber() 
		<< "\tNodes " << obj.m_node_A << " " << obj.m_node_B << " " 
		<< obj.m_booltable;

	return out;
}