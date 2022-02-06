#include "PCH.h"
#include "SameDisplacement.h"


SameDisplacement::SameDisplacement()
	: m_nodeA_id(0), m_nodeB_id(0), m_initial_load_step_id(0)
{}

SameDisplacement::SameDisplacement(unsigned int nodeA_id, unsigned int nodeB_id, unsigned int initial_load_step_id)
	: m_nodeA_id(nodeA_id), m_nodeB_id(nodeB_id), m_initial_load_step_id(initial_load_step_id)
{}

SameDisplacement::SameDisplacement(unsigned int id, unsigned int nodeA_id, unsigned int nodeB_id, const BoolTable & bool_table, unsigned int initial_load_step_id)
	: m_nodeA_id(nodeA_id), m_nodeB_id(nodeB_id), m_initial_load_step_id(initial_load_step_id)
{
	this->SetIDNumber(id);
	this->SetBoolTable(bool_table);
}

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
		<< "\tNodes " << obj.m_nodeA_id << " " << obj.m_nodeB_id << " "
		<< obj.m_booltable;

	return out;
}
