#include "PCH.h"
#include "RigidBody.h"


RigidBody::RigidBody()
{
	m_nodes.resize(1);
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


