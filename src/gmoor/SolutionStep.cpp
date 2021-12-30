#include "PCH.h"
#include "SolutionStep.h"
#include "AuxFunctions.h"


SolutionStep::SolutionStep()
	: m_id(0), m_is_static(true), m_is_dynamic(false),	m_global_start_time(0.0), 
	m_end_time(0.0), m_timestep(0.0), m_min_timestep(0.0), 
	m_max_timestep(0.0), m_max_timestep_defined(false),
	m_sample(0), m_beta_new(0.0), m_gamma_new(0.0), m_alpha_ray(0.0), m_beta_ray(0.0)
{}

SolutionStep::SolutionStep(unsigned int id, bool is_static,
	double global_start_time, double end_time, double timestep, double min_timestep, 
	double max_timestep, bool max_timestep_defined, int sample,
	double beta_new, double gamma_new, double alpha_ray, double beta_ray)
	: m_id(id), m_is_static(is_static), m_is_dynamic(!is_static),
	m_global_start_time(global_start_time), m_end_time(end_time),
	m_timestep(timestep), m_min_timestep(min_timestep),
	m_max_timestep(max_timestep), m_max_timestep_defined(max_timestep_defined),
	m_sample(sample), m_beta_new(beta_new), m_gamma_new(gamma_new),
	m_alpha_ray(alpha_ray), m_beta_ray(beta_ray)
{}

SolutionStep::~SolutionStep()
{}

void SolutionStep::CheckAndSetMaxTimeStep()
{
	if (!m_max_timestep_defined)
	{
		m_max_timestep = m_timestep;
		m_max_timestep_defined = true;
	}
}


/// 
/// SETTERS
/// 

void SolutionStep::SetIDNumber(unsigned int id)
{
	this->m_id = id;
}

void SolutionStep::SetStaticOpt(bool is_static)
{
	this->m_is_static = is_static;
	this->m_is_dynamic = !is_static;
}

void SolutionStep::SetDynamicOpt(bool is_dynamic)
{
	this->m_is_dynamic = is_dynamic;
	this->m_is_static = !is_dynamic;
}

void SolutionStep::SetGlobalStartTime(double global_start_time)
{
	this->m_global_start_time = global_start_time;
}

void SolutionStep::SetEndTime(double end_time)
{
	this->m_end_time = end_time;
}

void SolutionStep::SetTimestep(double timestep)
{
	this->m_timestep = timestep;
}

void SolutionStep::SetMaxTimestep(double max_timestep)
{
	this->m_max_timestep = max_timestep;
	this->m_max_timestep_defined = true;
}

void SolutionStep::SetMinTimeStep(double min_timestep)
{
	this->m_min_timestep = min_timestep;
}

void SolutionStep::SetSample(int sample)
{
	this->m_sample = sample;
}

bool SolutionStep::SetNewmarkDamping(std::string_view damping, std::string& readed)
{
	if (damping == "null")
	{
		m_beta_new = 0.3;
		m_gamma_new = 0.5;
		return true;
	}
	if (damping == "mild")
	{
		m_beta_new = 0.3;
		m_gamma_new = 0.505;
		return true;
	}
	if (damping == "moderate")
	{
		m_beta_new = 0.3;
		m_gamma_new = 0.52;
		return true;
	}
	if (damping == "high")
	{
		m_beta_new = 0.3;
		m_gamma_new = 0.55;
		return true;
	}
	if (damping == "extreme")
	{
		m_beta_new = 0.3;
		m_gamma_new = 0.6;
		return true;
	}

	// Set last readed word equals to 'damping' because in this case 
	//each coefficient MUST be defined explicitly
	readed = damping;
	return false;
}

void SolutionStep::SetBetaNewmark(double beta_new)
{
	this->m_beta_new = beta_new;
}

void SolutionStep::SetGammaNewmark(double gamma_new)
{
	this->m_gamma_new = gamma_new;
}

void SolutionStep::SetAlphaRayleigh(double alpha_ray)
{
	this->m_alpha_ray = alpha_ray;
}

void SolutionStep::SetBetaRayleigh(double beta_ray)
{
	this->m_beta_ray = beta_ray;
}



/// 
/// Overloaded operators
///

bool operator<(const SolutionStep& obj1, const SolutionStep& obj2)
{
	return obj1.m_id < obj2.m_id;
}
bool operator>(const SolutionStep& obj1, const SolutionStep& obj2)
{
	return !(obj1 < obj2);
}
bool operator==(const SolutionStep& obj1, const SolutionStep& obj2)
{
	return obj1.m_id == obj2.m_id;
}
bool operator!=(const SolutionStep& obj1, const SolutionStep& obj2)
{
	return !(obj1 == obj2);
}
