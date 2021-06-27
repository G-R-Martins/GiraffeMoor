#pragma once

class MathCode
{
	//Vector with equations
	std::vector <std::string> equations{"0","0","0","0","0","0"};

	double start_time;

	//============================================================================
public:
	MathCode();
	~MathCode();

	//============================================================================

			/*-------
			Functions
			--------*/

	//Reads GiraffeMoor file
	bool Read(FILE *f);

	//Setting start time ('t0') to apply math code
	void SetStartTime(const double& start);
	
	//Getting start time
	const double& GetStartTime();
	
	//Changing 't0' for the real time
	void SetEquationInitialTime(const double& init);


	///
	///Overloaded operator to print line in the summary file 
	///
	friend std::ostream& operator<<(std::ostream& out, const MathCode& mc);
	friend std::ostream& operator<<(std::ostream& out, MathCode* mcPtr);
};

