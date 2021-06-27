#pragma once


class PipeSection
{
public:
	PipeSection();
	PipeSection(const unsigned int& num, const char& tp, const double& d, const double& r,
				const double& ea, const double& ei, const double& gj, const double& ga,
				const double& cdt, const double& cdn, const double& cat, const double& can,
				const double& young, const double& poisson);
	~PipeSection();
	
	//Writes Giraffe file
	void WriteGiraffeModelFile(std::ostream& fout) const;	

	//Variables
	unsigned int number;
	char type;
	double diameter;
	double rho;
	double EA;
	double EI;
	double GJ;
	double GA;
	double CDt;
	double CDn;
	double CAt;
	double CAn;
	double E;
	double nu;
};

