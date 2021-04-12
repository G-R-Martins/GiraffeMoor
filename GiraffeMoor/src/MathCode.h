#pragma once

class MathCode
{
public:
	MathCode();
	~MathCode();

	//============================================================================

			/*-------
			Functions
			--------*/

	//Reads GiraffeMoor file
	bool Read(FILE *f);

	//Writes Giraffe file
	void WriteGiraffeModelFile(FILE *f);

	//Setting start time ('t0') to apply math code
	void SetStartTime(const double& start);
	
	//Getting start time
	const double& GetStartTime();
	
	//Changing 't0' for the real time
	void SetEquationInitialTime(const double& init);

private:
	//============================================================================

			/*-------
			Variables
			--------*/

	//Vector with equations
	std::vector <std::string> equations{"0","0","0","0","0","0"};

	double start_time;
};

