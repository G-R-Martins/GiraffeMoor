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
void PipeSection::WriteGiraffeModelFile(std::ostream& fout) const
{
	fout << std::setprecision(6) <<
		"\tPS " << number <<
		"\tEA " << EA <<
		"\tEI " << EI <<
		"\tGJ " << GJ <<
		"\tGA " << GA <<
		"\tRho " << rho <<
		"\tCDt " << CDt <<
		"\tCDn " << CDn <<
		"\tCAt " << CAn <<
		"\tCAn " << CAt <<
		"\tDe " << diameter <<
		"\tDi " << 0.0 <<
		"\n";
}