#include "PCH.h"
#include "SameRotation.h"


SameRotation::SameRotation()
	: m_nodeA_id(0), m_nodeB_id(0)
{}
SameRotation::SameRotation(unsigned int nodeA_id, unsigned int nodeB_id)
	: m_nodeA_id(nodeA_id), m_nodeB_id(nodeB_id)
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
		<< "\tNodes " << obj.m_nodeA_id << " " << obj.m_nodeB_id << " "
		<< obj.m_booltable;

	return out;
}