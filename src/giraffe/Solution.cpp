#include "PCH.h"
#include "Solution.h"


Solution::Solution()
	: m_id(0), m_start_time(0.0), m_end_time(0.0),
	m_time_step(0.0), m_max_time_step(0.0), m_min_time_step(0.0), 
	m_max_it(0), m_min_it(0), 
	m_convergence_increase(0), m_increase_factor(0.0),
	m_sample(0)
{}

Solution::~Solution()
{}


/// 
/// SETTERS
/// 

void Solution::SetIDNumber(unsigned int id)
{
	m_id = id;
}

void Solution::SetStartTime(double start_time)
{
	m_start_time = start_time;
}

void Solution::SetEndTime(double end_time)
{
	m_end_time = end_time;
}

void Solution::SetTimeStep(double time_step)
{
	m_time_step = time_step;
}

void Solution::SetTimeStep(double time_step, double min_time_step, double max_time_step)
{
	m_time_step = time_step;
	m_min_time_step = min_time_step;
	m_max_time_step = max_time_step;
}

void Solution::SetIterations(int max_it, int min_it)
{
	m_max_it = max_it;
	m_min_it = min_it;
}

void Solution::SetMaxIterations(int max_it)
{
	m_max_it = max_it;
}

void Solution::SetMinIterations(int min_it)
{
	m_min_it = min_it;
}

void Solution::SetIncrese(int convergence_increase, double increase_factor)
{
	m_convergence_increase = convergence_increase;
	m_increase_factor = increase_factor;
}

void Solution::SetConvergenceIncrese(int convergence_increase)
{
	m_convergence_increase = convergence_increase;
}

void Solution::SetIncreseFactor(double increase_factor)
{
	m_increase_factor = increase_factor;
}

void Solution::SetSample(int sample)
{
	m_sample = sample;
}

