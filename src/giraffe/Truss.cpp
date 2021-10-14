#include "PCH.h"
#include "Truss.h"


Truss::Truss()
{
	m_nodes.resize(2);
}


Truss::~Truss()
{}

std::ostream& operator<<(std::ostream& out, const Truss& obj)
{
	if (obj.m_mark_segment_begin)
		out << "\t//Segment begin\n";
	else if (!obj.m_label.empty())
		out << "\t//" << obj.m_label << "\n";
	
	out << "\tTruss_1 " << obj.m_number 
		<< "\tPipeSec " << obj.m_section <<
		"\tNodes " << obj.m_nodes[0] << " " << obj.m_nodes[1] 
		<< "\n";

	return out;
}


