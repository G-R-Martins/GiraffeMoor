#include "PCH.h"
#include "MoorPost.h"


MoorPost::MoorPost()
	: m_writing_flags{ true, /* by default, only mesh_flag is true*/
		false, false, false, false, false, false, false, false, false}
{}

MoorPost::~MoorPost()
{}



CADData* MoorPost::AddVesselCAD()
{
	return &this->m_vessel_cads.emplace_back();
}
void MoorPost::PushBackVesselCAD()
{
	this->m_vessel_cads.emplace_back();
}