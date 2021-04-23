#include "PCH.h"
#include "SameDisplacement.h"


SameDisplacement::SameDisplacement()
	: node_A(0), node_B(0), initial_load_step(0)
{}

SameDisplacement::~SameDisplacement()
{
	bool_table.Clear();
}

void SameDisplacement::WriteGiraffeModelFile(FILE *f)
{
	fprintf(f, "\tSameDisplacement\t%d\tNodes\t%d\t%d\t",
		number,
		node_A,
		node_B);
	bool_table.Write(f);
}
