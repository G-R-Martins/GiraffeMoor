#pragma once



class MoorLineDispFields
{
private:
	
	/*-------
	Variables
	--------*/

	unsigned int number;
	unsigned int step;
	bool isHarmonic;
	//bool extFile;
	double amplitude;
	unsigned int mode;

	//============================================================================

public:
	
	/// Constructors and destructor
	MoorLineDispFields();
	MoorLineDispFields(const MoorLineDispFields&) = default;
	MoorLineDispFields(MoorLineDispFields&&) = default;
	~MoorLineDispFields() = default;

	/*-------
	Functions
	--------*/
	
	//Read input file
	bool Read(FILE* f);

	///				 
	/// Get functions
	///				 

	unsigned int GetNumber();
	unsigned int GetStep();
	bool IsHarmonic();
	//bool CheckIfIsExternalFile();
	double GetAmplitude();
	unsigned int GetMode();


	//============================================================================

	
	/*------------------
	Overloaded operators
	-------------------*/

	friend bool operator<(const MoorLineDispFields& disp1, const MoorLineDispFields& disp2);
	friend bool operator>(const MoorLineDispFields& disp1, const MoorLineDispFields& disp2);
	friend bool operator==(const MoorLineDispFields& disp1, const MoorLineDispFields& disp2);
	friend bool operator!=(const MoorLineDispFields& disp1, const MoorLineDispFields& disp2);

	//Assignment operators (copy and move)
	MoorLineDispFields& operator=(MoorLineDispFields&& other) = default;
	MoorLineDispFields& operator=(const MoorLineDispFields& other) = default;
};

