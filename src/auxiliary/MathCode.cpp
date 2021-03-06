#include "PCH.h"
#include "MathCode.h"
#include "AuxFunctions.h"


MathCode::MathCode()
	: m_equations{ "\0","\0","\0","\0","\0","\0" }, m_start_time(-1.0)
{}

MathCode::~MathCode()
{}

//Match GiraffeMoor and Giraffe times
void MathCode::SetStartTime(const double& start)
{
	m_start_time = start;
}

void MathCode::SetEquation(unsigned int dof, const std::string& eq)
{
	m_equations[dof] = eq;
}

//Setting start time ('t0') to apply math code
void MathCode::SetEquationInitialTime(const double& init)
{
	m_start_time = init;
	for (std::string& eq : m_equations)
	{
		//Erases '\n' from the end of a readed equation
		if (eq != "0") eq.pop_back();

		size_t rf = eq.rfind("t0");
		while (rf != std::string::npos)
		{
			std::string::iterator it = eq.begin();
			eq.replace(it + rf, it + rf + 2, std::to_string(m_start_time));
			rf = eq.rfind("t0");
		}
	}
}


/// 
/// Overloaded operators
/// 

//Writes Giraffe file
std::ostream& operator<<(std::ostream& out, const MathCode& mc)
{
	out << "\t\t//X\n\t\tBegin\t" << mc.m_equations[0] << " End \n" <<
		"\t\t//Y\n\t\tBegin \t" << mc.m_equations[1] << " End \n" <<
		"\t\t//Z\n\t\tBegin \t" << mc.m_equations[2] << " End \n" <<
		"\t\t//ROTX\n\t\tBegin" << mc.m_equations[3] << " End \n" <<
		"\t\t//ROTY\n\t\tBegin" << mc.m_equations[4] << " End \n" <<
		"\t\t//ROTZ\n\t\tBegin" << mc.m_equations[5] << " End \n";


	return out;
}
std::ostream& operator<<(std::ostream& out, MathCode* mcPtr)
{
	out << "\t\t//X\n\t\tBegin\t" << mcPtr->m_equations[0] << " End \n" <<
		"\t\t//Y\n\t\tBegin \t" << mcPtr->m_equations[1] << " End \n" <<
		"\t\t//Z\n\t\tBegin \t" << mcPtr->m_equations[2] << " End \n" <<
		"\t\t//ROTX\n\t\tBegin\t" << mcPtr->m_equations[3] << " End \n" <<
		"\t\t//ROTY\n\t\tBegin\t" << mcPtr->m_equations[4] << " End \n" <<
		"\t\t//ROTZ\n\t\tBegin\t" << mcPtr->m_equations[5] << " End \n";


	return out;
}


