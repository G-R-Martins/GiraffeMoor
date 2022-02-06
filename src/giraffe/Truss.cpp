#include "PCH.h"
#include "Truss.h"


Truss::Truss()
{
	m_nodes.resize(2);
}

Truss::Truss(unsigned int id, bool segment_begin, unsigned int section_id, unsigned int node1, unsigned int node2)
{
	m_nodes.resize(2);

	this->SetIDNumber(id);
	this->SetFirstElementOpt(segment_begin);
	this->SetSection(section_id);
	this->SetNodes(std::vector{ node1,node2 });
}

Truss::Truss(unsigned int id, bool segment_begin, unsigned int section_id, unsigned int node1, unsigned int node2, const std::string& comment)
{
	m_nodes.resize(2);

	this->SetIDNumber(id);
	this->SetFirstElementOpt(segment_begin);
	this->SetSection(section_id);
	this->SetNodes(std::vector{ node1,node2 });
	this->SetLabel(comment);
}


Truss::~Truss()
{}

std::ostream& operator<<(std::ostream& out, const Truss& obj)
{
	if (obj.m_mark_segment_begin)
		out << "\t//Segment begin\n";
	else if (!obj.m_label.empty())
		out << "\t//" << obj.m_label << "\n";
	
	out << "\tTruss_1 " << obj.m_id
		<< "\tPipeSec " << obj.m_section_id <<
		"\tNodes " << obj.m_nodes[0] << " " << obj.m_nodes[1] 
		<< "\n";

	return out;
}


