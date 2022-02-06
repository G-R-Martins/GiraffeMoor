#include "PCH.h"
#include "Dynamic.h"

Dynamic::Dynamic()
	: m_alpha_ray(0.0), m_beta_ray(0.0), m_gamma_new(0.0), m_beta_new(0.0),
	m_update(0), m_zero_ic(false)
{}

Dynamic::Dynamic(double alpha_ray, double beta_ray, double gamma_new, double beta_new, int update)
	: m_alpha_ray(alpha_ray), m_beta_ray(beta_ray), m_gamma_new(gamma_new), m_beta_new(beta_new),
	m_update(update), m_zero_ic(false)
{}

Dynamic::Dynamic(unsigned int id, double start_time, double end_time, 
	double i_time_step, double min_time_step, double max_time_step, 
	unsigned int max_it, unsigned int min_it, unsigned int conv_increase, double inc_factor, unsigned int sample, 
	double alpha_ray, double beta_ray, double gamma_new, double beta_new, int update, bool zero_ic)
	: m_alpha_ray(alpha_ray), m_beta_ray(beta_ray), m_gamma_new(gamma_new), m_beta_new(beta_new), m_update(update), m_zero_ic(zero_ic)
{
	this->SetIDNumber(id);
	this->SetStartTime(start_time);
	this->SetEndTime(end_time);
	this->SetTimeStep(i_time_step, min_time_step, max_time_step);
	this->SetIterations(max_it, min_it);
	this->SetIncrese(conv_increase, inc_factor);
	this->SetSample(sample);
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

void Dynamic::SetZeroIC(bool zero_ic)
{
	this->m_zero_ic = zero_ic;
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
		<< "\tGamma " << obj.m_gamma_new 
		<< (obj.GetZeroIC() ? "\n\t\tZeroIC\n" : "\n");

	return out;
}