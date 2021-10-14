#include "PCH.h"
#include "NSSS.h"


NSSS::NSSS()
	: m_number(0), m_node_set(0), m_surface_set(0), m_mu(0), 
	m_epn(0), m_cn(0), m_ept(0), m_ct(0), m_pinball(0), m_radius(0), 
	m_max_interactions(0), m_comment("\0")
{
	m_booltable.Clear();
}

NSSS::NSSS(const size_t& number, const size_t& node_set, const size_t& surface_set,
	double mu, double epn, double cn, double ept, double ct, 
	double pinball, double radius, unsigned int max_interactions, 
	BoolTable&& booltable, const std::string_view& comment)
	: m_number(number), m_node_set(node_set), m_surface_set(surface_set),
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
	
	out << "\tNSSS "			<< obj.m_number 
		<< "\tNodeSet "			<< obj.m_node_set 
		<< "\tSurfaceSet "		<< obj.m_surface_set 
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