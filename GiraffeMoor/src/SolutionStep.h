#pragma once

class SolutionStep
{
public:
	SolutionStep();
	~SolutionStep();
	
	bool Read(FILE* f);
	unsigned int number;
	bool isStatic;

	/*-------------
	Time parameters
	--------------*/

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

	/*----------------------
	    Damping parameters
	  (for dynamic analisys)
	------------------------*/

	// Newmark damping (numerical damping)
	double beta_new, gamma_new;
	// Rayleigh damping 
	double alpha_ray, beta_ray;

	//============================================================================

	/*-------------------
	 Overloaded operators
	--------------------*/

	friend bool operator< (const SolutionStep& obj1, const SolutionStep& obj2);
	friend bool operator> (const SolutionStep& obj1, const SolutionStep& obj2);
	friend bool operator== (const SolutionStep& obj1, const SolutionStep& obj2);
	friend bool operator!= (const SolutionStep& obj1, const SolutionStep& obj2);
};

