#include "PCH.h"
#include "MoorEnvironment.h"
#include "Log.h"

double MoorEnvironment::s_gravity;


MoorEnvironment::MoorEnvironment()
	: m_rho_fluid(0.0), m_water_depth(0.0), 
	m_sea_current_exist(false), m_sea_current_is_constant(true)
{
	m_sea_current_vector.reserve(10);
}

MoorEnvironment::~MoorEnvironment()
{}



///
/// SETTERS
///

void MoorEnvironment::SetGravity(double g)
{
	MoorEnvironment::s_gravity = g;
}
void MoorEnvironment::SetRhoFluid(double rho_fluid)
{
	this->m_rho_fluid = rho_fluid;
}
void MoorEnvironment::SetWaterDepth(double water_depth)
{
	this->m_water_depth = water_depth;
}
void MoorEnvironment::SetBoolConstantSeaCurrent(bool is_constant)
{
	this->m_sea_current_is_constant = is_constant;
}
