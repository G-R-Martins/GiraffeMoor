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
void NodalForce::WriteGiraffeModelFile(FILE* f)
{
	fprintf(f, "\tNodalLoad\t%d\tNodeSet\t%d\tCS\t%d\t", this->GetNumber(), nodeset, this->GetCoordinateSystem());
	if (this->CheckIfIsMathCode())
	{
		fprintf(f, "MathCode\n");
		mathCode->WriteGiraffeModelFile(f);
	}
	else if (this->CheckIfIsExternalFile())
	{
		fprintf(f, "\n\t\tFile \"%s\"\tHeaderLines %d\tNTimes %d\n", file_name.c_str(), header_lines, n_times);
	}
	else
	{
		fprintf(f, "NTimes\t%d\n", table->GetLines());
		table->Write(f);
	}
}
