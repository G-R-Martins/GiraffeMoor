#include "PCH.h"
#include "Pipe.h"


Pipe::Pipe()
{
	nodes.resize(3);
}


Pipe::~Pipe()
{}

void Pipe::WriteGiraffeModelFile(std::ostream& fout) const
{
	if ( mark_segment_begin )
		fout << "\t//Segment begin\n";
	else if ( !label.empty() )
		fout << "\t//" << label << "\n";
	fout << "\tPipe_1 " << number <<
		"\tPipeSec " << section <<
		"\tCS " << cs <<
		"\tNodes " << nodes[0] << " " << nodes[1] << " " << nodes[2] <<
		"\n";
}
