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


void SolverOptions::WriteGiraffeModelFile(FILE* f) const
{

	if (fprintf(f, "\tProcessors %d\tLinSys ", n_cores))
	{
		if (isDirect)	fprintf(f, "Direct\n");
		else			fprintf(f, "Iterative\n");

	}

}