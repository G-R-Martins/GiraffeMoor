#include "PCH.h"
#include "Pipe.h"


Pipe::Pipe()
{
	m_nodes.resize(3);
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

