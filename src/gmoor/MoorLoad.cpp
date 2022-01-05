#include "PCH.h"
#include "MoorLoad.h"


MoorLoad::MoorLoad()
	: m_node_id(0), m_segment_id(1), m_line_id(0)
{}

MoorLoad::~MoorLoad()
{}


//Set functions

void MoorLoad::SetNodeID(unsigned int node_id)
{
	this->m_node_id = node_id; 
	SetIDOpt(true);
}
void MoorLoad::SetSegment(unsigned int segment_id)
{
	this->m_segment_id = segment_id; 
	SetSegmentIDOpt(true);
}
void MoorLoad::SetLineID(unsigned int line_id)
{
	this->m_line_id = line_id;
	SetIDOpt(true);
}
void MoorLoad::SetDescription(std::string_view desc)
{
	this->m_description = desc;
	SetDescriptionOpt(true);
}


