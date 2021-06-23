#pragma once
#include "SineWaveDisplacement.h"


class VesselDisplacement
{
	//Vessel number
	unsigned int vesselID;
		
	//Number of displacement step (if it exists)
	unsigned int step;

	//Boolean to indicate the type of the displacement
	bool isTable, isSineWave, isMathCode, fromFile;

	//External files
	unsigned int header_lines; //in the external csv/txt file 
	unsigned int n_times;      //lines in the csv/txt file
	
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

	//Set functions
	void SetStartTime(const double& start);
	void SetStartTableTime(const double& start_time, const size_t& start_line);
	Table* const GetTimeSeries() const;
	SineWaveDisplacement* const GetSineWave() const;
	MathCode* const GetMathCode() const;
	std::string& GetFileName();
	const unsigned int& GetFileHeaders() const;
	const unsigned int& GetFileNTimes() const;

	//Get functions
	unsigned int GetVesselID() const;
	unsigned int GetStep() const;

	bool CheckIfIsTable() const;
	bool CheckIfIsMathCode() const;
	bool CheckIfIsSineWave() const;
	bool CheckIfIsExternalFile() const;

};
