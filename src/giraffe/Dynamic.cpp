#include "PCH.h"
#include "Dynamic.h"

Dynamic::Dynamic()
	: i_time_step(0.0), max_time_step(0.0), min_time_step(0.0), 
	max_it(0), min_it(0), conv_increase(0), inc_factor(0.0), sample(0),
	update(0), alpha(0.0), beta(0.0), gamma_new(0.0), beta_new(0.0)
{}

Dynamic::~Dynamic()
{}

//Writes output file
void Dynamic::WriteGiraffeModelFile(FILE *f)
{
	fprintf(f, "\tDynamic\t%d\tEndTime\t%.6e\tTimeStep\t%.6e\tMaxTimeStep\t%.6e\tMinTimeStep\t%.6e\tMaxIt\t%d\tMinIt\t%d\tConvIncrease\t%d\tIncFactor\t%.6e\tSample\t%d\t\n\t\tRayleighDamping\tAlpha\t%.6e\tBeta\t%.6e\tUpdate\t%d\tNewmarkCoefficients\tBeta\t%.6e\tGamma\t%.6e\n",
		solution_number, end_time, i_time_step, max_time_step, min_time_step, max_it, min_it, conv_increase, inc_factor, sample, alpha, beta, update, beta_new, gamma_new);
}