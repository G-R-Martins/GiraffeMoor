#pragma once
#include "Solution.h"


class Static : public Solution
{
public:
	Static();
	Static(unsigned int id, double start_time, double end_time, double i_time_step, double min_time_step, double max_time_step, 
		unsigned int max_it, unsigned int min_it, unsigned int conv_increase, double inc_factor, unsigned int sample);
	~Static();
	
	inline std::ofstream& WriteGiraffeFile(std::ofstream& out) override { operator<<(out, *this); return out; }


	/// 
	/// Overloaded operators
	/// 

	friend std::ofstream& operator<<(std::ofstream& out, Static const& obj);
};

