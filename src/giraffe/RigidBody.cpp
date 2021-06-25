#include "PCH.h"
#include "RigidBody.h"


RigidBody::RigidBody()
{
	nodes.resize(1);
}
RigidBody::~RigidBody()
{
}

void RigidBody::WriteGiraffeModelFile(std::ostream& fout) const
{
	if ( !label.empty() )
		fout << "\t//" << label << "\n";
	fout << "\tRigidBody_1 " << number <<
		"\tRigidBodyData " << material <<
		"\tCS " << cs << "\tNode " << nodes[0] <<
		"\n";
}
