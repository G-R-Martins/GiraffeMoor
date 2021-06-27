#pragma once



class LineDisplacementField
{
	unsigned int number;
	unsigned int step;
	bool isHarmonic;
	double amplitude;
	unsigned int mode;

	//============================================================================

public:
	
	/// Constructors and destructor
	LineDisplacementField();
	LineDisplacementField(const LineDisplacementField&) = default;
	LineDisplacementField(LineDisplacementField&&) = default;
	~LineDisplacementField() = default;

			/*--------
			 Functions
 			 --------*/
	
	//Read input file
	bool Read(FILE* f);

	///				 
	/// Get functions
	///				 

	unsigned int GetNumber() const;
	unsigned int GetStep() const;
	bool IsHarmonic() const;
	double GetAmplitude() const;
	unsigned int GetMode() const;


	//============================================================================

	
	/*------------------
	Overloaded operators
	-------------------*/

	friend bool operator<(const LineDisplacementField& disp1, const LineDisplacementField& disp2);
	friend bool operator>(const LineDisplacementField& disp1, const LineDisplacementField& disp2);
	friend bool operator==(const LineDisplacementField& disp1, const LineDisplacementField& disp2);
	friend bool operator!=(const LineDisplacementField& disp1, const LineDisplacementField& disp2);

	//Assignment operators (copy and move)
	LineDisplacementField& operator=(LineDisplacementField&& other) = default;
	LineDisplacementField& operator=(const LineDisplacementField& other) = default;
};

