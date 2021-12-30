#include "PCH.h"
#include "Monitor.h"


Monitor::Monitor()
	: sample(1), bool_nodes_fairleads(true), bool_nodes_anchors(false), bool_nodes_tdz(false),
	bool_nodes_vessel(true), bool_elements_fairleads(false), bool_elements_anchors(false),
	bool_elements_tdz(false), bool_elements_vessel(false), bool_contact_seabed_moor(false)
{}

Monitor::~Monitor()
{}



/// 
/// Overloaded operators
/// 

std::ostream& operator<<(std::ostream& out, const Monitor& obj)
{
	out << "\tSample "<< obj.sample << "\n";
	if (!obj.nodes_id.empty())
	{
		out << "\tMonitorNodes\t";
		for (const unsigned int& node : obj.nodes_id)
			out << node << " ";
		out << "\n";
	}
	if (!obj.elements_id.empty())
	{
		out << "\tMonitorElements\t";
		for (const unsigned int& elem : obj.elements_id)
			out << elem << " ";
		out << "\n";
	}
	if (!obj.contacts_id.empty())
	{
		out << "\tMonitorContacts\t";
		for (const unsigned int& cont : obj.contacts_id)
			out << cont << " ";
		out << "\n";
	}
	if (!obj.node_sets_id.empty())
	{
		out << "\tMonitorNodeSets\t";
		for (const unsigned int& NS : obj.node_sets_id)
			out << NS << " ";
		out << "\n";
	}
	
	return out;
}
