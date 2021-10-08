#include "PCH.h"
#include "MoorSolution.h"
#include "LoopReading.h"
#include "Log.h"


MoorSolution::MoorSolution()
	: m_steps_to_set_model(0), m_seacurrent_step_exist(false), 
	m_dyn_relax_exist(false), m_lines_config_exist(false), 
	m_vessel_forces_exist(false)
{
	m_solution_steps.reserve(4);
}

MoorSolution::~MoorSolution()
{}

void MoorSolution::SetStepsBeforeAnalysis(unsigned int steps)
{
	this->m_steps_to_set_model = steps;
}

void MoorSolution::SetDynRelaxExist(bool exist)
{
	this->m_dyn_relax_exist = exist;
}

void MoorSolution::SetDynRelax_LinesConfigExist(bool exist)
{
	this->m_lines_config_exist = exist;
}

void MoorSolution::SetDynRelax_VesselForcesExist(bool exist)
{
	this->m_vessel_forces_exist = exist;
}


