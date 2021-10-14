#include "PCH.h"
#include "Dynamic.h"

Dynamic::Dynamic()
	: m_alpha_ray(0.0), m_beta_ray(0.0), m_gamma_new(0.0), m_beta_new(0.0),
	m_update(0)
{}

Dynamic::Dynamic(double alpha_ray, double beta_ray, double gamma_new, double beta_new, int update)
	: m_alpha_ray(alpha_ray), m_beta_ray(beta_ray), m_gamma_new(gamma_new), m_beta_new(beta_new),
	m_update(update)
{
}

Dynamic::~Dynamic()
{}

void Dynamic::SetRayleighDamping(double alpha_ray, double beta_ray)
{
	m_alpha_ray = alpha_ray;
	m_beta_ray = beta_ray;
}

void Dynamic::SetRayleighAlpha(double alpha_ray)
{
	m_alpha_ray = alpha_ray;
}

void Dynamic::SetRayleighBeta(double beta_ray)
{
	m_beta_ray = beta_ray;
}

void Dynamic::SetNewmarkCoefficients(double gamma_new, double beta_new)
{
	m_gamma_new = gamma_new;
	m_beta_new = beta_new;
}

void Dynamic::SetNewmarkGamma(double gamma_new)
{
	m_gamma_new = gamma_new;
}

void Dynamic::SetNewmarkBeta(double beta_new)
{
	m_beta_new = beta_new;
}

void Dynamic::SetUpdate(int update)
{
	m_update = update;
}


/// 
/// Overloaded operators
/// 

std::ofstream& operator<<(std::ofstream& out, Dynamic const& obj)
{
	out << "\tDynamic " << obj.GetNumber() 
		<< "\tEndTime " << obj.GetEndTime() 
		<< "\tTimeStep " << obj.GetTimeStep() 
		<< "\tMaxTimeStep " << obj.GetMaxTimeStep() 
		<< "\tMinTimeStep " << obj.GetMinTimeStep() 
		<< "\tMaxIt " << obj.GetMaxIt()
		<< "\tMinIt " << obj.GetMinIt()
		<< "\tConvIncrease " << obj.GetConvergenceCriteria()
		<< "\tIncFactor " << obj.GetIncreaseFactor()
		<< "\tSample " << obj.GetSample()
		<< "\n" 
		<< "\t\tRayleighDamping" 
		<< " \tAlpha " << obj.m_alpha_ray
		<< "\tBeta " << obj.m_beta_ray
		<< "\tUpdate " << obj.m_update
		<< "\tNewmarkCoefficients " 
		<< "\tBeta " << obj.m_beta_new
		<< "\tGamma " << obj.m_gamma_new << "\n";

	return out;
}