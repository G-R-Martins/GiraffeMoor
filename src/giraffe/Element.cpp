#include "PCH.h"
#include "Element.h"

Element::Element()
	: m_number(0), m_label(""), m_material(0), m_section(0), m_cs(0), 
	m_tot_nodes(0),	m_mark_segment_begin(false)
{}
Element::Element(const std::string & name)
	: m_material(0), m_section(0), m_number(0), m_tot_nodes(0), m_cs(0), 
	m_mark_segment_begin(false), m_label(name)
{}
Element::Element(size_t number, size_t material, size_t section, size_t cs, unsigned int tot_nodes, std::vector<unsigned int> nodes, bool segment_begin, const std::string& label)
	: m_number(number), m_label(label), m_material(material), m_section(section), m_cs(cs),
	m_tot_nodes(tot_nodes), m_mark_segment_begin(segment_begin)
{}


Element::~Element()
{}


void Element::SetIDNumber(size_t number)
{
	m_number = number;
}
void Element::SetLabel(const std::string& label)
{
	m_label = label;
}
void Element::SetMaterial(size_t material)
{
	m_material = material;
}
void Element::SetSection(size_t section)
{
	m_section = section;
}
void Element::SetCS(size_t cs)
{
	m_cs = cs;
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
