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

void NodeSet::WriteGiraffeModelFile(FILE *f)
{
	fprintf(f, "\t//");
	fprintf(f, comment);
	fprintf(f, "\n");
	if (total_nodes > 0)
	{
		fprintf(f, "\tNodeSet\t%d\tNodes\t%d\tSequence Initial\t%d\tIncrement\t%d", number, total_nodes, init, increment);
	}
	else
	{
		fprintf(f, "\tNodeSet\t%d\tNodes\t%d\tList\t", number, (int)nodes.size());
		for (int i = 0; i < (int)nodes.size(); i++)
			fprintf(f, "%d ", nodes[i]);
	}
	fprintf(f, "\n");
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
