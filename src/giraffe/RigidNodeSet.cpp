#include "PCH.h"
#include "RigidNodeSet.h"


RigidNodeSet::RigidNodeSet()
	: pilot_node(0), node_set(0), comment("")
{}


RigidNodeSet::~RigidNodeSet()
{
	bool_table.Clear();
}

void RigidNodeSet::WriteGiraffeModelFile(std::ostream& fout) const
{
	if ( !comment.empty() )
		fout << "\t//" << comment << "\n";
	fout << "\tRigidNodeSet " << number <<
		"\tPilotNode " << pilot_node <<
		"\tNodeSet " << node_set << " " << bool_table;
}
