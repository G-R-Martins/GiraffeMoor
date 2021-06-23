#pragma once


class SolverOptions
{
private:

	unsigned int n_cores;
	bool isDirect;

public:
	//Constructors
	SolverOptions();
	SolverOptions(unsigned int cores, bool bool_direct);
	
	~SolverOptions() = default;

	//Set options with readed date
	void SetSolverOptions(unsigned int cores, bool bool_direct);

	//Writes Giraffe input file (.inp)
	void WriteGiraffeModelFile(FILE* f) const;

};
