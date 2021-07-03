#include "PCH.h"
#include "NodalConstraint.h"

NodalConstraint::NodalConstraint()
	: node_set(0)
{}

NodalConstraint::~NodalConstraint()
{}

//Writes output file
void NodalConstraint::WriteGiraffeModelFile(std::ostream& fout) const
{
	fout << "\tNodalConstraint " << number << "\tNodeSet " << node_set << "\n" <<
		"\t\tUX\t\t" << UX_table <<
		"\t\tUY\t\t" << UY_table <<
		"\t\tUZ\t\t" << UZ_table <<
		"\t\tROTX\t" << ROTX_table <<
		"\t\tROTY\t" << ROTY_table <<
		"\t\tROTZ\t" << ROTZ_table;
}
