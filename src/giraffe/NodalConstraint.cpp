#include "PCH.h"
#include "NodalConstraint.h"

NodalConstraint::NodalConstraint()
	: node_set(0)
{}

NodalConstraint::~NodalConstraint()
{}

//Writes output file
void NodalConstraint::WriteGiraffeModelFile(FILE *f)
{
	fprintf(f, "\tNodalConstraint\t%d\tNodeSet\t%d\n", number, node_set);
	fprintf(f, "\t\tUX\t\t");
	UX_table.Write(f);
	fprintf(f, "\t\tUY\t\t");
	UY_table.Write(f);
	fprintf(f, "\t\tUZ\t\t");
	UZ_table.Write(f);
	fprintf(f, "\t\tROTX\t");
	ROTX_table.Write(f);
	fprintf(f, "\t\tROTY\t");
	ROTY_table.Write(f);
	fprintf(f, "\t\tROTZ\t");
	ROTZ_table.Write(f);
}
