#include "PCH.h"
#include "SolutionStep.h"
#include "Log.h"


SolutionStep::SolutionStep()
	: number(0), isStatic(true), global_start(0.0), end_time(0.0), timestep(0.0), 
	max_timestep(0.0), min_timestep(0.0), sample(0), beta_new(0.0), gamma_new(0.0), alpha_ray(0.0), beta_ray(0.0)
{}

SolutionStep::~SolutionStep()
{}


//Overloaded operators
bool operator<(const SolutionStep& obj1, const SolutionStep& obj2)
{
	return obj1.number < obj2.number;
}
bool operator>(const SolutionStep& obj1, const SolutionStep& obj2)
{
	return !(obj1 < obj2);
}

bool operator==(const SolutionStep& obj1, const SolutionStep& obj2)
{
	return obj1.number == obj2.number;
}
bool operator!=(const SolutionStep& obj1, const SolutionStep& obj2)
{
	return !(obj1 == obj2);
}


//Reads input file
bool SolutionStep::Read(FILE* f)
{
	using namespace std::string_literals;

	char str[200];
	fpos_t pos;				//vari�vel que salva ponto do stream de leitura

	//Line number
	if (fscanf(f, "%s", str) && isdigit(str[0]))
		number = atoi(str);
	else
	{
		Log::AddWarning("\n   + Error reading analysis step number.");
		return false;
	}

	//Solution type
	if (fscanf(f, "%s", str) && !strcmp(str, "static"))	isStatic = true;
	else if (!strcmp(str, "dynamic"))					isStatic = false;
	else //ERROR
	{
		Log::AddWarning("\n   + Analysis should be \"static\" or \"dynamic\".");
		return false;
	}

	//End time
	if (fscanf(f, "%s %lf", str, &end_time) && !strcmp(str, "Time"));
	else //ERROR (End time)
	{
		std::string w = "\n   + Error reading solution step number " + std::to_string(number);
		Log::AddWarning(w);
		return false;
	}

	//Time step
	if (fscanf(f, "%s %lf", str, &timestep) && !strcmp(str, "TimeStep"));
	else //ERROR
	{
		std::string w = "\n   + Error reading solution step number " + std::to_string(number);
		Log::AddWarning(w);
		return false;
	}

	// OPTIONAL
	//	Maximum time step
	fgetpos(f, &pos);
	if (fscanf(f, "%s %lf", str, &max_timestep) && !strcmp(str, "MaxTimeStep"));
	else //No maximum time step definition
	{
		max_timestep = timestep;
		fsetpos(f, &pos);
	}

	//Minimum time step
	if (fscanf(f, "%s %lf", str, &min_timestep) && !strcmp(str, "MinTimeStep"));
	else //ERROR
	{
		std::string w = "\n   + Error reading solution time parameters of the step number " + std::to_string(number);
		Log::AddWarning(w);
		return false;
	}

	//Sample
	if (fscanf(f, "%s %d", str, &sample) && !strcmp(str, "Sample"));
	else //ERROR
	{
		std::string w = "\n   + Error reading solution time parameters of the step number " + std::to_string(number);
		Log::AddWarning(w);
		return false;
	}

	///
	/// Numerical damping for dynamic analysis 
	///
	
	//Check if user has defined numerical damping for the analysis step
	if (!fgetpos(f, &pos) && fscanf(f, "%s", str) && !strcmp(str, "NumericalDamping"))// && isStatic)
	//{
		/*if (fscanf(f, "%s", str) && ( !strcmp(str, "null") || !strcmp(str, "mild") || !strcmp(str, "moderate") || !strcmp(str, "high") || !strcmp(str, "extreme") ))
		{
			std::string w = "\n   + There is no need to define numerical damping for the static analysis of the step number " + std::to_string(number);
			Log::AddWarning(w);
		}*/
	//}
	//else if (/*!isStatic && */!strcmp(str, "NumericalDamping"))
	{
		//Damping cases:
		if (fscanf(f, "%s", str) && !strcmp(str, "null"))
		{
			beta_new = 0.3;
			gamma_new = 0.5;
		}
		else if (!strcmp(str, "mild"))
		{
			beta_new = 0.3;
			gamma_new = 0.505;
		}
		else if (!strcmp(str, "moderate"))
		{
			beta_new = 0.3;
			gamma_new = 0.52;
		}
		else if (!strcmp(str, "high"))
		{
			beta_new = 0.3;
			gamma_new = 0.55;
		}
		else if (!strcmp(str, "extreme"))
		{
			beta_new = 0.3;
			gamma_new = 0.6;
		}
		else //ERROR
		{
			std::string w = "\n   + Please define one of these keywords for setting numerical damping parameters:\n\n";
			w = R"(	 ------------------------------
	|  Keyword   |  Beta |  Gamma  |
	|------------|-------|---------|
	|  null      |  0.3  |  0.500  |
	|  mild      |  0.3  |  0.505  |
	|  moderate  |  0.3  |  0.520  |
	|  high      |  0.3  |  0.550  |
	|  extreme   |  0.3  |  0.600  |
	 ------------------------------)";
			Log::AddWarning(w);
			return false;
		}

		//Warning for static analysis
		if ( isStatic )
		{
			std::string w = "\n   + There is no need to define numerical damping for the static analysis of the step number " + std::to_string(number);
			Log::AddWarning(w);
		}
	}
	else if (!isStatic && strcmp(str, "NumericalDamping"))
	{
		std::string w = "\n   + Numerical damping was not defined for the dynamic step number " + std::to_string(number) 
			+ ". Newmark coeficients were set to zero.";
		Log::AddWarning(w);
		fsetpos(f, &pos);
	}
	else
		fsetpos(f, &pos);

	//Check if user has defined Rayleigh damping for the analysis step
	if ( !fgetpos(f, &pos) && fscanf(f, "%s", str) && !strcmp(str, "RayleighDamping") &&
		fscanf(f, "%s %lf", str, &alpha_ray) && !strcmp(str, "Alpha") && fscanf(f, "%s %lf", str, &beta_ray) && !strcmp(str, "Beta") )
	{
		if ( isStatic )
		{
			std::string w = "\n   + There is no need to define Rayleigh damping for the static analysis of the step number "
				+ std::to_string(number);
			Log::AddWarning(w);
		}
	}
	else
		fsetpos(f, &pos);

	//All ok while reading
	return true;
}

void SolutionStep::SetGlobalStart(double time)
{ this->global_start = time; }

unsigned int SolutionStep::GetNumber() const
{
	return this->number;
}

double SolutionStep::GetGlobalStart() const
{
	return this->global_start;
}

double SolutionStep::GetEndTime() const
{
	return this->end_time;
}

double SolutionStep::GetTimestep() const
{
	return this->timestep;
}

double SolutionStep::GetMaxTimestep() const
{
	return this->max_timestep;
}

double SolutionStep::GetMinTimestep() const
{
	return this->min_timestep;
}

int SolutionStep::GetSample() const
{
	return this->sample;
}

double SolutionStep::GetBeta_new() const
{
	return this->beta_new;
}

double SolutionStep::GetGamma_new() const
{
	return this->gamma_new;
}

double SolutionStep::GetAlpha_ray() const
{
	return this->alpha_ray;
}

double SolutionStep::GetBeta_ray() const
{
	return this->beta_ray;
}

bool SolutionStep::CheckIfIsStatic() const
{
	return this->isStatic;
}
