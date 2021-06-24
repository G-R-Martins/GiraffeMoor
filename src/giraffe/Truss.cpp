#include "PCH.h"
#include "Truss.h"


Truss::Truss()
{
	nodes.resize(2);
}


Truss::~Truss()
{}

void Truss::WriteGiraffeModelFile(FILE *f)
{
	if (mark_segment_begin)
		fprintf(f, "\t//Segment begin\n");
	else if (!label.empty())
		fprintf(f, "\t//%s\n", label.c_str());
	fprintf(f, "\tTruss_1\t%d\tPipeSec\t%d\tNodes\t%d\t%d\n",
		number,
		section,
		nodes[0],
		nodes[1]);
}