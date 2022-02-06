#include "PCH.h"
#include "Pipe.h"


Pipe::Pipe()
{
	m_nodes.resize(3);
}

Pipe::Pipe(unsigned int id, bool segment_begin, unsigned int section_id, unsigned int cs_id, std::vector<unsigned int> nodes)
{
	m_nodes.resize(3);

	this->SetIDNumber(id);
	this->SetFirstElementOpt(segment_begin);
	this->SetSection(section_id);
	this->SetCS(cs_id);
	this->SetNodes(nodes);
}

Pipe::Pipe(unsigned int id, bool segment_begin, unsigned int section_id, unsigned int cs_id, std::vector<unsigned int> nodes, const std::string& comment)
{
	m_nodes.resize(3);

	this->SetIDNumber(id);
	this->SetFirstElementOpt(segment_begin);
	this->SetSection(section_id);
	this->SetCS(cs_id);
	this->SetNodes(nodes);
	this->SetLabel(comment);
}

Pipe::~Pipe()
{}

std::ostream& operator<<(std::ostream& out, const Pipe& obj)
{
	if ( obj.m_mark_segment_begin )
		out << "\t//Segment begin\n";
	else if ( !obj.m_label.empty() )
		out << "\t//" << obj.m_label << "\n";

	out << "\tPipe_1 " << obj.m_id
		<< "\tPipeSec " << obj.m_section_id
		<< "\tCS " << obj.m_cs_id
		<< "\tNodes " << obj.m_nodes[0] << " " << obj.m_nodes[1] << " " << obj.m_nodes[2] 
		<< "\n";

	return out;
}

