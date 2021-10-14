#include "PCH.h"
#include "RigidNodeSet.h"


RigidNodeSet::RigidNodeSet()
	: m_pilot_node(0), m_node_set(0), m_comment("")
{}
RigidNodeSet::RigidNodeSet(size_t pilot_node, size_t node_set, const std::string& comment)
	: m_pilot_node(pilot_node), m_node_set(node_set), m_comment(comment)
{}


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
		<< "\tPilotNode " << obj.m_pilot_node
		<< "\tNodeSet " << obj.m_node_set << " " << obj.m_booltable;

	return out;
}
