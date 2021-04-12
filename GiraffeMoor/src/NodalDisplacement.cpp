#include "PCH.h"
#include "NodalDisplacement.h"


NodalDisplacement::NodalDisplacement()
	: node_set(0), cs(0), n_values(6), table(nullptr), mathCode(nullptr)
{}	

NodalDisplacement::NodalDisplacement(Table* tbl)
	: node_set(0), cs(0), n_values(6), table(tbl), mathCode(nullptr)
{}

NodalDisplacement::NodalDisplacement(MathCode* mc)
	: node_set(0), cs(0), n_values(6), table(nullptr), mathCode(mc)
{
	isMathCode = true;
}

NodalDisplacement::~NodalDisplacement()
{}

void  NodalDisplacement::WriteGiraffeModelFile(FILE *f)
{
	fprintf(f, "\tNodalDisplacement\t%d\tNodeSet\t%d\tCS\t%d\t", number, node_set, cs);
	if (isMathCode)
	{
		fprintf(f, "MathCode\n");
		mathCode->WriteGiraffeModelFile(f);
	}
	else
	{
		fprintf(f, "NTimes\t%d\n", table->GetLines());
		table->Write(f);
	}
}