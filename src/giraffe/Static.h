#pragma once
#include "Solution.h"


class Static : public Solution
{
public:
	Static();
	~Static();
	
	//Writes output file
	void WriteGiraffeModelFile(FILE *f) override;
	
	//============================================================================

	/*-------
	Variables
	--------*/

	double i_time_step;
	double max_time_step;
	double min_time_step;
	int max_it;
	int min_it;
	int conv_increase;
	double inc_factor;
	int sample;
};

