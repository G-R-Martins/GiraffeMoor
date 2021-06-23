#pragma once


class Load
{
	//Load ID
	unsigned int number;

	// Coordinate system ID
	unsigned int CS; 

	//Booleans to indicate if current nodal force uses math code or an external file
	///otherwise, must be defined in the GiraffeMoor input file after 'TimeSeries' keyword
	bool isMathCode, extFile;

	//==========================================================================================================================

public:
	Load();
	virtual ~Load();

	//Set functions
	void SetNumber(unsigned int ID);
	void SetCoordinateSystem(unsigned int CS);
	void DefineMathCodeOption();
	void DefineExternalFileOption();

	//Get functions
	unsigned int GetNumber();
	unsigned int GetCoordinateSystem();
	bool CheckIfIsMathCode();
	bool CheckIfIsExternalFile();





	//==========================================================================================================================

				/*----------------
				|Virtual functions|
				-----------------*/

	virtual void WriteGiraffeModelFile(FILE* f) = 0;

};

