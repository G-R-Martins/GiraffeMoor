#include "PCH.h"
#include "Element.h"

Element::Element()
	: m_id(0), m_label(""), m_material_id(0), m_section_id(0), m_cs_id(0),
	m_tot_nodes(0),	m_mark_segment_begin(false)
{}
Element::Element(const std::string & name)
	: m_material_id(0), m_section_id(0), m_id(0), m_tot_nodes(0), m_cs_id(0),
	m_mark_segment_begin(false), m_label(name)
{}
Element::Element(unsigned int id, unsigned int material_id, unsigned int section_id, unsigned int cs_id, 
	unsigned int tot_nodes, std::vector<unsigned int> nodes, bool segment_begin, const std::string& label)
	: m_id(id), m_label(label), m_material_id(material_id), m_section_id(section_id), m_cs_id(cs_id),
	m_tot_nodes(tot_nodes), m_mark_segment_begin(segment_begin)
{}


Element::~Element()
{}


void Element::SetIDNumber(unsigned int id)
{
	m_id = id;
}
void Element::SetLabel(const std::string& label)
{
	m_label = label;
}
void Element::SetMaterial(unsigned int material_id)
{
	m_material_id = material_id;
}
void Element::SetSection(unsigned int section_id)
{
	m_section_id = section_id;
}
void Element::SetCS(unsigned int cs_id)
{
	m_cs_id = cs_id;
}
void Element::SetTotNodes(unsigned int tot_nodes)
{
	m_tot_nodes = tot_nodes;
}
void Element::SetNodes(const std::vector<unsigned int>& nodes)
{
	m_nodes = nodes;
}
void Element::SetFirstElementOpt(bool option)
{
	m_mark_segment_begin = option;
}
