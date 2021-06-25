#include "PCH.h"
#include "Truss.h"


Truss::Truss()
{
	nodes.resize(2);
}


Truss::~Truss()
{}

void Truss::WriteGiraffeModelFile(std::ostream& fout) const
{
	if (mark_segment_begin)
		fout << "\t//Segment begin\n";
	else if (!label.empty())
		fout << "\t//" << label << "\n";
	fout << "\tTruss_1 " << number <<
		"\tPipeSec " << section <<
		"\tNodes " << nodes[0] << " "<< nodes[1] <<
		"\n";
}