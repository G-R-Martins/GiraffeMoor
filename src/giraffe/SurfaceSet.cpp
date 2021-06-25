#include "PCH.h"
#include "SurfaceSet.h"


SurfaceSet::SurfaceSet()
	: number(0)
{}

SurfaceSet::SurfaceSet(unsigned int n, std::vector<unsigned int> surf)
	: number(n), surfaces(surf)
{}


SurfaceSet::~SurfaceSet()
{}

void SurfaceSet::WriteGiraffeModelFile(std::ostream& fout) const
{
	fout << "\tSurfaceSet " << number << "\tSurfaces " << surfaces.size() << "\tList ";
	for ( size_t i = 0; i < surfaces.size(); ++i )
		fout << i + 1 << " ";
	fout << "\n";
}
