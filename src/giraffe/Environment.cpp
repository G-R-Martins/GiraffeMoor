#include "PCH.h"
#include "Environment.h"


Environment::Environment()
	: m_gravity(0.0), m_rho_fluid(0.0), m_water_depth(0.0)
{	
	m_bool_g.Clear();
	m_bool_current.Clear();
}

Environment::~Environment()
{}


/// 
/// SETTERS
/// 

void Environment::SetGravity(double g)
{
	this->m_gravity = g;
}

void Environment::SetRhoFluid(double rho)
{
	this->m_rho_fluid = rho;
}

void Environment::SetWaterDepth(double wd)
{
	this->m_water_depth = wd;
}

void Environment::SetGravityBooltable(const BoolTable & bool_grav)
{
	this->m_bool_g = bool_grav;
}

void Environment::SetSeaCurrentBooltable(const BoolTable & bool_current)
{
	this->m_bool_current = bool_current;
}

void Environment::SetSeaCurrentVec(const std::vector<SeaCurrent>& current_vec)
{
	this->m_sea_current_vector = current_vec;
}


void Environment::SetNullSeaCurrent()
{
	m_sea_current_vector.emplace_back(0.0, 0.0, 0.0);
	m_sea_current_vector.emplace_back(m_water_depth, 0.0, 0.0);
}

/// 
/// Overloaded operators
/// 

std::ostream& operator<<(std::ostream& out, const Environment& obj)
{
	out << "\tGravityData\n\tG " << 0.0 << " " << 0.0 << " " << -obj.m_gravity << " " << obj.m_bool_g
		<< "\n\tOceanData\n\t\tRhoFluid " << obj.m_rho_fluid
		<< "\n\t\tSurfacePosition " << 0.0 << " " << 0.0 << " " << 0.0
		<< "\n\tSeaCurrent\tN " << obj.m_sea_current_vector.size() << " " << obj.m_bool_current << "\n";

	for (const SeaCurrent& sc : obj.GetSeaCurrentVec())
	{
		out << "\t\tDepth " << sc.GetDepth()
			<< "\tSpeed " << sc.GetSpeed()
			<< "\tAngle " << sc.GetAzimuth()
			<< "\n";
	}

	return out;
}
