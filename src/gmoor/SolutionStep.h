#pragma once

class SolutionStep
{
protected:
	size_t m_number;
	
	bool m_is_static;
	bool m_is_dynamic;

	// Global start time for analysis
	double m_global_start_time;

	// Simulation end time 
	double m_end_time;
	double m_timestep;
	double m_max_timestep;
	double m_min_timestep;

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
	SolutionStep(size_t number, bool is_static, bool is_dynamic,
		double global_start_time, double end_time, double timestep,
		double max_timestep, double min_timestep, int sample,
		double beta_new, double gamma_new, double alpha_ray, double beta_ray);
	SolutionStep(const SolutionStep&) = default;
	SolutionStep(SolutionStep&&) noexcept = default;
	~SolutionStep();
	
	///
	/// SETTERS
	/// 
	
	void SetIDNumber(size_t m_number);

	void SetStaticOpt(bool is_static);
	void SetDynamicOpt(bool is_dynamic);

	void SetGlobalStartTime(double global_start_time);

	void SetEndTime(double end_time);
	void SetTimestep(double timestep);
	void SetMaxTimestep(double max_timestep);
	void SetMinTimeStep(double min_timestep);
	void SetSample(int sample);
	
	bool SetNewmarkDamping(std::string_view damping);
	void SetBetaNewmark(double beta_new);
	void SetGammaNewmark(double gamma_new);
	void SetAlphaRayleigh(double alpha_ray);
	void SetBetaRayleigh(double beta_ray);


	/// 
	/// GETTERS
	/// 

	inline size_t GetNumber() const			{ return this->m_number; }

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

