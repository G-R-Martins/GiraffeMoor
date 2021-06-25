#include "PCH.h"
#include "SameDisplacement.h"


SameDisplacement::SameDisplacement()
	: node_A(0), node_B(0), initial_load_step(0)
{}

SameDisplacement::~SameDisplacement()
{
	bool_table.Clear();
}

void SameDisplacement::WriteGiraffeModelFile(std::ostream& fout) const
{
	fout << "\tSameDisplacement " << number <<
		"\tNodes " << node_A << " " << node_B << " " << bool_table;
}
