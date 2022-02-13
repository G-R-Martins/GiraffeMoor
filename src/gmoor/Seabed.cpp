#include "PCH.h"
#include "Seabed.h"


Seabed::Seabed()
	: m_is_flat(true), m_pilot_node_id(0), m_nodeset_id(0),
	m_stiffness(0.0), m_stiffness_tangential_factor(0.1), 
	m_damping(0.0), m_mu(0.0), m_pinball(0.0), m_radius(0.0)
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
void Seabed::SetPilotNode(unsigned int pilot_node_id)
{
	this->m_pilot_node_id = pilot_node_id;
}
void Seabed::SetNodeset(unsigned int nodeset_id)
{
	this->m_nodeset_id = nodeset_id;
}
void Seabed::SetStiffness(double stiffness)
{
	this->m_stiffness = stiffness;
}
void Seabed::SetStiffnessTangentialFactor(double factor)
{
	this->m_stiffness_tangential_factor = factor;
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
