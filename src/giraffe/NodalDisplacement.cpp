#include "PCH.h"
#include "NodalDisplacement.h"


NodalDisplacement::NodalDisplacement()
	: node_set(0), cs(0), n_values(6), 
	table(nullptr), mathCode(nullptr), file_name("\0"), header_lines(0), n_times(0)
{}	

NodalDisplacement::NodalDisplacement(Table* tbl)
	: node_set(0), cs(0), n_values(6), 
	table(tbl), mathCode(nullptr), file_name("\0"), header_lines(0), n_times(0)
{}
NodalDisplacement::NodalDisplacement(MathCode* mc)
	: node_set(0), cs(0), n_values(6), 
	table(nullptr), mathCode(mc), file_name("\0"), header_lines(0), n_times(0)
{
	isMathCode = true;
}
NodalDisplacement::NodalDisplacement(const std::string& f_name, const unsigned int& h_lines, const unsigned int& ntimes)
	: node_set(0), cs(0), n_values(6), 
	table(nullptr), mathCode(nullptr), file_name(f_name), header_lines(h_lines), n_times(ntimes)
{
	extFile = true;
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
	else if (extFile)
	{
		fprintf(f, "\n\t\tFile \"%s\"\tHeaderLines %d\tNTimes %d\n", file_name.c_str(), header_lines, n_times);
	}
	else
	{
		fprintf(f, "NTimes\t%d\n", table->GetLines());
		table->Write(f);
	}
}