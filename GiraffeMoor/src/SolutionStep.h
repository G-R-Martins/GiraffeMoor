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

	/*--------------------------
	Numerical damping parameters
	  (for dynamic analisys)
	---------------------------*/
	//Beta -> Newmark damping
	double beta_new;

	//Gamma -> Newmark damping
	double gamma_new;

	//============================================================================

	/*-------------------
	 Overloaded operators
	--------------------*/

	friend bool operator< (const SolutionStep& obj1, const SolutionStep& obj2);
	friend bool operator> (const SolutionStep& obj1, const SolutionStep& obj2);
	friend bool operator== (const SolutionStep& obj1, const SolutionStep& obj2);
	friend bool operator!= (const SolutionStep& obj1, const SolutionStep& obj2);
};

