#pragma once
#include "Solution.h"

class Dynamic :	public Solution
{
public:
	Dynamic();
	~Dynamic();
	
	//============================================================================

	//Writes output file
	void WriteGiraffeModelFile(std::ostream& fout) const override;	
	
	//============================================================================

	/*------------------------
		General parameters 
	(time steps and iterations)
	-------------------------*/

	double i_time_step;
	double max_time_step;
	double min_time_step;
	int max_it;
	int min_it;
	int conv_increase;
	double inc_factor;
	int sample;
	

	/*-----
	Damping
	------*/

	int update;

	//Rayleigh
	double alpha;
	double beta;
	
	//Newmark
	double gamma_new;
	double beta_new;
};

