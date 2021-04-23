#include "PCH.h"
#include "Pipe.h"


Pipe::Pipe()
	: label("")
{
	nodes.resize(3);
}


Pipe::~Pipe()
{}

void Pipe::WriteGiraffeModelFile(FILE *f)
{
	if (mark_segment_begin)
		fprintf(f, "\t//Segment begin\n");
	else if (label.size() > 0)
		fprintf(f, "\t//%s\n", label.c_str());
	fprintf(f, "\tPipe_1\t%d\tPipeSec\t%d\tCS\t%d\tNodes\t%d\t%d\t%d\n",
		number,
		section,
		cs,
		nodes[0],
		nodes[1],
		nodes[2]);
}
