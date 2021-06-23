#pragma once
#include "Seabed.h"
#include "SeaCurrent.h"


class MoorEnvironment
{
	//General environment variables
	static double gravity;
	double rhofluid;
	double waterdepth;
	
	//Seabed object
	Seabed seabed;

	//Sea current
	std::vector<SeaCurrent> seacurrent_vector;
	
	//Boolean to indicate if there is a sea current
	bool seacurrent_exist;

	//Boolean to indicate if sea current have constant amplitude and azimuth
	bool const_seacurrent;
	
	//============================================================================

public:
	
	MoorEnvironment();
	~MoorEnvironment();

	//Reads input file
	bool Read(FILE *f);

	//Set functions
	static void SetGravity(double g);
	void SetRhoFluid(double rho);
	void SetWaterDepth(double wd);
	void SetBoolConstantSeaCurrent(bool b);

	//Get functions
	static double GetGravity();
	double GetRhoFluid() const;
	double GetWaterDepth() const;

	Seabed& GetSeabed();
	Seabed const& GetSeabed() const;

	SeaCurrent const& GetSeaCurrent(size_t sea_cur) const;
	SeaCurrent& GetSeaCurrent(size_t sea_cur);

	std::vector<SeaCurrent> const& GetSeaCurrentVec() const;
	std::vector<SeaCurrent>& GetSeaCurrentVec();

	bool CheckIfExistSeaCurrent() const;
	bool CheckIfExistSeaCurrent();
	bool CheckIfSeaCurrentIsConstant() const;
	bool CheckIfSeaCurrentIsConstant();

};

