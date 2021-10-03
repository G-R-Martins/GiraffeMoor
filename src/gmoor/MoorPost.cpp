#include "PCH.h"
#include "MoorPost.h"


MoorPost::MoorPost()
	: m_writing_flags{ true, /* by default, only mesh_flag is true*/
		false, false, false, false, false, false, false, false, false}
{}

MoorPost::~MoorPost()
{}


void MoorPost::AddPlatformCAD(const CADData & cad)
{
	m_platform_cads.emplace_back();
}

