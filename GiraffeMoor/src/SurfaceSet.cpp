#include "PCH.h"
#include "SurfaceSet.h"


SurfaceSet::SurfaceSet()
	: number(0)
{}


SurfaceSet::~SurfaceSet()
{}

void SurfaceSet::WriteGiraffeModelFile(FILE *f) const
{
	fprintf(f, "\tSurfaceSet\t%d\tSurfaces\t%d\tList\t", number, (int)surfaces.size());
	for (int i = 0; i < (int)surfaces.size(); i++)
		fprintf(f, "%d\t", i + 1);
	fprintf(f, "\n");
}
