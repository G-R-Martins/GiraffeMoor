#include "PCH.h"
#include "Static.h"


Static::Static()
{}

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

