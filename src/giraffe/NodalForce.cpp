#include "PCH.h"
#include "NodalForce.h"


NodalForce::NodalForce()
	: table(nullptr), mathCode(nullptr), file_name("\0"), header_lines(0),  n_times(0), nodeset(0)
{}
NodalForce::NodalForce(Table* time_series)
	: table(time_series), mathCode(nullptr), file_name("\0"), header_lines(0), n_times(0), nodeset(0)
{}
NodalForce::NodalForce(MathCode* mc)
	: table(nullptr), mathCode(mc), file_name("\0"), header_lines(0), n_times(0), nodeset(0)
{
	this->DefineMathCodeOption();
}
NodalForce::NodalForce(const std::string& f_name, const unsigned int& h_lines, const unsigned int& ntimes)
	: table(nullptr), mathCode(nullptr),
	file_name(f_name), header_lines(h_lines), n_times(ntimes), nodeset(0)
{
	this->DefineExternalFileOption();
}
NodalForce::NodalForce(std::string_view f_name, const unsigned int& h_lines, const unsigned int& ntimes)
	: table(nullptr), mathCode(nullptr),
	file_name(f_name), header_lines(h_lines), n_times(ntimes), nodeset(0)
{
	this->DefineExternalFileOption();
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
void NodalForce::WriteGiraffeModelFile(std::ostream& fout) const
{
	fout << "\tNodalLoad " << number << 
		"\tNodeSet " << nodeset << 
		"\tCS " << CS << "\t";
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
		fout << "NTimes " << table->GetNLines() << "\n" << table;
	}
}
