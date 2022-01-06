#include "PCH.h"
#include "SegmentSet.h"


//Constructor
SegmentSet::SegmentSet()
	: m_id(0), m_tot_segments(0)
{
	m_segments.reserve(4);
}



/// 
/// SETTERS
/// 

void SegmentSet::SetIDNumber(unsigned int id)
{
	this->m_id = id;
}




/// 
/// Overloaded operators
///

bool operator<(const SegmentSet& segset1, const SegmentSet& segset2)
{
	return segset1.m_id < segset2.m_id;
}
bool operator>(const SegmentSet& segset1, const SegmentSet& segset2)
{
	return !(segset1 < segset2);
}
bool operator==(const SegmentSet& segset1, const SegmentSet& segset2)
{
	return segset1.m_id == segset2.m_id;
}
bool operator!=(const SegmentSet& segset1, const SegmentSet& segset2)
{
	return !(segset1 == segset2);
}

