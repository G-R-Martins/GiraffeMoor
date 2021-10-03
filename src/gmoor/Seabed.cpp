#include "PCH.h"
#include "Seabed.h"


Seabed::Seabed()
	: m_is_flat(true), m_pilot_node(0), m_nodeset(0),
	m_stiffness(0.0), m_damping(0.0), m_mu(0.0),
	m_pinball(0.0), m_radius(0.0)
{}

Seabed::~Seabed()
{}


/// 
/// SETTERS
/// 

void Seabed::SetFlatOption(bool is_flat)
{
	this->m_is_flat = is_flat;
}

void Seabed::SetPilotNode(unsigned int pilot_node)
{
	this->m_pilot_node = pilot_node;
}
void Seabed::SetNodeset(unsigned int nodeset)
{
	this->m_nodeset = nodeset;
}

void Seabed::SetStiffness(double stiffness)
{
	this->m_stiffness = stiffness;
}
void Seabed::SetDamping(double damping)
{
	this->m_damping = damping;
}
void Seabed::SetFrictionCoefficient(double mu)
{
	this->m_mu = mu;
}
void Seabed::SetPinball(double pinball)
{
	this->m_pinball = pinball;
}
void Seabed::SetRadius(double radius)
{
	this->m_radius = radius;
}
