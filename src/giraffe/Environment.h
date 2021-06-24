#pragma once
#include "SeaCurrent.h"
#include "BoolTable.h"


class Environment
{
	double gravity;
	double rhofluid;
	double waterdepth;

	/*-----
	Objects
	------*/

	//Gravity booltable
	BoolTable bool_g;

	//Sea current booltable
	BoolTable bool_current;
		
	//Vector with sea current data
	std::vector <SeaCurrent> seacurrent_vector;
	
	//============================================================================
public:
	Environment();
	~Environment();

	/*-------
	Functions
	--------*/

	//Writes input file
	void WriteGiraffeModelFile(FILE *f);


	///
	///  Set/Get functions 
	///

	//Set variables
	void SetGravity(double g);
	void SetRhoFluid(double rho);
	void SetWaterDepth(double wd);
	//Set booltables
	void SetGravityBooltable(const BoolTable& bool_grav);
	void SetSeaCurrentBooltable(const BoolTable& bool_current);

	//Set vector
	void SetSeaCurrentVec(const std::vector<SeaCurrent>& current_vec);


	//Get variables
	double GetGravity() const;
	double GetRhoFluid() const;
	double GetWaterDepth() const;

	//Get booltables
	const BoolTable& GetGravityBooltable() const;
	BoolTable& GetGravityBooltable();
	const BoolTable& GetSeaCurrentBooltable() const;
	BoolTable& GetSeaCurrentBooltable();

	//Get vector
	const std::vector<SeaCurrent>& GetSeaCurrentVec() const;
	std::vector<SeaCurrent>& GetSeaCurrentVec();

};

