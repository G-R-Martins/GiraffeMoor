#include "PCH.h"
#include "VesselDisplacement.h"
#include "IO.h" //to get the folder name

VesselDisplacement::VesselDisplacement()
	: m_vesselID(0), m_solution_step(0),
	m_is_table(false), m_is_sine_wave(false), m_is_math_code(false), m_is_external_file(false),
	m_file_name("\0"), m_header_lines(0), m_tot_steps(0),
	m_ptr_time_series(nullptr), m_ptr_math_code(nullptr)
{}
VesselDisplacement::~VesselDisplacement()
{
	if (m_ptr_math_code)
	{
		delete m_ptr_math_code;
		m_ptr_math_code = nullptr;
	}
}


void VesselDisplacement::SetVesselID(size_t vesselID)
{
	m_vesselID = vesselID;
}
void VesselDisplacement::SetSolutionStep(size_t solution_step)
{
	m_solution_step = solution_step;
}
void VesselDisplacement::SetStartTime(double start)
{
	this->m_ptr_math_code->SetEquationInitialTime(start);
}
void VesselDisplacement::SetStartTableTime(double start_time, size_t start_line)
{
	m_ptr_time_series->SetStartTime(start_time, start_line);
}

void VesselDisplacement::SetTimeSeries()
{
	m_is_table = true;
	m_ptr_time_series = new Table();
}
void VesselDisplacement::SetTimeSeries(std::ifstream& input)
{
	m_is_table = true;
	m_ptr_time_series = new Table();

	input >> m_ptr_time_series;
}
void VesselDisplacement::SetMathCode()
{
	m_is_math_code = true;
	m_ptr_math_code = new MathCode();
}

void VesselDisplacement::SetFileName(const std::string& file_name)
{
	m_file_name = file_name;
}
void VesselDisplacement::SetFileHeaders(unsigned int header_lines)
{
	m_header_lines = header_lines;
}
void VesselDisplacement::SetFileNSteps(unsigned int tot_steps)
{
	m_tot_steps = tot_steps;
}



/// 
/// Overloaded operators
/// 

bool operator<(const VesselDisplacement& obj1, const VesselDisplacement& obj2)
{
	return obj1.m_vesselID < obj2.m_vesselID;
}

bool operator>(const VesselDisplacement& obj1, const VesselDisplacement& obj2)
{
	return !(obj1 < obj2);
}

bool operator==(const VesselDisplacement& obj1, const VesselDisplacement& obj2)
{
	return obj1.m_vesselID == obj2.m_vesselID;
}

bool operator!=(const VesselDisplacement& obj1, const VesselDisplacement& obj2)
{
	return !(obj1 == obj2);
}
