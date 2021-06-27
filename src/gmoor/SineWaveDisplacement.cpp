#include "PCH.h"
#include "SineWaveDisplacement.h"
#include "Log.h"


SineWaveDisplacement::SineWaveDisplacement()
	: start_time(-1), step(0)
{
	period.fill(0.0);
	amplitude.fill(0.0);
	phase.fill(0.0);
	mean.table.clear();
	isMathCode = true;
	equations.resize(6);
	mean_eq.clear();
}

//Copy constructor
SineWaveDisplacement::SineWaveDisplacement(const SineWaveDisplacement& original)
	: start_time(original.start_time), step(original.step), period(original.period), amplitude(original.amplitude), phase(original.phase),
	mean(original.mean), equations(original.equations)
{
	std::cout << "SineWAveDisplacement copied!\n";
}

SineWaveDisplacement::~SineWaveDisplacement()
{
	mean.table.clear();
	equations.clear();
	mean_eq.clear();
}

void SineWaveDisplacement::SetStartTime(const double& start)
{
	start_time = start;
}

unsigned int SineWaveDisplacement::GetStartStep()
{
	return this->step;
}

bool SineWaveDisplacement::Read(FILE *f)
{
	char str[200];
	
	if (fscanf(f, "%s", str) && !strcmp(str, "MeanDrift"))
	{
		if(!mean.Read(f))
			return false;
	}
	else //ERROR
	{
		Log::AddWarning("\n   + Error reading mean drift from sine wave displacement.");
		return false;
	}

	if (fscanf(f, "%s %lf %lf %lf %lf %lf %lf", str, &period[0], &period[1], &period[2], &period[3], &period[4], &period[5]) == EOF || strcmp(str, "Period"))
	{
		Log::AddWarning("\n   + Error reading period from sine wave displacement.");
		return false;
	}

	if (fscanf(f, "%s %lf %lf %lf %lf %lf %lf", str, &amplitude[0], &amplitude[1], &amplitude[2], &amplitude[3], &amplitude[4], &amplitude[5]) == EOF || strcmp(str, "Amplitude"))
	{
		Log::AddWarning("\n   + Error reading amplitude from sine wave displacement.");
		return false;
	}

	if (fscanf(f, "%s %lf %lf %lf %lf %lf %lf", str, &phase[0], &phase[1], &phase[2], &phase[3], &phase[4], &phase[5]) == EOF || strcmp(str, "Phase"))
	{
		Log::AddWarning("\n   + Error reading phase from sine wave displacement.");
		return false;
	}

	return true;
}

void SineWaveDisplacement::WriteGiraffeModelFile(std::ostream& fout) const
{
	fout << "\tNodalDisplacement" << number <<
		"\tNodeSet" << node_set <<
		"\tCS" << cs <<
		"\tMathCode" <<
		"\n\t//X\n\t" << equations[0] <<
		"\n\t//Y\n\t" << equations[1] <<
		"\n\t//Z\n\t" << equations[2] <<
		"\n\t//ROTX\n\t" << equations[3] <<
		"\n\t//ROTY\n\t" << equations[4] <<
		"\n\t//ROTZ\n\t" << equations[5];
}

void SineWaveDisplacement::GenerateMathCode()
{
	using namespace std::string_literals;

	std::string aux_str;

	if (start_time > 0.0)
	{
		// Mean drift
		for (size_t i = 0; i < 6; ++i)
		{
			double m = mean.table[0][i + 1] / mean.table[0][0];
			double h = -1 * m * start_time;

			aux_str = std::to_string(m) + "*t"s;
			if (h > 0)	
				aux_str += "+"s;
			if (h != 0)	
				aux_str += std::to_string(h);

			mean_eq.push_back(aux_str);
			aux_str.clear();
		}

		// Oscillations
		for (size_t i = 0; i < 6; ++i)
		{
			//Checks if there is movement in the current direction
			if (mean.table[0][i + 1] != 0.0 || amplitude[i] != 0.0)
			{
				equations[i] = "Begin if (t>"s + std::to_string(start_time + mean.table[0][0]) + ", ";
				
				//Position after mean drift
				if (mean.table[0][i + 1] != 0.0)
					equations[i] += std::to_string(mean.table[0][i + 1]);
				//Starts to write sine wave equation
				if (amplitude[i] != 0.0)
				{
					if (amplitude[i] > 0.0 && mean.table[0][i + 1] != 0.0) 
						equations[i] += "+"s;
					equations[i] += std::to_string(amplitude[i]) + "*sin((t-"s + std::to_string(start_time + mean.table[0][0]) + ")*2*pi/" + std::to_string(period[i]);
				}
				//Checks if phase is not null
				if (phase[i] > 0.0)
					equations[i] += "+"s + std::to_string(phase[i]);
				else if (phase[i] < 0.0)
					equations[i] += std::to_string(phase[i]);
				//End sine
				equations[i] += ")";


				//Checks if there is a mean drift in the current direction
				if (mean.table[0][i + 1] != 0.0)
					equations[i] += ", if (t>="s + std::to_string(start_time) + ", " + mean_eq[i] + ", 0)) End";
				else
					equations[i] += ", 0) End"s;
			}
			//No movement in the current direction
			else
				equations[i] = "Begin 0 End"s;
		}
	}
	else
		Log::AddWarning("\n   + Time is not defined for a \"SineWaveDisplacement\" block. Please, check your input file");

}