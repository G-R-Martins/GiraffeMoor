#include "PCH.h"
#include "Vessel.h"


//Constructors
Vessel::Vessel()
	: m_id(0), m_keypoint_id(0), m_node_id(0), m_nodeset_id(0), m_rigid_nodeset_id(0),
	m_element_id(0), m_mass(0.0f), m_inertia_tensor({ 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f })
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

void Vessel::SetIDNumber(unsigned int id)
{
	m_id = id;
}

void Vessel::SetKeypoint(unsigned int keypoint_id)
{
	m_keypoint_id = keypoint_id;
}
void Vessel::SetNode(unsigned int node_id)
{
	m_node_id = node_id;
}
void Vessel::SetNodeset(unsigned int nodeset_id)
{
	m_nodeset_id = nodeset_id;
}
void Vessel::SetRigidNodeset(unsigned int rigid_nodeset_id)
{
	m_rigid_nodeset_id = rigid_nodeset_id;
}
void Vessel::SetElement(unsigned int element_id)
{
	m_element_id = element_id;
}

void Vessel::SetMass(double mass)
{
	m_mass = mass;
}
void Vessel::SetInertiaTensor(const std::array<double, 6>& inertia_tensor)
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
	return vessel1.m_id < vessel2.m_id;
}
bool operator> (Vessel& vessel1, Vessel& vessel2)
{
	return !(vessel1 < vessel2);
}
bool operator== (Vessel& vessel1, Vessel& vessel2)
{
	return vessel1.m_id == vessel2.m_id;
}
bool operator!= (Vessel& vessel1, Vessel& vessel2)
{
	return !(vessel1 == vessel2);
}
