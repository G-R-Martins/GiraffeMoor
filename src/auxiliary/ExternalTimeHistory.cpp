#include "PCH.h"
#include "ExternalTimeHistory.h"


ExternalTimeHistory::ExternalTimeHistory()
	: m_solution_step_id(0),
	m_is_table(false), m_is_math_code(false), m_is_external_file(false),
	m_file_name("\0"), m_header_lines(0), m_tot_steps(0),
	m_ptr_time_series(nullptr), m_ptr_math_code(nullptr),
	m_description_defined(false), m_id_defined(false),
	m_segment_id_defined(false), m_type_defined(false),
	m_step_defined(false)
{}

ExternalTimeHistory::~ExternalTimeHistory()
{
	if (m_ptr_math_code)
	{
		delete m_ptr_math_code;
		m_ptr_math_code = nullptr;
	}
}


///
/// SETTERS
///

void ExternalTimeHistory::SetSolutionStep(unsigned int solution_step_id)
{
	m_solution_step_id = solution_step_id;
	m_step_defined = true;
}
void ExternalTimeHistory::SetStartTime(double start)
{
	this->m_ptr_math_code->SetEquationInitialTime(start);
}
void ExternalTimeHistory::SetStartTableTime(double start_time, unsigned int start_line)
{
	m_ptr_time_series->SetStartTime(start_time, start_line);
}

void ExternalTimeHistory::SetTimeSeries()
{
	m_is_table = true;
	m_type_defined = true;

	m_ptr_time_series = new Table();
}
void ExternalTimeHistory::SetTimeSeries(Table* ptr_time_series)
{
	m_is_table = true;
	m_type_defined = true;

	m_ptr_time_series = new Table();
	m_ptr_time_series = ptr_time_series;
}
void ExternalTimeHistory::SetMathCode()
{
	m_is_math_code = true;
	m_type_defined = true;

	m_ptr_math_code = new MathCode();
}

void ExternalTimeHistory::SetFileOption(bool opt)
{
	this->m_is_external_file = opt;
	this->m_type_defined = true;
}
void ExternalTimeHistory::SetFileName(const std::string& file_name)
{
	m_file_name = file_name;
}
void ExternalTimeHistory::SetFileHeaders(unsigned int header_lines)
{
	m_header_lines = header_lines;
}
void ExternalTimeHistory::SetFileNSteps(unsigned int tot_steps)
{
	m_tot_steps = tot_steps;
}


void ExternalTimeHistory::SetDescriptionOpt(bool opt)
{
	m_description_defined = opt;
}
void ExternalTimeHistory::SetIDOpt(bool opt)
{
	m_id_defined = opt;
}
void ExternalTimeHistory::SetSegmentIDOpt(bool opt)
{
	m_segment_id_defined = opt;
}
void ExternalTimeHistory::SetTypeOpt(bool opt)
{
	m_type_defined = opt;
}
void ExternalTimeHistory::SetSolutionStepOpt(bool opt)
{
	m_step_defined = true;
}

