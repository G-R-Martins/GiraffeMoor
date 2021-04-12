#pragma once
#include "Seabed.h"
#include "SeaCurrent.h"
#include "BoolTable.h"


class Environment
{
public:
	Environment();
	~Environment();

	//============================================================================

	//Writes input file
	void WriteGiraffeModelFile(FILE *f);

	//============================================================================

	/*-------
	Variables
	--------*/
	
	double gravity;
	double rhofluid;
	double waterdepth;

	//============================================================================

	/*-----
	Objects
	------*/

	//Gravity booltable
	BoolTable bool_g;

	//Sea current booltable
	BoolTable bool_current;

	//Seabed object
	Seabed seabed; 
	
	//Vector with sea current data
	std::vector <SeaCurrent> seacurrent_vector;
};

