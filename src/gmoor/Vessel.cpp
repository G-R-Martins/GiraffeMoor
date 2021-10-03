#include "PCH.h"
#include "Vessel.h"
#include "Log.h"


//Constructors
Vessel::Vessel()
	: m_number(0), m_keypoint(0), m_node(0), m_nodeset(0), m_rigid_nodeset(0),
	m_element(0), m_mass(0.0f), m_inertia_tensor({ 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f })
{}

//Destructor
Vessel::~Vessel()
{}



void Vessel::AddNode2RigidNodeset(unsigned int node)
{
	this->m_nodes_rigid_nodeset.emplace(node);
}

///
/// SETTERS
///

void Vessel::SetIDNumber(size_t number)
{
	m_number = number;
}

void Vessel::SetKeypoint(unsigned int keypoint)
{
	m_keypoint = keypoint;
}
void Vessel::SetNode(unsigned int node)
{
	m_node = node;
}
void Vessel::SetNodeset(unsigned int nodeset)
{
	m_nodeset = nodeset;
}
void Vessel::SetRigidNodeset(unsigned int rigid_nodeset)
{
	m_rigid_nodeset = rigid_nodeset;
}
void Vessel::SetElement(unsigned int element)
{
	m_element = element;
}

void Vessel::SetMass(float mass)
{
	m_mass = mass;
}
void Vessel::SetInertiaTensor(const std::array<float, 6>& inertia_tensor)
{
	m_inertia_tensor = inertia_tensor;
}

void Vessel::SetNodesRigidNodeset(const std::unordered_set<unsigned int>& nodes_rigid_nodeset)
{
	m_nodes_rigid_nodeset = nodes_rigid_nodeset;
}


/// 
/// Overloaded operators
/// 

bool operator< (Vessel& vessel1, Vessel& vessel2)
{
	return vessel1.m_number < vessel2.m_number;
}
bool operator> (Vessel& vessel1, Vessel& vessel2)
{
	return !(vessel1 < vessel2);
}
bool operator== (Vessel& vessel1, Vessel& vessel2)
{
	return vessel1.m_number == vessel2.m_number;
}
bool operator!= (Vessel& vessel1, Vessel& vessel2)
{
	return !(vessel1 == vessel2);
}
