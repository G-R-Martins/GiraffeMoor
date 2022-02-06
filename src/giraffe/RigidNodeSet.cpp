#include "PCH.h"
#include "RigidNodeSet.h"


RigidNodeSet::RigidNodeSet()
	: m_pilot_node_id(0), m_node_set_id(0), m_comment("")
{}

RigidNodeSet::RigidNodeSet(unsigned int pilot_node_id, unsigned int nodeset_id, const std::string& comment)
	: m_pilot_node_id(pilot_node_id), m_node_set_id(nodeset_id), m_comment(comment)
{}

RigidNodeSet::RigidNodeSet(unsigned int id, unsigned int pilot_node_id, unsigned int nodeset_id, const BoolTable & bool_table, const std::string & comment)
	: m_pilot_node_id(pilot_node_id), m_node_set_id(nodeset_id), m_comment(comment)
{
	this->SetIDNumber(id);
	this->SetBoolTable(bool_table);
}


RigidNodeSet::~RigidNodeSet()
{
	m_booltable.Clear();
}


/// 
/// Overloaded operators
/// 

std::ostream& operator<<(std::ostream& out, const RigidNodeSet& obj)
{
	if ( !obj.m_comment.empty() )
		out << "\t//" << obj.m_comment << "\n";
	out << "\tRigidNodeSet " << obj.GetIDNumber()
		<< "\tPilotNode " << obj.m_pilot_node_id
		<< "\tNodeSet " << obj.m_node_set_id << " " << obj.m_booltable;

	return out;
}
