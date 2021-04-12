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

	//Boolean to indicate if current nodal force uses math code
	bool isMathCode;
};

