#include "PCH.h"
#include "VesselDisplacement.h"
#include "Log.h"
#include "AuxFunctions.h"


//Global variable
extern std::string folder_name;


VesselDisplacement::VesselDisplacement()
	: vesselID(0), step(0), 
	isTable(false), isSineWave(false), isMathCode(false), fromFile(false),
	file_name("\0"), header_lines(0), n_times(0),
	time_series(time_series), sineWaveDisp(nullptr), mathCode(nullptr)
{}
VesselDisplacement::~VesselDisplacement()
{
	if (sineWaveDisp)
	{
		delete sineWaveDisp;
		sineWaveDisp = nullptr;
	}
	else if (mathCode)
	{
		delete mathCode;
		mathCode = nullptr;
	}
}


bool VesselDisplacement::Read(FILE* f)
{
	char str[500];			//salva palavras-chave lidas e valores lidos
	std::string warning = "";


	//Displacement ID
	if (fscanf(f, "%s", str) != EOF && isdigit(str[0]))
		vesselID = atoi(str);
	else
	{
		Log::AddWarning("\n   + Error reading vessel displacement.\n");
		return false;
	}

	//Step
	if (fscanf(f, "%s %d", str, &step) == EOF || strcmp(str, "Step"))
	{
		warning = "\n   + Error reading step of the displacement of the vessel number " + std::to_string(vesselID);
		Log::AddWarning(warning);
		return false;
	}

	//Read mathematical expressions for displacements
	if (fscanf(f, "%s", str) != EOF && !strcmp(str, "MathCode"))
	{
		//Alloc table
		mathCode = new MathCode();
		if (!mathCode->Read(f))
		{
			warning = "\n   + Error reading 'MathCode' of the displacement of the vessel number " + std::to_string(vesselID);
			Log::AddWarning(warning);
			return false;
		}

		isMathCode = true;
	}
	//Read from external file (GiraffeMoor check if the file exists and only Giraffe will actually read it)
	else if (!strcmp(str, "File"))
	{
		AuxFunctions::Read::TryComment(f);

		//Read the name of the file with the table data 
		///file name must be enclosed by quotes
		char c;
		if (fscanf(f, "%[^\"]*", str) == EOF ||       /*read until double quotes (whitespaces)*/
			fscanf(f, "%c%[^\"]s", &c, str) == EOF || /*read file name, until the last double quotes*/
			c != '\"' || fscanf(f, "%c", &c) == EOF || c != '\"')  /*check first double quotes and read last one*/
			return false;
		else
			file_name = str;

		//Checks format (must be .csv or .txt)
		size_t dot_pos = file_name.find('.');				// position of the dot, before file format
		std::string_view format(file_name.c_str() + dot_pos + 1, 3);	// get a substring with the letters after the dot
		
		//Invalid format
		if (format != "csv" && format != "txt")
		{
			warning = "\n   + Invalid format for the file with displacement data of the vessel number " + std::to_string(vesselID);
			Log::AddWarning(warning);
			return false;
		}

		//Tries to open the file before continue
		std::string full_file_name = folder_name + "time series/" + std::string(file_name);
		std::ifstream inp(full_file_name);

		if (!inp.is_open())
		{
			warning = "\n   + Error trying to open the file with displacement of the vessel number" + std::to_string(vesselID);
			Log::AddWarning(warning);
			return false;
		}

		//Check for error during the reading of the number of header and data lines
		if (fscanf(f, "%s %d", str, &header_lines) == EOF || strcmp(str, "HeaderLines") //set number of header lines
			|| fscanf(f, "%s %d", str, &n_times) == EOF || strcmp(str, "NTimes")) //set number of lines with data
			return false;

		fromFile = true;
	}
	//Reads a table
	else if (!strcmp(str, "TimeSeries"))
	{
		//Alloc table
		time_series = new Table();
		if (!time_series->Read(f))
		{
			warning = "\n   + Error reading time series displacement of the vessel number " + std::to_string(vesselID);
			Log::AddWarning(warning);
			return false;
		}
		//Check for first line with zeros
		if (time_series->table[0][0] == 0)
		{
			warning = "\n   + There is no need to define a null row.\nPlease check your Giraffe input file (or the monitor) and make sure you are running the whole desirable time.\n";
			Log::AddWarning(warning);
		}
		isTable = true;
	}
	//Uses math code to generate a mean drift and a sinusoidal displacement
	else if (!strcmp(str, "SineWave"))
	{
		//Alloc sine wave 
		sineWaveDisp = new SineWaveDisplacement();

		//Reads input file
		if (!sineWaveDisp->Read(f))
		{
			warning = "\n   + Error reading 'SineWave' displacement of the vessel number " + std::to_string(vesselID);
			Log::AddWarning(warning);
			return false;
		}

		isSineWave = true;
		step = sineWaveDisp->GetStartStep();
	}
	//ERROR
	else
	{
		warning = "\n   + Error reading displacement type of the vessel number " + std::to_string(vesselID);
		Log::AddWarning(warning);
		return false;
	}


	//All ok
	return true;
}


/*******************
 *  GET functions  *
 *******************/

Table* const VesselDisplacement::GetTimeSeries() const
{
	return this->time_series;
}
SineWaveDisplacement* const VesselDisplacement::GetSineWave() const
{
	return this->sineWaveDisp;
}
MathCode* const VesselDisplacement::GetMathCode() const
{
	return this->mathCode;
}
std::string& VesselDisplacement::GetFileName() 
{
	return this->file_name;
}

const unsigned int& VesselDisplacement::GetFileHeaders() const
{
	return this->header_lines;
}
const unsigned int& VesselDisplacement::GetFileNTimes() const 
{
	return this->n_times;
}
unsigned int VesselDisplacement::GetVesselID() const
{
	return this->vesselID;
}
unsigned int VesselDisplacement::GetStep() const
{
	return this->step;
}


 /*******************
 *  GET functions  *
 *******************/

void VesselDisplacement::SetStartTime(const double& start)
{

	if (this->isSineWave)
		this->sineWaveDisp->SetStartTime(start);
	else if (this->isMathCode)
		this->mathCode->SetEquationInitialTime(start);
}

void VesselDisplacement::SetStartTableTime(const double& start_time, const size_t& start_line)
{
	this->time_series->SetStartTime(start_time, start_line);
}