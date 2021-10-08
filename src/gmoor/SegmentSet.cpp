#include "PCH.h"
#include "SegmentSet.h"


//Constructor
SegmentSet::SegmentSet()
	: ID(0), n_segments(0)
{
	segments.reserve(4);
}



/// 
/// SETTERS
/// 

void SegmentSet::SetIDNumber(size_t id)
{
	this->ID = id;
}

//Returns the number of 'LineSegment's in the set
const size_t& SegmentSet::GetSegmentSetSize() const
{
	return this->n_segments;
}


const std::vector<LineSegment>& SegmentSet::GetAllSegment() const
{
	return this->segments;
}
std::vector<LineSegment>& SegmentSet::GetAllSegment()
{
	return this->segments;
}

LineSegment& SegmentSet::GetSegment(const size_t& seg)
{
	return this->segments[seg];
}



/// 
/// Overloaded operators
///

bool operator<(const SegmentSet& segset1, const SegmentSet& segset2)
{
	return segset1.ID < segset2.ID;
}
bool operator>(const SegmentSet& segset1, const SegmentSet& segset2)
{
	return !(segset1 < segset2);
}
bool operator==(const SegmentSet& segset1, const SegmentSet& segset2)
{
	return segset1.ID == segset2.ID;
}
bool operator!=(const SegmentSet& segset1, const SegmentSet& segset2)
{
	return !(segset1 == segset2);
}

