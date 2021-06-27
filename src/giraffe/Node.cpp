#include "PCH.h"
#include "Node.h"

Node::Node()
	: number(0), mark_comment(false), ref_coordinates({0.,0.,0.}), comment("\0")
{}

Node::~Node()
{}

void Node::WriteGiraffeModelFile(std::ostream& fout) const
{
	if ( mark_comment )
		fout << "\t//" << comment << "\n";

	fout << "\tNode " << number << "\t\t" <<
		ref_coordinates[0] << " \t" << ref_coordinates[1] << " \t" << ref_coordinates[2] <<
		"\n";
}
