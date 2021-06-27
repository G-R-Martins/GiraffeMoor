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
void Dynamic::WriteGiraffeModelFile(std::ostream& fout) const
{
	fout << "\tDynamic " << solution_number <<
		std::setprecision(6) <<
		"\tEndTime " << end_time <<
		"\tTimeStep " << i_time_step <<
		"\tMaxTimeStep " << max_time_step <<
		"\tMinTimeStep " << min_time_step <<
		"\tMaxIt " << max_it << "\tMinIt " << min_it <<
		"\tConvIncrease " << conv_increase << 
		"\tIncFactor " << inc_factor <<
		"\tSample " << sample <<
		"\n\t\tRayleighDamping \tAlpha " << alpha << "\tBeta " << beta << "\tUpdate " << update <<
		"\tNewmarkCoefficients \tBeta " << beta_new << "\tGamma " << gamma_new << "n";
}