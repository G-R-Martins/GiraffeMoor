#include "PCH.h"
#include "Monitor.h"
#include "AuxFunctions.h"
#include "Log.h"


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
	if (!obj.nodes.empty())
	{
		out << "\tMonitorNodes\t";
		for (const int& node : obj.nodes)
			out << node << " ";
		out << "\n";
	}
	if (!obj.elements.empty())
	{
		out << "\tMonitorElements\t";
		for (const int& elem : obj.elements)
			out << elem << " ";
		out << "\n";
	}
	if (!obj.contacts.empty())
	{
		out << "\tMonitorContacts\t";
		for (const int& cont : obj.contacts)
			out << cont << " ";
		out << "\n";
	}
	if (!obj.node_sets.empty())
	{
		out << "\tMonitorNodeSets\t";
		for (const int& NS : obj.node_sets)
			out << NS << " ";
		out << "\n";
	}
	
	return out;
}
