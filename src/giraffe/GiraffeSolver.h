#pragma once


class GiraffeSolver
{
private:
	/*------------
	Solver options
	-------------*/

	//Number of cores used for Giraffe
	unsigned int nCores;

	//Linear system solver option
	/// if is not direct, it will be defined as 'iterative'
	bool isDirect;

	bool runGiraffe;

public:
	GiraffeSolver();
	~GiraffeSolver() = default;

	//=========================================================================================

	/*-------------
	  I/O Funtions
	 -------------*/

	//Read input file
	bool Read(FILE* f);

	//Writes Giraffe input file (.inp)
	void WriteGiraffeModelFile(FILE* f) const;

	/*------------------
	  Set/Get functions
	 ------------------*/
	//Set options with readed date
	void SetSolverOptions(unsigned int cores, bool bool_direct);
	//Get Giraffe solver boolena
	bool GetRunOption();
};

