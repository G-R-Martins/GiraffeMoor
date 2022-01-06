#include "PCH.h"
#include "SegmentProperty.h"
#include "Log.h"

SegmentProperty::SegmentProperty()
	: m_id(0), m_rho( 0.0 ), m_diameter(0.0),
	m_diameter_inner(0.0), m_diameter_contact(0.0),
	m_EA(0.0), m_EI(0.0), m_GJ(0.0), m_GA(0.0),
	m_CDt(0.0), m_CDn(0.0), m_CAt(0.0), m_CAn(0.0),
	m_E(0.0), m_nu(0.0), m_SG(1.0), m_MBS(0.0),
	m_is_chain(false), m_is_truss(false), m_is_beam(false), 
	m_wizard(WizardType::NONE), m_grade(Grade::NONE)
{}

SegmentProperty::~SegmentProperty()
{}




void SegmentProperty::SetIDNumber(unsigned int id)
{
	this->m_id = id;
}
void SegmentProperty::SetMass(double rho)
{
	this->m_rho = rho;
}
void SegmentProperty::SetDiameter(double diameter)
{
	if (this->m_wizard != WizardType::NONE)
		SetWizard(diameter);

	this->m_diameter = diameter;
}
void SegmentProperty::SetInnerDiameter(double diameter_inner)
{
	this->m_diameter_inner = diameter_inner;
}
void SegmentProperty::SetContactDiameter(double diameter_contact)
{
	this->m_diameter_contact = diameter_contact;
}
void SegmentProperty::SetEA(double EA)
{
	this->m_EA = EA;
}
void SegmentProperty::SetEI(double EI)
{
	this->m_EI = EI;
}
void SegmentProperty::SetGJ(double GJ)
{
	this->m_GJ = GJ;
}
void SegmentProperty::SetGA(double GA)
{
	this->m_GA = GA;
}
void SegmentProperty::SetCDt(double CDt)
{
	this->m_CDt = CDt;
}
void SegmentProperty::SetCDn(double CDn)
{
	this->m_CDn = CDn;
}
void SegmentProperty::SetCAt(double CAt)
{
	this->m_CAt = CAt;
}
void SegmentProperty::SetCAn(double CAn)
{
	this->m_CAn = CAn;
}
void SegmentProperty::SetYoungMod(double E)
{
	this->m_E = E;
}
void SegmentProperty::SetPoisson(double nu)
{
	this->m_nu = nu;
}
void SegmentProperty::SetSG(double SG)
{
	this->m_SG = SG;
}
void SegmentProperty::SetMBS(double MBS)
{
	this->m_MBS = MBS;
}
void SegmentProperty::SetMBSFromWizard(double d)
{
	if (this->m_is_chain)
	{
		double c = 0.0;
		switch (this->m_grade)
		{
		case Grade::ORQ:	c = 2.11e4; break;
		case Grade::TWO:	c = 1.37e4; break;
		case Grade::THREE:	c = 1.96e4; break;
		case Grade::R4:		c = 2.74e4; break;
		}
		this->m_MBS = c * pow(d, 2.0) * (44.0 - 80.0 * d) * 1'000.0;
	}
}
void SegmentProperty::SetGrade(std::string_view grade)
{
	m_grade = (grade == "ORQ") ? Grade::ORQ :
		(grade == "2") ? Grade::TWO :
		(grade == "3") ? Grade::THREE :
		(grade == "R4") ? Grade::R4 :
		Grade::NONE;
	
	// Check invalid option
	if (m_grade == Grade::NONE)
		Log::SetWarning("\nInvalid grade for segment property number " + std::to_string(m_id) + ". No MBS could be defined for this segment.");

}

void SegmentProperty::SetChainOpt(bool is_chain)
{
	this->m_is_chain = is_chain;
	this->m_is_truss = is_chain; // a chain uses truss FEM model
}

void SegmentProperty::SetTrussOpt(bool is_truss)
{
	this->m_is_truss = is_truss;
}

void SegmentProperty::SetBeamOpt(bool is_beam)
{
	this->m_is_beam = is_beam;
}


void SegmentProperty::SetWizardType(std::string_view type)
{
	// Transform input option to lower case 
	//std::transform(type.begin(), type.end(), type.begin(), [](char c) { return std::tolower(c); });
	
	if (type == "studlink")			this->m_wizard = WizardType::STUDLINK;
	else if (type == "studless")	this->m_wizard = WizardType::STUDLESS;
	else
		Log::SetWarning("\nInvalid wizard definition for the segment property number " + std::to_string(this->m_id));
}

void SegmentProperty::SetWizard(double d)
{
	
	switch (this->m_wizard)
	{
	case WizardType::STUDLESS:
		SetWizardStudless(d);
		break;
	case WizardType::STUDLINK:
		SetWizardStudlink(d);
		break;
	default:
		break;
	}

	SetMBSFromWizard(d);
}

void SegmentProperty::SetWizardStudless(double d)
{
	//Set properties
	this->m_diameter = 1.8 * d;
	this->m_diameter_inner = 0.0;
	this->m_diameter_contact = 3.35 * d;
	this->m_rho = pow( 19.9 * d, 2.0) * 1'000.0;
	this->m_EA = pow(0.854 * 100'000'000.0 * d, 2.0) * 1'000.0;
	this->m_EI = 0.0;
	this->m_CDn = 2.4;
	this->m_CDt = 1.15;
	this->m_CAn = 1.0;
	this->m_CAt = 0.5;
}
void SegmentProperty::SetWizardStudlink(double d)
{
	//Set properties
	this->m_diameter = 1.89 * d;
	this->m_diameter_inner = 0.0;
	this->m_diameter_contact = 3.6 * d;
	this->m_rho = pow(21.9 * d, 2.0) * 1'000.0;
	this->m_EA = pow(1.01 * 100'000'000.0 * d, 2.0) * 1'000.0;
	this->m_EI = 0.0;
	this->m_CDn = 2.6;
	this->m_CDt = 1.4;
	this->m_CAn = 1.0;
	this->m_CAt = 0.5;
}


//Overloaded operators
bool operator<(const SegmentProperty& obj1, const SegmentProperty& obj2)
{
	return obj1.m_id < obj2.m_id;
}
bool operator>(const SegmentProperty& obj1, const SegmentProperty& obj2)
{
	return !(obj1 < obj2);
}
bool operator==(const SegmentProperty& obj1, const SegmentProperty& obj2)
{
	return obj1.m_id == obj2.m_id;
}
bool operator!=(const SegmentProperty& obj1, const SegmentProperty& obj2)
{
	return !(obj1 == obj2);
}