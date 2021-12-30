#include "PCH.h"
#include "LineSegment.h"
#include "Log.h"


LineSegment::LineSegment()
	: m_length(0.0), m_property_id(0), m_discretization(0),
	m_tot_nodes(0), m_tot_elements(0), m_nodeset_id(0),
	m_epsilon(0.0), m_gamma(0.0)
{}

LineSegment& LineSegment::operator=(LineSegment&& other) noexcept
{
	m_length = std::move(other.m_length);
	m_property_id = std::move(other.m_property_id);
	m_discretization = std::move(other.m_discretization);
	m_tot_nodes = std::move(other.m_tot_nodes);
	m_tot_elements = std::move(other.m_tot_elements);
	m_nodeset_id = std::move(other.m_nodeset_id);
	m_epsilon = std::move(other.m_epsilon);
	m_gamma = std::move(other.m_gamma);

	return *this;
}

LineSegment::LineSegment(LineSegment&& other) noexcept
	: m_length(std::move(other.m_length)), m_property_id(std::move(other.m_property_id)),
	m_discretization(std::move(other.m_discretization)), m_tot_nodes(std::move(other.m_tot_nodes)),
	m_tot_elements(std::move(other.m_tot_elements)), m_nodeset_id(std::move(other.m_nodeset_id)),
	m_epsilon(std::move(other.m_epsilon)), m_gamma(std::move(other.m_gamma))
{}


LineSegment::~LineSegment()
{}



///
/// SETTERS
///

void LineSegment::SetLength(double len)
{
	this->m_length = len;
}
void LineSegment::SetProperty(unsigned int property_id)
{
	this->m_property_id = property_id;
}
void LineSegment::SetDiscretization(unsigned int discretization)
{
	this->m_discretization = discretization;
}
void LineSegment::SetNNodes(unsigned int tot_nodes)
{
	this->m_tot_nodes = tot_nodes;
}
void LineSegment::SetNElements(unsigned int tot_elements)
{
	this->m_tot_elements = tot_elements;
}
void LineSegment::SetNodeSet(unsigned int nodeset_id)
{
	this->m_nodeset_id = nodeset_id;
}
void LineSegment::SetEpsilon(double epsilon)
{
	this->m_epsilon = epsilon;
}
void LineSegment::SetGamma(double gamma)
{
	this->m_gamma = gamma;
}


