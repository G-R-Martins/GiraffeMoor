#pragma once
#include "Seabed.h"
#include "SeaCurrent.h"


//static double gravity;
class MoorEnvironment
{
public:
	MoorEnvironment();
	~MoorEnvironment();

	//Reads input file
	bool Read(FILE *f);
	
	//============================================================================

	/*-------
	Variables
	--------*/

	//General environment variables
	static double gravity;
	double rhofluid;
	double waterdepth;
	
	//Seabed object
	Seabed seabed;

	//Sea current
	std::vector <SeaCurrent> seacurrent_vector;
	
	//Boolean to indicate if there is a sea current
	bool seacurrent_exist;

	//Boolean to indicate if sea current have constant amplitude and azimuth
	bool const_seacurrent;
};

