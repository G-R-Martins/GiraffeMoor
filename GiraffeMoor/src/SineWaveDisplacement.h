#pragma once
#include "NodalDisplacement.h"


class SineWaveDisplacement : public NodalDisplacement
{
private:
	//============================================================================

	/*---------------
	Private variables
	----------------*/

	//Solution time when vessel starts to move (mean drift or sine wave)
	double start_time;
	unsigned int step;

	/*--------
	Conteiners
	---------*/

	//Arrays with data
	std::array<double, 6> period;		//(X, Y, Z, ROTX, ROTY, ROTZ)
	std::array<double, 6> amplitude;	//(X, Y, Z, ROTX, ROTY, ROTZ)
	std::array<double, 6> phase;		//(X, Y, Z, ROTX, ROTY, ROTZ)
	
	//Vectors with math codes (equations)
	std::vector <std::string> equations;	//full equation: mean drift + sine wave (X, Y, Z, ROTX, ROTY, ROTZ)
	std::vector <std::string> mean_eq;		//mean drift (X, Y, Z, ROTX, ROTY, ROTZ)

	//============================================================================

public:
	SineWaveDisplacement();
	SineWaveDisplacement(const SineWaveDisplacement& original); //Copy constructor
	~SineWaveDisplacement();

	//============================================================================

	/*-------
	Functions
	--------*/

	//Reads GiraffeMoor file
	bool Read(FILE *f);
	
	//Writes Giraffe file
	void WriteGiraffeModelFile(FILE *f) override;

	//Generates math code
	void GenerateMathCode();

	//Function to set start time (start of mean drift or time series)
	void SetStartTime(const double& start);

	//Function to set start step (start of mean drift or time series)
	unsigned int GetStartStep();

	//============================================================================
	
	//Table with mean drift
	Table mean;				

};
