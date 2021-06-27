#include "PCH.h"
#include "NodeSet.h"


NodeSet::NodeSet()
	: number(0), total_nodes(0), init(0), increment(0), comment("\0")
{}

NodeSet::NodeSet(const unsigned int& num_nodes, const unsigned int& node0, const unsigned int& inc)
	: number(0), total_nodes(num_nodes), init(node0), increment(inc), comment("\0")
{}

NodeSet::~NodeSet()
{}

void NodeSet::WriteGiraffeModelFile(std::ostream& fout) const
{
	fout << "\t//" << comment << "\n";
	if (total_nodes > 0)
	{
		fout << "\tNodeSet " << number <<
			"\tNodes " << total_nodes <<
			"\tSequence Initial " << init <<
			"\tIncrement " << increment;
	}
	else
	{
		fout << "\tNodeSet " << number <<
			"\tNodes " << nodes.size() <<
			"\tList ";
		for (size_t i = 0; i < nodes.size(); ++i)
			fout <<  nodes[i] << " ";
	}
	fout << "\n";
}

bool operator<(const NodeSet& ns1, const NodeSet& ns2)
{
	return ns1.number < ns2.number;
}

bool operator>(const NodeSet& ns1, const NodeSet& ns2)
{
	return !(ns1<ns2);
}

bool operator==(const NodeSet& ns1, const NodeSet& ns2)
{
	return ns1.number == ns2.number;
}

bool operator!=(const NodeSet& ns1, const NodeSet& ns2)
{
	return !(ns1==ns2);
}
