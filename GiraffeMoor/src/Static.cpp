#include "PCH.h"
#include "Static.h"


Static::Static()
	: i_time_step(0), max_time_step(0), min_time_step(0), max_it(0), min_it(0), 
	conv_increase(0), inc_factor(0), sample(0)
{}

Static::~Static()
{}

//Writes output file
void Static::WriteGiraffeModelFile(FILE *f)
{
	fprintf(f, "\tStatic\t%d\tEndTime\t%.6e\tTimeStep\t%.6e\tMaxTimeStep\t%.6e\tMinTimeStep\t%.6e\tMaxIt\t%d\tMinIt\t%d\tConvIncrease\t%d\tIncFactor\t%.6e\tSample\t%d\n",
		solution_number, end_time, i_time_step, max_time_step, min_time_step, max_it, min_it, conv_increase, inc_factor, sample);
}