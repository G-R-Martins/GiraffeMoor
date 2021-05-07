#pragma once
#include "SolutionStep.h"

class MoorSolution
{
public:
	MoorSolution();
	~MoorSolution();
	
	//Reads input file
	bool Read(FILE *f);

	//Returns the vector with all solution (anlysis) steps
	const std::vector<SolutionStep>& GetStepsVec() const;

	//Returns a specific solution (analysis) step
	const SolutionStep& GetStep(const size_t& step) const;

	//============================================================================

							/*-------
							Variables
							--------*/

	/*---------------------------
	Dynamic relaxation parameters
	----------------------------*/
	
	//Boolean to indicate if there is a dynamic relaxations step
	bool bool_DynamicRelax;

	//Displacement decrement
	double decrement;

	//Number of periods during the dyn. relax. step
	unsigned int dyn_relax_periods;

	//Time during the dyn. relax. step (round up)
	unsigned int TimeRelax;

	//Alpha coefficient to Rayleigh damping during the dyn. relax. step
	double alpha_relax;

	//Boolean to indicate if there is a dynamic step to release forces at the vessel node
	bool bool_ReleaseForces;

	//Time step for release forces
	double release_timestep;


	/*--------------------
	Sea current parameters
	---------------------*/
	
	//Sea current time step
	double seacurrent_timestep;
	
	//Sea current maximum time step
	double seacurrent_max_timestep;

	//Sea current minimum time step
	double seacurrent_min_timestep;
	
	
	/*-----------
	Steps options
	------------*/
	//Steps before analysis
	unsigned int steps_to_set_model;

	///TODO: make it private
	//Container with analysis steps
	std::vector <SolutionStep> solution_steps;

	
	///TODO: send to another object (GiraffeModel or a new one)
	/*------------
	Solver options
	-------------*/
		
	//Number of cores used for Giraffe
	unsigned int ncores;

	//Linear system solver option
	/// if is not direct, it will be defined as 'iterative'
	bool lin_sys_isDirect;
};