#pragma once


class CoordinateSystem
{
public:
	CoordinateSystem();
	~CoordinateSystem();

	//Writes Giraffe model
	void WriteGiraffeModelFile(FILE *f);

	//======================================================================================================

					/*--------
					|Variables|
					---------*/
	
	//ID do CoordinateSystem
	unsigned int number;
	
	//Versores
	std::array<double, 3> E1;
	std::array<double, 3> E3;
};

