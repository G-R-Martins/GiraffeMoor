#include "PCH.h"
#include "PipeSection.h"


PipeSection::PipeSection()
	: m_id(0), m_is_beam(false), m_diameter(0.0), m_rho(0.0),
	m_EA(0.0), m_EI(0.0), m_GJ(0.0), m_GA(0.0), 
	m_CDt(0.0), m_CDn(0.0), m_CAt(0.0), m_CAn(0.0), 
	m_E(0.0), m_nu(0.0)
{}

PipeSection::PipeSection(unsigned int id, bool is_beam, double d, double rho,
	double EA, double EI, double GJ, double GA,
	double CDt, double CDn, double CAt, double CAn,
	double E, double nu)
	: m_id(id), m_is_beam(is_beam), m_diameter(d), m_rho(rho),
	m_EA(EA), m_EI(EI), m_GJ(GJ), m_GA(GA),
	m_CDt(CDt), m_CDn(CDn), m_CAt(CAt), m_CAn(CAn), m_E(E), m_nu(nu)
{}

PipeSection::PipeSection(const SegmentProperty& moor_prop)
	: m_id(moor_prop.GetNumber()), m_is_beam(moor_prop.IsBeam()), 
	m_diameter(moor_prop.GetDiameter()), m_rho(moor_prop.GetMass()),
	m_EA(moor_prop.GetEA()), m_EI(moor_prop.GetEI()), m_GJ(moor_prop.GetGJ()), m_GA(moor_prop.GetGA()),
	m_CDt(moor_prop.GetCDt()), m_CDn(moor_prop.GetCDn()), m_CAt(moor_prop.GetCAt()), m_CAn(moor_prop.GetCAn()),
	m_E(moor_prop.GetYoungMod()), m_nu(moor_prop.GetPoisson())
{}

PipeSection::~PipeSection()
{}



/// 
/// Overloaded operators
/// 

std::ostream& operator<<(std::ostream& out, const PipeSection& obj)
{
	out << 
		"\tPS "  << obj.m_id <<
		"\tEA "  << obj.m_EA <<
		"\tEI "  << obj.m_EI <<
		"\tGJ "  << obj.m_GJ <<
		"\tGA "  << obj.m_GA <<
		"\tRho " << obj.m_rho <<
		"\tCDt " << obj.m_CDt <<
		"\tCDn " << obj.m_CDn <<
		"\tCAt " << obj.m_CAt <<
		"\tCAn " << obj.m_CAn <<
		"\tDe "  << obj.m_diameter <<
		"\tDi "  << 0.0 <<
		"\n";

	return out;
}