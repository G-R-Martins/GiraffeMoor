#include "PCH.h"
#include "VesselDisplacement.h"
#include "Log.h"



VesselDisplacement::VesselDisplacement()
	: vesselID(0), step(0), isTable(false), isSineWave(false), isMathCode(false),
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
		Log::getInstance().AddWarning("\n   + Error reading vessel displacement.\n");
		return false;
	}

	//Step
	if (fscanf(f, "%s %d", str, &step) == EOF || strcmp(str, "Step"))
	{
		warning = "\n   + Error reading step of the displacement of the vessel number " + std::to_string(vesselID);
		Log::getInstance().AddWarning(warning);
		return false;
	}

	//Reads a table
	if (fscanf(f, "%s", str) != EOF && !strcmp(str, "TimeSeries"))
	{
		//Alloc table
		time_series = new Table();
		if (!time_series->Read(f))
		{
			warning = "\n   + Error reading time series displacement of the vessel number " + std::to_string(vesselID);
			Log::getInstance().AddWarning(warning);
			return false;
		}
		else if (time_series->table[0][0] == 0)
		{
			warning = "\n   + There is no need to define a null row.\nPlease check your Giraffe input file (or the monitor) and make sure you are running the whole desirable time.\n";
			Log::getInstance().AddWarning(warning);
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
			Log::getInstance().AddWarning(warning);
			return false;
		}

		isSineWave = true;
		step = sineWaveDisp->GetStartStep();
	}
	else if (!strcmp(str, "MathCode"))
	{
		//Alloc table
		mathCode = new MathCode();
		if (!mathCode->Read(f))
		{
			warning = "\n   + Error reading 'MathCode' of the displacement of the vessel number " + std::to_string(vesselID);
			Log::getInstance().AddWarning(warning);
			return false;
		}

		isMathCode = true;
	}

	//All ok
	return true;
}

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

unsigned int VesselDisplacement::GetVesselID()
{
	return this->vesselID;
}

unsigned int VesselDisplacement::GetStep()
{
	return this->step;
}

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