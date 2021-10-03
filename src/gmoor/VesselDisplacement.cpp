#include "PCH.h"
#include "VesselDisplacement.h"
#include "Log.h"
#include "AuxFunctions.h"
#include "IO.h" //to get the folder name


VesselDisplacement::VesselDisplacement()
	: m_vesselID(0), m_solution_step(0),
	m_is_table(false), m_is_sine_wave(false), m_is_math_code(false), m_is_external_file(false),
	m_file_name("\0"), m_header_lines(0), m_tot_steps(0),
	m_ptr_time_series(nullptr), m_ptr_sine_wave(nullptr), m_ptr_math_code(nullptr)
{}
VesselDisplacement::~VesselDisplacement()
{
	if (m_ptr_sine_wave)
	{
		delete m_ptr_sine_wave;
		m_ptr_sine_wave = nullptr;
	}
	else if (m_ptr_math_code)
	{
		delete m_ptr_math_code;
		m_ptr_math_code = nullptr;
	}
}


//	char str[500];			//salva palavras-chave lidas e valores lidos
//	std::string warning = "";
//
//
//	//Displacement ID
//	if (fscanf(f, "%s", str) != EOF && isdigit(str[0]))
//		vesselID = atoi(str);
//	else
//	{
//		Log::AddWarning("\n   + Error reading vessel displacement.\n");
//		return false;
//	}
//
//	//Step
//	if (fscanf(f, "%s %d", str, &step) == EOF || strcmp(str, "Step"))
//	{
//		warning = "\n   + Error reading step of the displacement of the vessel number " + std::to_string(vesselID);
//		Log::AddWarning(warning);
//		return false;
//	}
//
//	//Read mathematical expressions for displacements
//	if (fscanf(f, "%s", str) != EOF && !strcmp(str, "MathCode"))
//	{
//		//Alloc table
//		mathCode = new MathCode();
//		if (!mathCode->Read(f))
//		{
//			warning = "\n   + Error reading 'MathCode' of the displacement of the vessel number " + std::to_string(vesselID);
//			Log::AddWarning(warning);
//			return false;
//		}
//
//		isMathCode = true;
//	}
//	//Read from external file (GiraffeMoor check if the file exists and only Giraffe will actually read it)
//	else if (!strcmp(str, "File"))
//	{
//		AuxFunctions::Read::TryComment(f);
//
//		//Read the name of the file with the table data 
//		///file name must be enclosed by quotes
//		char c;
//		if (fscanf(f, "%[^\"]*", str) == EOF ||       /*read until double quotes (whitespaces)*/
//			fscanf(f, "%c%[^\"]s", &c, str) == EOF || /*read file name, until the last double quotes*/
//			c != '\"' || fscanf(f, "%c", &c) == EOF || c != '\"')  /*check first double quotes and read last one*/
//			return false;
//		else
//			file_name = str;
//
//		//Checks format (must be .csv or .txt)
//		size_t dot_pos = file_name.find('.');				// position of the dot, before file format
//		std::string_view format(file_name.c_str() + dot_pos + 1, 3);	// get a substring with the letters after the dot
//		
//		//Invalid format
//		if (format != "csv" && format != "txt")
//		{
//			warning = "\n   + Invalid format for the file with displacement data of the vessel number " + std::to_string(vesselID);
//			Log::AddWarning(warning);
//			return false;
//		}
//
//		//Tries to open the file before continue
//		std::string full_file_name = IO::folder_name + "time series/" + std::string(file_name);
//		std::ifstream inp(full_file_name);
//
//		if (!inp.is_open())
//		{
//			warning = "\n   + Error trying to open the file with displacement of the vessel number" + std::to_string(vesselID);
//			Log::AddWarning(warning);
//			return false;
//		}
//
//		//Check for error during the reading of the number of header and data lines
//		if (fscanf(f, "%s %d", str, &header_lines) == EOF || strcmp(str, "HeaderLines") //set number of header lines
//			|| fscanf(f, "%s %d", str, &n_times) == EOF || strcmp(str, "NTimes")) //set number of lines with data
//			return false;
//
//		fromFile = true;
//	}
//	//Reads a table
//	else if (!strcmp(str, "TimeSeries"))
//	{
//		//Alloc table
//		time_series = new Table();
//		if (!time_series->Read(f))
//		{
//			warning = "\n   + Error reading time series displacement of the vessel number " + std::to_string(vesselID);
//			Log::AddWarning(warning);
//			return false;
//		}
//		//Check for first line with zeros
//		if (time_series->table[0][0] == 0)
//		{
//			warning = "\n   + There is no need to define a null row.\nPlease check your Giraffe input file (or the monitor) and make sure you are running the whole desirable time.\n";
//			Log::AddWarning(warning);
//		}
//		isTable = true;
//	}
//	//Uses math code to generate a mean drift and a sinusoidal displacement
//	else if (!strcmp(str, "SineWave"))
//	{
//		//Alloc sine wave 
//		sineWaveDisp = new SineWaveDisplacement();
//
//		//Reads input file
//		if (!sineWaveDisp->Read(f))
//		{
//			warning = "\n   + Error reading 'SineWave' displacement of the vessel number " + std::to_string(vesselID);
//			Log::AddWarning(warning);
//			return false;
//		}
//
//		isSineWave = true;
//		step = sineWaveDisp->GetStartStep();
//	}
//	//ERROR
//	else
//	{
//		warning = "\n   + Error reading displacement type of the vessel number " + std::to_string(vesselID);
//		Log::AddWarning(warning);
//		return false;
//	}
//
//
//	//All ok
//	return true;



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
	if (this->m_is_sine_wave)
		this->m_ptr_sine_wave->SetStartTime(start);
	else if (this->m_is_math_code)
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
void VesselDisplacement::SetSineWave()
{
	m_is_sine_wave = true;
	m_ptr_sine_wave = new SineWaveDisplacement();
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

