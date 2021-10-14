#include "PCH.h"
#include "RigidBodyData.h"


RigidBodyData::RigidBodyData()
	: m_number{ 0 }, m_mass{ 0.0 }, m_J_G{ 0.,0.,0.,0.,0.,0. }, m_G{ 0.,0.,0. }, 
	m_cad_id{ 0 }, m_comment{"\0"}
{}

RigidBodyData::RigidBodyData(size_t number, double mass, const std::array<double, 6>& J_G, const std::array<double, 3>& G, size_t cad_id, const std::string& comment)
	: m_number(number), m_mass(mass), m_J_G(J_G), m_G(G), m_cad_id(cad_id), m_comment(comment)
{}

RigidBodyData::~RigidBodyData()
{}



/// 
/// Overloaded operators
/// 

std::ostream& operator<<(std::ostream& out, const RigidBodyData& obj)

{
	if (!obj.m_comment.empty())
		out << "\t//" << obj.m_comment;
	
	out << "\n\tRBData " << obj.m_number 
		<< "\n\t\tMass " << obj.m_mass 
		<< "\n\t\tJ11 "  << obj.m_J_G[0] << "\tJ22 " << obj.m_J_G[1] << "\tJ33 " << obj.m_J_G[2] 
		<< "\n\t\tJ12 "  << obj.m_J_G[3] << "\tJ13 " << obj.m_J_G[4] << "\tJ23 " << obj.m_J_G[5] 
		<< "\n\t\tBarycenter " << obj.m_G[0] << "\t" << obj.m_G[1] << "\t" << obj.m_G[2];

	if (obj.m_cad_id)
		out << "\t\tCADData " << obj.m_cad_id << "\n";

	return out;
}
