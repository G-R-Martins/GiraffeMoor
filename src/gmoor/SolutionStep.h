#pragma once

class SolutionStep
{
protected:
	unsigned int m_id;
	
	bool m_is_static;
	bool m_is_dynamic;

	// Global start time for analysis
	double m_global_start_time;

	// Simulation end time 
	double m_end_time;
	double m_timestep;
	double m_min_timestep;
	double m_max_timestep;
	bool m_max_timestep_defined;

	// Sample -> to save VTK
	int m_sample;

	// Damping parameters for dynamic step
	double m_beta_new;  // Newmark
	double m_gamma_new;  // Newmark 
	double m_alpha_ray;  // Rayleigh
	double m_beta_ray;  // Rayleigh 

	//============================================================================

public:
	SolutionStep();
	SolutionStep(unsigned int id, bool is_static, 
		double global_start_time, double end_time, double timestep,
		double min_timestep, double max_timestep, bool max_timestep_defined, int sample,
		double beta_new, double gamma_new, double alpha_ray, double beta_ray);
	SolutionStep(const SolutionStep&) = default;
	SolutionStep(SolutionStep&&) noexcept = default;
	~SolutionStep();
	
	//Check if maximum time step was defined -> if not, make it equal to time step
	void CheckAndSetMaxTimeStep();

	///
	/// SETTERS
	/// 
	
	void SetIDNumber(unsigned int id);

	void SetStaticOpt(bool is_static);
	void SetDynamicOpt(bool is_dynamic);

	void SetGlobalStartTime(double global_start_time);

	void SetEndTime(double end_time);
	void SetTimestep(double timestep);
	void SetMaxTimestep(double max_timestep);
	void SetMinTimeStep(double min_timestep);
	void SetSample(int sample);
	
	bool SetNewmarkDamping(std::string_view damping, std::string& readed);
	void SetBetaNewmark(double beta_new);
	void SetGammaNewmark(double gamma_new);
	void SetAlphaRayleigh(double alpha_ray);
	void SetBetaRayleigh(double beta_ray);


	/// 
	/// GETTERS
	/// 

	inline unsigned int GetNumber() const			{ return this->m_id; }

	inline double GetGlobalStart() const	{ return this->m_global_start_time; }
	
	inline double GetEndTime() const		{ return this->m_end_time; }
	inline double GetTimestep() const		{ return this->m_timestep; }
	inline double GetMaxTimestep() const	{ return this->m_max_timestep; }
	inline double GetMinTimestep() const	{ return this->m_min_timestep; }
	
	inline int GetSample() const			{ return this->m_sample; }
	
	inline double GetBeta_new() const		{ return this->m_beta_new; }
	inline double GetGamma_new() const		{ return this->m_gamma_new; }
	inline double GetAlpha_ray() const		{ return this->m_alpha_ray; }
	inline double GetBeta_ray() const		{ return this->m_beta_ray; }

	// Getter-ish -> check booleans
	inline bool IsStatic() const			{ return this->m_is_static; }
	inline bool IsDynamic() const			{ return this->m_is_dynamic; }


	//============================================================================
	
	/*-------------------
	 Overloaded operators
	--------------------*/

	friend bool operator< (const SolutionStep& obj1, const SolutionStep& obj2);
	friend bool operator> (const SolutionStep& obj1, const SolutionStep& obj2);
	friend bool operator== (const SolutionStep& obj1, const SolutionStep& obj2);
	friend bool operator!= (const SolutionStep& obj1, const SolutionStep& obj2);

	SolutionStep& operator=(const SolutionStep&) = default;
	SolutionStep& operator=(SolutionStep&&) = default;
};



class DynRelaxLinesConfig : public SolutionStep
{
private:
	double m_decrement;
	double m_periods;
	int m_duration;

public:
	DynRelaxLinesConfig(double decrement, double periods, int duration,
		unsigned int id, bool is_static,
		double global_start_time, double end_time, double timestep,
		double max_timestep, double min_timestep, int sample,
		double beta_new, double gamma_new, double alpha_ray, double beta_ray)
		: m_decrement(decrement), m_periods(periods), m_duration(duration)
	{
		m_id = id;
		m_is_static = is_static;
		m_is_dynamic = !is_static;
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
	void SetDecrement(double decrement) { m_decrement = decrement; }
	void SetPeriods(double periods) { m_periods = periods; }
	void SetDuration(int duration) { m_duration = duration; }

	// GETTERS
	inline double GetDecrement() const { return m_decrement; }
	inline double GetPeriods() const { return m_periods; }
	inline int GetDuration() const { return m_duration; }
};

