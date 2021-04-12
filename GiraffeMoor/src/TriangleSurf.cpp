#include "PCH.h"
#include "TriangleSurf.h"


TriangleSurf::TriangleSurf()
	: number(0), pilot_node(0)
{}

TriangleSurf::~TriangleSurf()
{}

void TriangleSurf::WriteGiraffeModelFile(FILE *f) const
{
	fprintf(f, "\tRigidTriangularSurface_1\t%d\tPoints\t%d\t%d\t%d\tPilotNode\t%d\n", number, points[0], points[1], points[2], pilot_node);
}
