#include "PCH.h"
#include "NodalForce.h"


NodalForce::NodalForce()
	: table(nullptr), mathCode(nullptr), nodeset(0)
{}

NodalForce::NodalForce(Table* time_series)
	: table(time_series), mathCode(nullptr), nodeset(0)
{}

NodalForce::NodalForce(MathCode* mc)
	: table(nullptr), mathCode(mc), nodeset(0)
{
	isMathCode = true;
}

NodalForce::~NodalForce()
{
	if (table)
	{
		table->table.clear();
		table = nullptr;
	}

	if (mathCode) 
		delete mathCode;
}

//Writes Giraffe input file
void NodalForce::WriteGiraffeModelFile(FILE* f)
{
	fprintf(f, "\tNodalLoad\t%d\tNodeSet\t%d\tCS\t%d\t", number, nodeset, CS);
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
