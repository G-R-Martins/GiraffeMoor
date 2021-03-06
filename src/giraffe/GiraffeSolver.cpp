#include "PCH.h"
#include "GiraffeSolver.h"
#include "Log.h"


GiraffeSolver::GiraffeSolver()
	: m_run_Giraffe(false), m_cores(2), m_is_direct(true)
{}

GiraffeSolver::~GiraffeSolver()
{}



///
/// SETTERS
///

void GiraffeSolver::SetRunGiraffeOpt(bool run_opt)
{
	this->m_run_Giraffe = run_opt;
}
void GiraffeSolver::SetCores(unsigned int cores)
{
	this->m_cores = cores;
}
void GiraffeSolver::SetLinSolverOpt(bool is_direct)
{
	this->m_is_direct = is_direct;
}
void GiraffeSolver::SetLinSolverOpt(std::string_view type)
{
	if (type == "direct")
		this->m_is_direct = true;
	else if (type == "iterative")
		this->m_is_direct = false;
	else
	{
		Log::SetWarning(Log::Warning::INVALID_KEYWORD, "SolverOptions", 0, "LinSys");
		Log::SetWarning("\n  GiraffeMoor will set the default option: \'directive\'");
	}
}


/// 
/// Overloaded operators
/// 

std::ostream& operator<<(std::ostream& fout, const ConvergenceCriteria& conv_criteria)
{
	fout <<
		"\tForceTolerance " << conv_criteria.force_tol <<
		"\n\tMomentTolerance " << conv_criteria.moment_tol <<
		"\n\tForceMinimumReference " << conv_criteria.force_min <<
		"\n\tMomentMinimumReference " << conv_criteria.moment_min <<
		"\n\tConstraintMinimumReference " << conv_criteria.constraint_min <<
		"\n\tDisplacementTolerance " << conv_criteria.disp_tol <<
		"\n\tRotationTolerance " << conv_criteria.rot_tol <<
		"\n\tLagrangeTolerance " << conv_criteria.lag_tol <<
		"\n\tDisplacementMinimumReference " << conv_criteria.disp_min <<
		"\n\tRotationMinimumReference " << conv_criteria.rot_min <<
		"\n\tLagrangeMinimumReference " << conv_criteria.lag_min <<
		"\n\tDivergenceReference " << conv_criteria.divergence_ref <<
		"\n";

	return fout;
}


std::ostream& operator<<(std::ostream& out, const GiraffeSolver* obj)
{
	out << "\tProcessors " << obj->m_cores <<
		"\tLinSys " << (obj->m_is_direct ? "Direct\n" : "Iterative\n");

	return out;
}
