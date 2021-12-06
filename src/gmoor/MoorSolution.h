#pragma once
#include "SolutionStep.h"


class DynRelaxLinesConfig : public SolutionStep
{
private:
	double m_decrement;
	unsigned int m_periods;
	int m_duration;

public:
	DynRelaxLinesConfig(double decrement, unsigned int periods, int duration,
		size_t number, bool is_static, bool is_dynamic,
		double global_start_time, double end_time, double timestep,
		double max_timestep, double min_timestep, int sample,
		double beta_new, double gamma_new, double alpha_ray, double beta_ray)
		: m_decrement(decrement), m_periods(periods), m_duration(duration)
	{
		m_number = number;
		m_is_static = is_static;
		m_is_dynamic = is_dynamic;
		m_global_start_time = global_start_time;
		m_end_time = end_time;
		m_timestep = timestep;
		m_max_timestep = max_timestep;
		m_min_timestep = min_timestep;
		m_sample = sample;
		m_beta_new = beta_new;
		m_gamma_new = gamma_new;
		m_alpha_ray = alpha_ray;
		m_beta_ray = beta_ray;
	}

	DynRelaxLinesConfig(const DynRelaxLinesConfig&) = default;
	DynRelaxLinesConfig& operator=(const DynRelaxLinesConfig&) = default;
	DynRelaxLinesConfig(DynRelaxLinesConfig&&) noexcept = default;
	DynRelaxLinesConfig& operator=(DynRelaxLinesConfig&&) = default;

	~DynRelaxLinesConfig() = default;

	// SETTERS
	void SetDecrement(double decrement)		{ m_decrement = decrement; }
	void SetPeriods(unsigned int periods)	{ m_periods = periods; }
	void SetDuration(int duration)			{ m_duration = duration; }

	// GETTERS
	inline double GetDecrement() const		{ return m_decrement; }
	inline unsigned int GetPeriods() const	{ return m_periods; }
	inline int GetDuration() const			{ return m_duration; }
};


class MoorSolution
{
private:
	// Before analysis
	unsigned int m_steps_to_set_model;
	
	// Optional step to establish the sea current
	std::shared_ptr<SolutionStep> m_sea_current_step_ptr;
	bool m_seacurrent_step_exist;

	// Optional dynamic relaxation step(s)
	// -> to find lines static configuration and/or to release vessel forces
	bool m_dyn_relax_exist;
	
	// Optional step to search for lines static configuration
	std::shared_ptr<DynRelaxLinesConfig> m_lines_configuration;
	bool m_lines_config_exist;
	
	// Optional step to release forces at vessels
	std::shared_ptr<SolutionStep> m_vessel_forces;
	bool m_vessel_forces_exist;
	
	// Analysis steps
	std::vector<SolutionStep> m_solution_steps;


public:

	MoorSolution();
	MoorSolution(const MoorSolution&) = default;
	MoorSolution(MoorSolution&&) noexcept = default;
	~MoorSolution();
	
	inline std::shared_ptr<DynRelaxLinesConfig> InitDynRelaxLines()	{ 
		this->m_lines_configuration = std::make_shared<DynRelaxLinesConfig>(0.0, 0, 0, 0, false, true, 0.0, 0.0, 1.0, 1.0e-1, 1.0e-4, 1'000'000,
			0.0, 0.0, 0.0, 0.0);
		return this->m_lines_configuration;
	}
	
	///
	/// SETTERS
	///

	void SetStepsBeforeAnalysis(unsigned int steps);
	void SetDynRelaxExist(bool exist);
	void SetDynRelax_LinesConfigExist(bool exist);
	void SetDynRelax_VesselForcesExist(bool exist);
	void SetStepSeaCurrent(double number, bool is_static, bool is_dynamic,
		double global_start_time, double end_time, double timestep,
		double max_timestep, double min_timestep, int sample,
		double beta_new, double gamma_new, double alpha_ray, double beta_ray) 
	{
		this->m_sea_current_step_ptr = std::make_shared<SolutionStep>(number, is_static, is_dynamic,
			global_start_time, end_time, timestep, max_timestep, min_timestep, sample,
			beta_new, gamma_new, alpha_ray, beta_ray);
	}


	///
	/// GETTERS
	///

	inline unsigned int GetStepsBeforeAnalysis() const					{ return this->m_steps_to_set_model; }

	// Get dynamic relaxation step to find lines static configuration
	inline std::shared_ptr<DynRelaxLinesConfig> GetStepDynRelaxLines()	{ return this->m_lines_configuration; }
	
	// Get dynamic relaxation step to release vessel forces
	inline std::shared_ptr<SolutionStep> GetStepDynRelaxVessels()		{ return this->m_vessel_forces; }

	// Get step to establish sea current
	inline std::shared_ptr<SolutionStep> GetStepSeaCurrent()			{ return this->m_sea_current_step_ptr; }

	// Get the vector with all solution (anlysis) steps
	inline const std::vector<SolutionStep>& GetStepsVec() const			{ return this->m_solution_steps; }
	inline std::vector<SolutionStep>& GetStepsVec()						{ return this->m_solution_steps; }

	// Get a specific solution (analysis) step
	inline const SolutionStep& GetStep(const size_t& step) const		{ return this->m_solution_steps[step]; }

	// Getter-ish -> check booleans

	bool ExistDynamicRelaxation() const	{ return this->m_dyn_relax_exist; }
	bool ExistDynRelax_Lines() const	{ return this->m_lines_config_exist; }
	bool ExistDynRelax_Vessel() const	{ return this->m_vessel_forces_exist; }
	bool ExistSeaCurrentStep() const	{ return this->m_seacurrent_step_exist; }



	///
	/// Overloaded operators
	///

	MoorSolution& operator=(const MoorSolution&) = default;
	MoorSolution& operator=(MoorSolution&&) = default;
};