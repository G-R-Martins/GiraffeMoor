#include "PCH.h"
#include "Element.h"

Element::Element()
	: material(0), section(0), number(0), n_nodes(0), cs(0), 
	mark_segment_begin(false)
{}

Element::Element(const std::string & name)
	: material(0), section(0), number(0), n_nodes(0), cs(0), 
	mark_segment_begin(false), label(name)
{}


Element::~Element()
{}


/// 
/// Get functions
/// 
std::string const& Element::GetLabel() const
{
	return this->label;
}
std::string& Element::GetLabel()
{
	return this->label;
}
unsigned int Element::GetMaterial() const
{
	return this->material;
}
unsigned int Element::GetSection() const
{
	return this->section;
}
unsigned int Element::GetNumber() const
{
	return this->number;
}
unsigned int Element::GetNNodes() const
{
	return this->n_nodes;
}
unsigned int Element::GetCS() const
{
	return this->cs;
}
std::vector<unsigned int> const& Element::GetNodes() const
{
	return this->nodes;
}
std::vector<unsigned int>& Element::GetNodes()
{
	return this->nodes;
}
bool Element::CheckIfIsFirstElement() const
{
	return this->mark_segment_begin;
}

/// 
/// Set functions
/// 
void Element::SetLabel(const std::string& name)
{
	this->label = name;
}
void Element::SetMaterial(unsigned int mat)
{
	this->material = mat;
}
void Element::SetSection(unsigned int sec)
{
	this->section = sec;
}
void Element::SetNumber(unsigned int num)
{
	this->number = num;
}
void Element::SetNNodes(unsigned int nnodes)
{
	this->n_nodes = nnodes;
}
void Element::SetCS(unsigned int coord_sys)
{
	this->cs = coord_sys;
}
void Element::SetNodes(const std::vector<unsigned int>& n_vec)
{
	this->nodes = n_vec;
}
void Element::SetFirstElementBool(bool bool_option)
{
	this->mark_segment_begin = bool_option;
}
