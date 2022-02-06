#include "PCH.h"
#include "RigidBody.h"


RigidBody::RigidBody()
{
	m_nodes.resize(1);
}

RigidBody::RigidBody(unsigned int id, unsigned int RB_data_material_id, unsigned int cs_id, unsigned int node)
{
	m_nodes.resize(1);

	this->SetIDNumber(id);
	this->SetMaterial(RB_data_material_id);
	this->SetCS(cs_id);
	this->SetNodes(std::vector{ node });
}

RigidBody::RigidBody(unsigned int id, unsigned int RB_data_material_id, unsigned int cs_id, unsigned int node, const std::string& comment)
{
	m_nodes.resize(1);

	this->SetIDNumber(id);
	this->SetMaterial(RB_data_material_id);
	this->SetCS(cs_id);
	this->SetNodes(std::vector{ node });
	this->SetLabel(comment);
}

RigidBody::~RigidBody()
{
}

std::ostream& operator<<(std::ostream& out, const RigidBody& obj)
{
	if ( !obj.m_label.empty() )
		out << "\t//" << obj.m_label << "\n";
	
	out << "\tRigidBody_1 " << obj.m_id
		<< "\tRigidBodyData " << obj.m_material_id
		<< "\tCS " << obj.m_cs_id
		<< "\tNode " << obj.m_nodes[0] 
		<< "\n";

	return out;
}


