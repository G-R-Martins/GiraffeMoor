#include "PCH.h"
#include "VesselDisplacement.h"


VesselDisplacement::VesselDisplacement()
	: m_vessel_id(0)
{}

VesselDisplacement::~VesselDisplacement()
{}


void VesselDisplacement::SetVesselID(unsigned int vessel_id)
{
	m_vessel_id = vessel_id;
	SetIDOpt(true);
}




/// 
/// Overloaded operators
/// 

bool operator<(const VesselDisplacement& obj1, const VesselDisplacement& obj2)
{
	return obj1.m_vessel_id < obj2.m_vessel_id;
}

bool operator>(const VesselDisplacement& obj1, const VesselDisplacement& obj2)
{
	return !(obj1 < obj2);
}

bool operator==(const VesselDisplacement& obj1, const VesselDisplacement& obj2)
{
	return obj1.m_vessel_id == obj2.m_vessel_id;
}

bool operator!=(const VesselDisplacement& obj1, const VesselDisplacement& obj2)
{
	return !(obj1 == obj2);
}
