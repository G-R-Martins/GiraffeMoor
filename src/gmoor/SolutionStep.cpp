#include "PCH.h"
#include "SolutionStep.h"
#include "Log.h"


SolutionStep::SolutionStep()
	: m_number(0), m_is_static(true), m_is_dynamic(false),	m_global_start_time(0.0), 
	m_end_time(0.0), m_timestep(0.0), m_max_timestep(0.0), m_min_timestep(0.0), 
	m_sample(0.0), m_beta_new(0.0), m_gamma_new(0.0), m_alpha_ray(0.0), m_beta_ray(0.0)
{}

SolutionStep::SolutionStep(size_t number, bool is_static, bool is_dynamic,
	double global_start_time, double end_time, double timestep,
	double max_timestep, double min_timestep, int sample,
	double beta_new, double gamma_new, double alpha_ray, double beta_ray)
	: m_number(number), m_is_static(is_static), m_is_dynamic(is_dynamic),
	m_global_start_time(global_start_time), m_end_time(end_time),
	m_timestep(timestep), m_max_timestep(max_timestep), m_min_timestep(min_timestep),
	m_sample(sample), m_beta_new(beta_new), m_gamma_new(gamma_new),
	m_alpha_ray(alpha_ray), m_beta_ray(beta_ray)
{}

SolutionStep::~SolutionStep()
{}


/// 
/// SETTERS
/// 

void SolutionStep::SetIDNumber(size_t number)
{
	this->m_number = number;
}

void SolutionStep::SetStaticOpt(bool is_static)
{
	this->m_is_static = is_static;
}

void SolutionStep::SetDynamicOpt(bool is_dynamic)
{
	this->m_is_dynamic = is_dynamic;
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
}

void SolutionStep::SetMinTimeStep(double min_timestep)
{
	this->m_min_timestep = min_timestep;
}

void SolutionStep::SetSample(int sample)
{
	this->m_sample = sample;
}

bool SolutionStep::SetNewmarkDamping(std::string_view damping)
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

	// Or, defined each coefficient explicitly
///	{
///		std::unordered_set<std::string_view> coeffs = { "Beta", "Gamma" };
///		for (int i = 0; i < 2; ++i)
///		{
///			auto nh = coeffs.extract(damping);
///			if (nh.empty())
///			{
///				bool all_parameters_readed = coeffs.empty();
///				if (!all_parameters_readed)
///					Log::AddWarning("  + Error reading numerical damping");
///
///				return all_parameters_readed;
///			}
///
///			if (name == "Beta")			ptr->SetBetaNewmark(std::stod(readed));
///			else if (name == "Gamma")	ptr->SetGammaNewmark(std::stod(readed));
///		}
///
///	}

	// ERROR: invalid numerical damping
	Log::SetWarning(R"(
   + Please define one of these keywords for setting numerical damping parameters:

	 ------------------------------
	|  Keyword   |  Beta |  Gamma  |
	|------------|-------|---------|
	|  null      |  0.3  |  0.500  |
	|  mild      |  0.3  |  0.505  |
	|  moderate  |  0.3  |  0.520  |
	|  high      |  0.3  |  0.550  |
	|  extreme   |  0.3  |  0.600  |
	 ------------------------------)");

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
	return obj1.m_number < obj2.m_number;
}
bool operator>(const SolutionStep& obj1, const SolutionStep& obj2)
{
	return !(obj1 < obj2);
}
bool operator==(const SolutionStep& obj1, const SolutionStep& obj2)
{
	return obj1.m_number == obj2.m_number;
}
bool operator!=(const SolutionStep& obj1, const SolutionStep& obj2)
{
	return !(obj1 == obj2);
}
