#include "PCH.h"
#include "Static.h"


Static::Static()
{}

Static::Static(unsigned int id, double start_time, double end_time, 
	double i_time_step, double min_time_step, double max_time_step, 
	unsigned int max_it, unsigned int min_it, unsigned int conv_increase, 
	double inc_factor, unsigned int sample)
{
	this->SetIDNumber(id);
	this->SetStartTime(start_time);
	this->SetEndTime(end_time);
	this->SetTimeStep(i_time_step, min_time_step, max_time_step);
	this->SetIterations(max_it, min_it);
	this->SetIncrese(conv_increase, inc_factor);
	this->SetSample(sample);
}


Static::~Static()
{}


/// 
/// Overloaded operators
/// 

std::ofstream& operator<<(std::ofstream& out, Static const& obj)
{
	out << "\tStatic "		<< obj.GetNumber() <<
		"\tEndTime "		<< obj.GetEndTime() <<
		"\tTimeStep "		<< obj.GetTimeStep() <<
		"\tMaxTimeStep "	<< obj.GetMaxTimeStep() <<
		"\tMinTimeStep "	<< obj.GetMinTimeStep() <<
		"\tMaxIt "			<< obj.GetMaxIt() <<
		"\tMinIt "			<< obj.GetMinIt() <<
		"\tConvIncrease "	<< obj.GetConvergenceCriteria() <<
		"\tIncFactor "		<< obj.GetIncreaseFactor() <<
		"\tSample "			<< obj.GetSample() << "\n";

	return out;
}

