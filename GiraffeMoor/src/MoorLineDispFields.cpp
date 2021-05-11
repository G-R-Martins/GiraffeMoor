#include "PCH.h"
#include "MoorLineDispFields.h"
#include "Log.h"


MoorLineDispFields::MoorLineDispFields()
	: number(0), step(0), isHarmonic(true), amplitude(0.0), mode(1)
{}


bool MoorLineDispFields::Read(FILE * f)
{
	//To save readed words/values
	char str[200];

	if (fscanf(f, "%s", str) && isdigit(str[0]))
		number = atoi(str);
	else
	{
		Log::AddWarning("\n   + Error reading a 'DispLineID' number\n");
		return false;
	}

	//Read Step
	if (fscanf(f, "%s %d", str, &step) == EOF || strcmp(str, "Step"))
	{
		std::string w = "\n   + 'Step' keyword is missing for the displacement field of the line number " + std::to_string(number) ;
		Log::AddWarning(w);
		return false;
	}
	//Read DisplacementField type (for now, only Harmonic is defined)
	if (fscanf(f, "%s", str) == EOF || strcmp(str, "Harmonic"))
	{
		std::string w = "\n   + Displacement field must be 'Harmonic', please check it for the line number " + std::to_string(number) ;
		Log::AddWarning(w);
		return false;
	}
	//Read sine amplitude
	if (fscanf(f, "%s %lf", str, &amplitude) == EOF || strcmp(str, "Amplitude"))
	{
		std::string w = "\n   + 'Amplitude' keyword is missing for the displacement field of the line number " + std::to_string(number) ;
		Log::AddWarning(w);
		return false;
	}
	//Read sinusoidal mode
	if (fscanf(f, "%s %d", str, &mode) == EOF || strcmp(str, "Mode"))
	{
		std::string w = "\n   + 'Mode' keyword is missing for the displacement field of the line number " + std::to_string(number) ;
		Log::AddWarning(w);
		return false;
	}
	


	//All OK while reading
	return true;
}



/*------
 Getters 
 ------*/

unsigned int MoorLineDispFields::GetNumber() const
{
	return this->number;
}
unsigned int MoorLineDispFields::GetStep() const
{
	return this->step;
}
bool MoorLineDispFields::IsHarmonic() const
{
	return this->isHarmonic;
}
double MoorLineDispFields::GetAmplitude() const
{
	return this->amplitude;
}
unsigned int MoorLineDispFields::GetMode() const
{
	return this->mode;
}


/*------------------
Overloaded operators
-------------------*/

bool operator<(const MoorLineDispFields& disp1, const MoorLineDispFields& disp2)
{
	return disp1.number < disp2.number;
}
bool operator>(const MoorLineDispFields& disp1, const MoorLineDispFields& disp2)
{
	return !( disp1 < disp2 );
}
bool operator==(const MoorLineDispFields& disp1, const MoorLineDispFields& disp2)
{
	return disp1.number == disp2.number;
}
bool operator!=(const MoorLineDispFields& disp1, const MoorLineDispFields& disp2)
{
	return !( disp1 == disp2 );
}
