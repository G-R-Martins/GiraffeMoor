#include "PCH.h"
#include "RigidBody.h"


RigidBody::RigidBody()
{
	nodes.resize(1);
}

RigidBody::~RigidBody()
{
}

void RigidBody::WriteGiraffeModelFile(FILE *f)
{
	if (label.size() > 0)
		fprintf(f, "\t//%s\n", label.c_str());
	fprintf(f, "\tRigidBody_1\t%d\tRigidBodyData\t%d\tCS\t%d\tNode\t%d\n", number, material, cs, nodes[0]);
}
