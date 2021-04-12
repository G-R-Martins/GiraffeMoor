#include "PCH.h"
#include "NSSS.h"


NSSS::NSSS()
{
	number = 0;
	node_set = 0;
	surface_set = 0;
	mu = 0;
	epn = 0;
	cn = 0;
	ept = 0;
	ct = 0;
	pinball = 0;
	radius = 0;
	max_interactions = 0;
	bool_table.Clear();
}

NSSS::~NSSS()
{
	bool_table.Clear();
}
void NSSS::WriteGiraffeModelFile(FILE *f)
{
	fprintf(f, "\tNSSS\t%d\tNodeSet\t%d\tSurfaceSet\t%d\tMU\t%.6e\tEPN\t%.6e\tCN\t%.6e\tEPT\t%.6e\tCT\t%.6e\tPinball\t%.6e\tRadius\t%.6e\tMaxPointwiseInt\t%d\t",
		number, node_set, surface_set, mu, epn, cn, ept, ct, pinball, radius, max_interactions);
	bool_table.Write(f);
}