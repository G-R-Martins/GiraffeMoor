#pragma once
#include "SineWaveDisplacement.h"


class VesselDisplacement
{
private:
	//============================================================================

					/*--------
					|Variables|
					---------*/

	//Vessel number
	unsigned int vesselID;
		
	//Number of displacement step (if it exists)
	unsigned int step;

public:
	//Boolean to indicate the type of the displacement
	bool isTable, isSineWave, isMathCode, fromFile;
	unsigned int header_lines; //in the external csv/txt file 
	unsigned int n_times;      //lines in the csv/txt file

private:
	//Pointers to vessel displacement (Table, SineWaveDisplacement or MathCode)
	Table* time_series;
	SineWaveDisplacement* sineWaveDisp;
	MathCode* mathCode;
	std::string file_name;

public:
	VesselDisplacement();
	~VesselDisplacement();

	//============================================================================

					/*--------
					|Functions|
					---------*/

	bool Read(FILE* f);

	Table* const GetTimeSeries() const;
	SineWaveDisplacement* const GetSineWave() const;
	MathCode* const GetMathCode() const;
	std::string& GetFileName();
	const unsigned int& GetFileHeaders() const;
	const unsigned int& GetFileNTimes() const;


	unsigned int GetVesselID();
	unsigned int GetStep();

	void SetStartTime(const double& start);
	void SetStartTableTime(const double& start_time, const size_t& start_line);

};
