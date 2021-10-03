#include "PCH.h"
#include "NSSS.h"


NSSS::NSSS()
	: number(0), node_set(0), surface_set(0), mu(0), epn(0), cn(0), ept(0), ct(0), 
	pinball(0), radius(0), max_interactions(0), comment("\0")
{
	bool_table.Clear();
}

NSSS::~NSSS()
{
	bool_table.Clear();
}
void NSSS::WriteGiraffeModelFile(std::ostream& fout) const
{
	if ( !comment.empty() )
		fout << "//" << comment << "\n";
	
	fout << "\tNSSS " << number <<
		"\tNodeSet " << node_set <<
		"\tSurfaceSet " << surface_set <<
		"\tMU " << mu <<
		"\tEPN " << epn <<
		"\tCN " << cn <<
		"\tEPT " << ept <<
		"\tCT " << ct <<
		"\tPinball " << pinball <<
		"\tRadius " << radius <<
		"\tMaxPointwiseInt " << max_interactions << 
		" " << bool_table;
}