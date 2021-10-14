#include "PCH.h"
#include "LineSegment.h"
#include "Log.h"


LineSegment::LineSegment()
	: m_length(0.0), m_property(0), m_discretization(0), 
	m_tot_nodes(0), m_tot_elements(0), m_nodeset(0), 
	m_epsilon(0.0), m_gamma(0.0)
{}

LineSegment& LineSegment::operator=(LineSegment&& other) noexcept
{
	m_length = std::move(other.m_length);
	m_property = std::move(other.m_property);
	m_discretization = std::move(other.m_discretization);
	m_tot_nodes = std::move(other.m_tot_nodes);
	m_tot_elements = std::move(other.m_tot_elements);
	m_nodeset = std::move(other.m_nodeset);
	m_epsilon = std::move(other.m_epsilon);
	m_gamma = std::move(other.m_gamma);

	return *this;
}

LineSegment::LineSegment(LineSegment&& other) noexcept
	: m_length(std::move(other.m_length)), m_property(std::move(other.m_property)),
	m_discretization(std::move(other.m_discretization)), m_tot_nodes(std::move(other.m_tot_nodes)),
	m_tot_elements(std::move(other.m_tot_elements)), m_nodeset(std::move(other.m_nodeset)),
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
void LineSegment::SetProperty(size_t property)
{
	this->m_property = property;
}
void LineSegment::SetDiscretization(unsigned int discretization)
{
	this->m_discretization = discretization;
}
void LineSegment::SetNNodes(size_t nodes)
{
	this->m_tot_nodes = nodes;
}
void LineSegment::SetNElements(size_t elements)
{
	this->m_tot_elements = elements;
}
void LineSegment::SetNodeSet(size_t nodeset)
{
	this->m_nodeset = nodeset;
}
void LineSegment::SetEpsilon(double epsilon)
{
	this->m_epsilon = epsilon;
}
void LineSegment::SetGamma(double gamma)
{
	this->m_gamma = gamma;
}


