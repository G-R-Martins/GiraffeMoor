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

void SameRotation::WriteGiraffeModelFile(std::ostream& fout) const
{
	fout << "\tSameRotation " << number <<
		"\tNodes " << node_A << " " << node_B << " " << bool_table;
}