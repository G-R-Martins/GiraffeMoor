#include "PCH.h"
#include "Monitor.h"


Monitor::Monitor()
	: m_nodes_id{}, m_elements_id{}, m_contacts_id{}, m_node_sets_id{},
	m_nodes_sequence_hint{}, m_elements_sequence_hint{},
	m_sample(1), m_nodes_fairleads_opt(true), m_nodes_anchors_opt(false),
	m_nodes_tdz_opt(false), m_nodes_vessel_opt(false),
	m_elements_fairleads_opt(false), m_elements_anchors_opt(false),
	m_elements_tdz_opt(false), m_elements_vessel_opt(false),
	m_contact_seabed_lines_opt(false)
{}

Monitor::~Monitor()
{}

void Monitor::PushNodeID(unsigned int node_id)
{
	m_nodes_id.emplace_front(node_id);
}

void Monitor::PushElementID(unsigned int element_id)
{
	m_elements_id.emplace_front(element_id);
}

void Monitor::PushContactID(unsigned int contact_id)
{
	m_contacts_id.emplace_front(contact_id);
}

void Monitor::PushNodeSetID(unsigned int node_set_id)
{
	m_node_sets_id.emplace_front(node_set_id);
}

NodesSequence* Monitor::AddNodesSequence(unsigned int nodes, unsigned int begin, unsigned int increment)
{
	this->m_nodes_sequence_hint.emplace_front() = { nodes, begin, increment };
	return &this->m_nodes_sequence_hint.front();
}

NodesSequence* Monitor::AddNodesSequence()
{
	return &this->m_nodes_sequence_hint.emplace_front();
}

void Monitor::PushNodesSequence(unsigned int nodes, unsigned int begin, unsigned int increment)
{
	this->m_nodes_sequence_hint.emplace_front() = { nodes, begin, increment };
}

void Monitor::PushNodesSequence()
{
	this->m_nodes_sequence_hint.emplace_front();
}

ElementsSequence* Monitor::AddElementsSequence(unsigned int elements, unsigned int begin, unsigned int increment)
{
	this->m_elements_sequence_hint.emplace_front() = { elements, begin, increment };
	return &this->m_elements_sequence_hint.front();
}

ElementsSequence* Monitor::AddElementsSequence()
{
	return &this->m_elements_sequence_hint.emplace_front();
}

void Monitor::PushElementsSequence(unsigned int elements, unsigned int begin, unsigned int increment)
{
	this->m_elements_sequence_hint.emplace_front() = { elements, begin, increment };	
}

void Monitor::PushElementsSequence()
{
	this->m_elements_sequence_hint.emplace_front();
}

void Monitor::SetSample(unsigned int sample)
{
	this->m_sample = sample;
}

void Monitor::SetMonitorFairleadNodesOpt(bool nodes_fairleads_opt)
{
	this->m_nodes_fairleads_opt = nodes_fairleads_opt;
}

void Monitor::SetMonitorAnchorNodesOpt(bool nodes_anchors_opt)
{
	this->m_nodes_anchors_opt = nodes_anchors_opt;
}

void Monitor::SetMonitorTDZNodesOpt(bool nodes_tdz_opt)
{
	this->m_nodes_tdz_opt = nodes_tdz_opt;
}

void Monitor::SetMonitorVesselNodesOpt(bool nodes_vessel_opt)
{
	this->m_nodes_vessel_opt = nodes_vessel_opt;
}

void Monitor::SetMonitorFairleadElementsOpt(bool elements_fairleads_opt)
{
	this->m_elements_fairleads_opt = elements_fairleads_opt;
}

void Monitor::SetMonitorAnchorElementsOpt(bool elements_anchors_opt)
{
	this->m_elements_anchors_opt = elements_anchors_opt;
}

void Monitor::SetMonitorTDZElementsOpt(bool elements_tdz_opt)
{
	this->m_elements_tdz_opt = elements_tdz_opt;
}

void Monitor::SetMonitorVesselElementsOpt(bool elements_vessel_opt)
{
	this->m_elements_vessel_opt = elements_vessel_opt;
}

void Monitor::SetMonitorLinesSeabedContactOpt(bool contact_seabed_lines_opt)
{
	this->m_contact_seabed_lines_opt = contact_seabed_lines_opt;
}

void Monitor::SetAllNodesFlags(bool option)
{
	m_nodes_anchors_opt = option;
	m_nodes_fairleads_opt = option;
	m_nodes_tdz_opt = option;
	m_nodes_vessel_opt = option;
}

void Monitor::SetAllElementsFlags(bool option)
{
	m_elements_anchors_opt = option;
	m_elements_fairleads_opt = option;
	m_elements_tdz_opt = option;
	m_elements_vessel_opt = option;
}



/// 
/// Overloaded operators
/// 

std::ostream& operator<<(std::ostream& out, const Monitor& obj)
{
	out << "\tSample "<< obj.m_sample << "\n";
	if (!obj.m_nodes_id.empty())
	{
		out << "\tMonitorNodes\t";
		for (const auto& node : obj.m_nodes_id)
			out << node << " ";
		out << "\n";
	}
	if (!obj.m_elements_id.empty())
	{
		out << "\tMonitorElements\t";
		for (const auto& elem : obj.m_elements_id)
			out << elem << " ";
		out << "\n";
	}
	if (!obj.m_contacts_id.empty())
	{
		out << "\tMonitorContacts\t";
		for (const auto& cont : obj.m_contacts_id)
			out << cont << " ";
		out << "\n";
	}
	if (!obj.m_node_sets_id.empty())
	{
		out << "\tMonitorNodeSets\t";
		for (const auto& NS : obj.m_node_sets_id)
			out << NS << " ";
		out << "\n";
	}
	
	return out;
}
