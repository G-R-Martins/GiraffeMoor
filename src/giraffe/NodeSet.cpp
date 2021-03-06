#include "PCH.h"
#include "NodeSet.h"


NodeSet::NodeSet()
	: m_id(0), m_total_nodes(0), m_node_init(0), m_increment(0), m_comment("\0")
{}

NodeSet::NodeSet(unsigned int id, const std::vector<unsigned int>& nodes, const std::string& comment)
	: m_id(id), m_total_nodes(0), m_node_init(0), m_increment(0), m_comment(comment), 
	m_nodes(nodes)
{}
NodeSet::NodeSet(unsigned int id, const std::vector<unsigned int>& nodes, std::string& comment)
	: m_id(0), m_total_nodes(0), m_node_init(0), m_increment(0), m_comment(comment), 
	m_nodes(nodes)
{}

NodeSet::NodeSet(unsigned int id, unsigned int total_nodes, unsigned int node_init, 
	unsigned int increment, const std::string& comment)
	: m_id(id), m_total_nodes(total_nodes), m_node_init(node_init), m_increment(increment), m_comment(comment)
{}
NodeSet::NodeSet(unsigned int id, unsigned int total_nodes, unsigned int node_init, 
	unsigned int increment, std::string& comment)
	: m_id(id), m_total_nodes(total_nodes), m_node_init(node_init), m_increment(increment), m_comment(comment)
{}

NodeSet::~NodeSet()
{}


/// 
/// SETTERS
/// 

void NodeSet::SetIDNumber(unsigned int id)
{
	m_id = id;
}

void NodeSet::SetNNodes(unsigned int total_nodes)
{
	m_total_nodes = total_nodes;
}

void NodeSet::SetNodeInit(unsigned int node_init)
{
	m_node_init = node_init;
}

void NodeSet::SetIncrement(unsigned int increment)
{
	m_increment = increment;
}

void NodeSet::SetComment(const std::string& comment)
{
	m_comment = comment;
}

void NodeSet::SetNodes(std::vector<unsigned int> nodes)
{
	m_nodes = nodes;
}



/// 
/// Overloaded operators
/// 

bool operator<(const NodeSet& ns1, const NodeSet& ns2)
{
	return ns1.m_id < ns2.m_id;
}

bool operator>(const NodeSet& ns1, const NodeSet& ns2)
{
	return !(ns1<ns2);
}

bool operator==(const NodeSet& ns1, const NodeSet& ns2)
{
	return ns1.m_id == ns2.m_id;
}

bool operator!=(const NodeSet& ns1, const NodeSet& ns2)
{
	return !(ns1==ns2);
}


std::ostream& operator<<(std::ostream& out, const NodeSet& obj)
{
	out << "\t//" << obj.m_comment << "\n";
	if (obj.m_total_nodes > 0)
	{
		out << "\tNodeSet "				<< obj.m_id 
			<<	"\tNodes "				<< obj.m_total_nodes 
			<< "\tSequence Initial "	<< obj.m_node_init 
			<< "\tIncrement "			<< obj.m_increment;
	}
	else
	{
		out << "\tNodeSet "		<< obj.m_id 
			<< "\tNodes "		<< obj.m_nodes.size() 
			<< "\tList ";
		for (auto node : obj.m_nodes)
			out << node << " ";
	}
	out << "\n";

	return out;
}