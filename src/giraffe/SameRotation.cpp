#include "PCH.h"
#include "SameRotation.h"


SameRotation::SameRotation()
	: node_A(0), node_B(0)
{
}

SameRotation::~SameRotation()
{
	bool_table.Clear();
}

void SameRotation::WriteGiraffeModelFile(FILE *f)
{
	fprintf(f, "\tSameRotation\t%d\tNodes\t%d\t%d\t",
		number,
		node_A,
		node_B);
	bool_table.Write(f);
}