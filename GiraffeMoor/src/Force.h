#pragma once


class Load
{
public:
	Load();
	virtual ~Load();

//==========================================================================================================================

				/*----------------
				|Virtual functions|
				-----------------*/

	virtual void WriteGiraffeModelFile(FILE* f) = 0;

//==========================================================================================================================

				/*--------
				|Variables|
				---------*/

	//Load ID
	unsigned int number;

	// Coordinate system ID
	unsigned int CS; 

	//Booleans to indicate if current nodal force uses math code or an external file
	///otherwise, must be defined in the GiraffeMoor input file after 'TimeSeries' keyword
	bool isMathCode, extFile;
};

