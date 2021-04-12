#include "PCH.h"
#include "Node.h"

Node::Node()
	: number(0), mark_comment(false), ref_coordinates({0.,0.,0.}), comment("\0")
{
	//ref_coordinates.resize(3);
	//number = 0;
	//mark_comment = false;
}

Node::~Node()
{}

void Node::WriteGiraffeModelFile(FILE *f)
{
	if (mark_comment)
	{
		fprintf(f, "\t//%s\n", comment);
	}

	fprintf(f, "\tNode\t%d\t%.14e\t%.14e\t%.14e\n", number,
		ref_coordinates[0],
		ref_coordinates[1],
		ref_coordinates[2]);
}
