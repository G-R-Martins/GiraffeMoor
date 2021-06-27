#pragma once

class SolutionStep
{
	unsigned int number;
	bool isStatic;

	/// 
	/// Time parameters
	/// 

	//Global step start time
	double global_start;

	//Simulation end time 
	double end_time;

	//Time step
	double timestep;

	//Maximum time step
	double max_timestep;

	//Minimum time step
	double min_timestep;

	//Sample -> to save VTK
	int sample;

	/// 
	/// Damping parameters 
	/// 

	// Newmark damping (numerical damping)
	double beta_new, gamma_new;
	// Rayleigh damping 
	double alpha_ray, beta_ray;

	//============================================================================

public:
	SolutionStep();
	~SolutionStep();
	
	bool Read(FILE* f);
	
	///
	/// Set functions
	/// 
	void SetGlobalStart(double time);

	/// 
	/// Get functions
	/// 

	unsigned int GetNumber() const;

	//Time parameters
	double GetGlobalStart() const;
	double GetEndTime() const;
	double GetTimestep() const;
	double GetMaxTimestep() const;
	double GetMinTimestep() const;

	//Sample -> to save VTK
	int GetSample() const;

	/// 
	/// Damping parameters 
	/// 

	double GetBeta_new() const, GetGamma_new() const;
	double GetAlpha_ray() const, GetBeta_ray() const;

	bool CheckIfIsStatic() const;


	//============================================================================
	
	/*-------------------
	 Overloaded operators
	--------------------*/

	friend bool operator< (const SolutionStep& obj1, const SolutionStep& obj2);
	friend bool operator> (const SolutionStep& obj1, const SolutionStep& obj2);
	friend bool operator== (const SolutionStep& obj1, const SolutionStep& obj2);
	friend bool operator!= (const SolutionStep& obj1, const SolutionStep& obj2);
};

