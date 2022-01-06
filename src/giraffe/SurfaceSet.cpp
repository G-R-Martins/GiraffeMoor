#include "PCH.h"
#include "SurfaceSet.h"


SurfaceSet::SurfaceSet()
	: m_id(0)
{}

SurfaceSet::SurfaceSet(unsigned int id, const std::vector<unsigned int>& surfaces)
	: m_id(id), m_surfaces(surfaces)
{}


SurfaceSet::~SurfaceSet()
{}



/// 
/// Overloaded operators
/// 

std::ostream& operator<<(std::ostream& out, const SurfaceSet& obj)
{
	out << "\tSurfaceSet " << obj.m_id
		<< "\tSurfaces " << obj.m_surfaces.size() 
		<< "\tList ";
	for (size_t i = 0; i < obj.m_surfaces.size(); ++i)
		out << i + 1 << " ";
	out << "\n";

	return out;
}
