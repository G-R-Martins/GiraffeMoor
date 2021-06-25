#include "PCH.h"
#include "SolverOptions.h"


SolverOptions::SolverOptions()
	: n_cores(1), isDirect(true)
{}
SolverOptions::SolverOptions(unsigned int cores, bool bool_direct)
	: n_cores(cores), isDirect(bool_direct)
{}


void SolverOptions::SetSolverOptions(unsigned int cores, bool bool_direct)
{
	n_cores = cores;
	isDirect = bool_direct;
}


void SolverOptions::WriteGiraffeModelFile(std::ostream& fout) const
{
	fout << "\tProcessors " << n_cores <<
		"\tLinSys ";
	isDirect ? fout << "Direct\n" : 
		fout <<"Iterative\n";
}