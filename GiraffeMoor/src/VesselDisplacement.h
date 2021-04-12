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
	bool isTable, isSineWave, isMathCode;

private:
	//Pointers to vessel displacement (Table, SineWaveDisplacement or MathCode)
	Table* time_series;
	SineWaveDisplacement* sineWaveDisp;
	MathCode* mathCode;

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

	unsigned int GetVesselID();
	unsigned int GetStep();

	void SetStartTime(const double& start);
	void SetStartTableTime(const double& start_time, const size_t& start_line);

};
