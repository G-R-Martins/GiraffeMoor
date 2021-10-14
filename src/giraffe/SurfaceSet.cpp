#include "PCH.h"
#include "SurfaceSet.h"


SurfaceSet::SurfaceSet()
	: m_number(0)
{}

SurfaceSet::SurfaceSet(size_t n, const std::vector<size_t>& surfaces)
	: m_number(n), m_surfaces(surfaces)
{}


SurfaceSet::~SurfaceSet()
{}



/// 
/// Overloaded operators
/// 

std::ostream& operator<<(std::ostream& out, const SurfaceSet& obj)
{
	out << "\tSurfaceSet " << obj.m_number 
		<< "\tSurfaces " << obj.m_surfaces.size() 
		<< "\tList ";
	for (size_t i = 0; i < obj.m_surfaces.size(); ++i)
		out << i + 1 << " ";
	out << "\n";

	return out;
}
