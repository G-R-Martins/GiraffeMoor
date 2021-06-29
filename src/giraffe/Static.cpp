#include "PCH.h"
#include "Static.h"


Static::Static()
	: i_time_step(0), max_time_step(0), min_time_step(0), max_it(0), min_it(0), 
	conv_increase(0), inc_factor(0), sample(0)
{}

Static::~Static()
{}

//Writes output file
void Static::WriteGiraffeModelFile(std::ostream& fout) const
{
	fout << "\tStatic " << solution_number <<
		"\tEndTime " << end_time <<
		"\tTimeStep " << i_time_step <<
		"\tMaxTimeStep " << max_time_step <<
		"\tMinTimeStep " << min_time_step <<
		"\tMaxIt " << max_it << 
		"\tMinIt " << min_it <<
		"\tConvIncrease " << conv_increase << 
		"\tIncFactor " << inc_factor <<
		"\tSample " << sample << "\n";
}