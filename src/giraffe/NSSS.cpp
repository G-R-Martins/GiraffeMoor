#include "PCH.h"
#include "NSSS.h"


NSSS::NSSS()
	: m_id(0), m_node_set_id(0), m_surface_set_id(0), m_mu(0),
	m_epn(0), m_cn(0), m_ept(0), m_ct(0), m_pinball(0), m_radius(0), 
	m_max_interactions(0), m_comment("\0")
{
	m_booltable.Clear();
}

NSSS::NSSS(const unsigned int& id, const unsigned int& node_set_id, const unsigned int& surface_set_id,
	double mu, double epn, double cn, double ept, double ct, 
	double pinball, double radius, unsigned int max_interactions, 
	BoolTable&& booltable, const std::string& comment)
	: m_id(id), m_node_set_id(node_set_id), m_surface_set_id(surface_set_id),
		m_mu(mu), m_epn(epn), m_cn(cn), m_ept(ept), m_ct(ct),
		m_pinball(pinball), m_radius(radius), m_max_interactions(max_interactions),
		m_booltable(booltable), m_comment(comment)
{}

NSSS::~NSSS()
{
	m_booltable.Clear();
}



/// 
/// Overloaded operators
/// 

std::ostream& operator<<(std::ostream& out, const NSSS& obj)
{
	if ( !obj.m_comment.empty() )
		out << "//" << obj.m_comment << "\n";
	
	out << "\tNSSS "			<< obj.m_id
		<< "\tNodeSet "			<< obj.m_node_set_id
		<< "\tSurfaceSet "		<< obj.m_surface_set_id
		<< "\tMU "				<< obj.m_mu 
		<< "\tEPN "				<< obj.m_epn 
		<< "\tCN "				<< obj.m_cn 
		<< "\tEPT "				<< obj.m_ept 
		<< "\tCT "				<< obj.m_ct 
		<< "\tPinball "			<< obj.m_pinball 
		<< "\tRadius "			<< obj.m_radius 
		<< "\tMaxPointwiseInt " << obj.m_max_interactions 
		<< " "					<< obj.m_booltable;

	return out;
}