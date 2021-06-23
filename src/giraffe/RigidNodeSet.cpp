#include "PCH.h"
#include "RigidNodeSet.h"


RigidNodeSet::RigidNodeSet()
	: pilot_node(0), node_set(0), comment("")
{}


RigidNodeSet::~RigidNodeSet()
{
	bool_table.Clear();
}

void RigidNodeSet::WriteGiraffeModelFile(FILE *f)
{
	if (!comment.empty())
		fprintf(f, "\t//%s\n", comment.c_str());
	fprintf(f, "\tRigidNodeSet\t%d\tPilotNode\t%d\tNodeSet\t%d\t", number, pilot_node, node_set);
	bool_table.Write(f);
}
