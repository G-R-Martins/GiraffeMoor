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

void NodalDisplacement::WriteGiraffeModelFile(std::ostream& fout) const
{
	fout << "\tNodalDisplacement " << number << 
		"\tNodeSet " << node_set << 
		"\tCS " << cs << "\t";
	if (isMathCode)
	{
		fout << "MathCode\n" << mathCode;
	}
	else if (extFile)
	{
		fout << "\n\t\tFile \"" << file_name << "\"" <<
			"\tHeaderLines " << header_lines << 
			"\tNTimes " << n_times << "\n";
	}
	else
	{
		fout << "NTimes " << table->GetLines() << "\n" << table;
	}
}