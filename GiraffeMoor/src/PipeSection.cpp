#include "PCH.h"
#include "PipeSection.h"


PipeSection::PipeSection()
	: number(0), type('0'), diameter(0.0), rho(0.0), EA(0.0), EI(0.0), GJ(0.0), 
	GA(0.0), CDt(0.0), CDn(0.0), CAt(0.0), CAn(0.0), E(0.0), nu(0.0)	
{}

PipeSection::PipeSection(const unsigned int& num, const char& tp, const double& d, const double& r, const double& ea, const double& ei, const double& gj, const double& ga, const double& cdt, const double& cdn, const double& cat, const double& can, const double& young, const double& poisson)
	: number(num), type(tp), diameter(d), rho(r), EA(ea), EI(ei), GJ(gj),
	GA(ga), CDt(cdt), CDn(cdn), CAt(cat), CAn(can), E(young), nu(poisson)
{}

PipeSection::~PipeSection()
{}

//Writes Giraffe file data
void PipeSection::WriteGiraffeModelFile(FILE *f)
{
	fprintf(f, "\tPS\t%d\tEA\t%.6e\tEI\t%.6e\tGJ\t%.6e\tGA\t%.6e\tRho\t%.6e\tCDt\t%.6e\tCDn\t%.6e\tCAt\t%.6e\tCAn\t%.6e\tDe\t%.6e\tDi\t%.6e\n", 
		number, EA, EI, GJ, GA, rho, CDt, CDn, CAt, CAn, diameter, 0.0);
}