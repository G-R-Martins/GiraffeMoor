#include "PCH.h"
#include "LineDisplacementField.h"


LineDisplacementField::LineDisplacementField()
	: m_number(0), m_step_id(0), 
	m_is_harmonic(true), m_amplitude(0.0), m_mode(1)
{}

LineDisplacementField::~LineDisplacementField()
{}

void LineDisplacementField::SetIDNumber(unsigned int number)
{
	m_number = number;
}

void LineDisplacementField::SetSolutionStep(unsigned int step_id)
{
	m_step_id = step_id;
}

void LineDisplacementField::SetAmplitude(double amplitude)
{
	m_amplitude = amplitude;
}

void LineDisplacementField::SetMode(unsigned int mode)
{
	m_mode = mode;
}

void LineDisplacementField::SetHarmonicOpt(bool is_harmonic)
{
	m_is_harmonic = is_harmonic;
}


//bool LineDisplacementField::Read(FILE * f)
//{
//	//To save readed words/values
//	char str[200];
//
//	if (fscanf(f, "%s", str) && isdigit(str[0]))
//		number = atoi(str);
//	else
//	{
//		Log::AddWarning("\n   + Error reading a 'DispLineID' number\n");
//		return false;
//	}
//
//	//Read Step
//	if (fscanf(f, "%s %d", str, &step) == EOF || strcmp(str, "Step"))
//	{
//		std::string w = "\n   + 'Step' keyword is missing for the displacement field of the line number " + std::to_string(number) ;
//		Log::AddWarning(w);
//		return false;
//	}
//	//Read DisplacementField type (for now, only Harmonic is defined)
//	if (fscanf(f, "%s", str) == EOF || strcmp(str, "Harmonic"))
//	{
//		std::string w = "\n   + Displacement field must be 'Harmonic', please check it for the line number " + std::to_string(number) ;
//		Log::AddWarning(w);
//		return false;
//	}
//	//Read sine amplitude
//	if (fscanf(f, "%s %lf", str, &amplitude) == EOF || strcmp(str, "Amplitude"))
//	{
//		std::string w = "\n   + 'Amplitude' keyword is missing for the displacement field of the line number " + std::to_string(number) ;
//		Log::AddWarning(w);
//		return false;
//	}
//	//Read sinusoidal mode
//	if (fscanf(f, "%s %d", str, &mode) == EOF || strcmp(str, "Mode"))
//	{
//		std::string w = "\n   + 'Mode' keyword is missing for the displacement field of the line number " + std::to_string(number) ;
//		Log::AddWarning(w);
//		return false;
//	}
//	
//
//
//	//All OK while reading
//	return true;
//}



/// 
/// Overloaded operators
/// 

bool operator<(const LineDisplacementField& disp1, const LineDisplacementField& disp2)
{
	return disp1.m_number < disp2.m_number;
}
bool operator>(const LineDisplacementField& disp1, const LineDisplacementField& disp2)
{
	return !( disp1 < disp2 );
}
bool operator==(const LineDisplacementField& disp1, const LineDisplacementField& disp2)
{
	return disp1.m_number == disp2.m_number;
}
bool operator!=(const LineDisplacementField& disp1, const LineDisplacementField& disp2)
{
	return !( disp1 == disp2 );
}

