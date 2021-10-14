#include "PCH.h"
#include "SameDisplacement.h"


SameDisplacement::SameDisplacement()
	: m_node_A(0), m_node_B(0), m_initial_load_step(0)
{}
SameDisplacement::SameDisplacement(size_t node_A, size_t node_B, size_t initial_load_step)
	: m_node_A(node_A), m_node_B(node_B), m_initial_load_step(initial_load_step)
{}

SameDisplacement::~SameDisplacement()
{
	m_booltable.Clear();
}


/// 
/// Overloaded operators
/// 

std::ostream& operator<<(std::ostream& out, const SameDisplacement& obj)
{
	out << "\tSameDisplacement " << obj.GetIDNumber() 
		<< "\tNodes " << obj.m_node_A << " " << obj.m_node_B << " " 
		<< obj.m_booltable;

	return out;
}
