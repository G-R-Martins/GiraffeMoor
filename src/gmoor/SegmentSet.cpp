#include "PCH.h"
#include "SegmentSet.h"
#include "LoopReading.h"


//Constructor
SegmentSet::SegmentSet()
	: ID(0), n_segments(0)
{
	segments.reserve(4);
}


/* Overloaded operators */
bool operator<(const SegmentSet& segset1, const SegmentSet& segset2)
{
	return segset1.ID < segset2.ID;
}
bool operator>(const SegmentSet& segset1, const SegmentSet& segset2)
{
	return !( segset1 < segset2 );
}
bool operator==(const SegmentSet& segset1, const SegmentSet& segset2)
{
	return segset1.ID == segset2.ID;
}
bool operator!=(const SegmentSet& segset1, const SegmentSet& segset2)
{
	return !( segset1 == segset2 );
}


//Input file reading 
bool SegmentSet::Read(FILE * f)
{
	//Variables
	fpos_t pos;		//to save current reading position
	char str[100];	//to save readed keywords/variables


	if (fscanf(f, "%s", str) && isdigit(str[0]))
		ID = atoi(str);
	else
	{
		Log::AddWarning("\n   + Error reading a segment set number\n");
		return false;
	}


	//Read segment(s)
	if (!AuxFunctions::Reading::TryNestedKeyword_UnorderedMultiple(segments,
														 std::unordered_set<std::string_view>({ "Length" }),
														 std::unordered_set<std::string_view>({ "Set" }),
														 f, pos, str))
	{
		std::string w = "\n   + Error reading data of the segment set number " + std::to_string(ID);
		Log::AddWarning(w);
		return false;
	}

	//Set the number of segments
	n_segments = segments.size();

	//All ok while reading
	return true;
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
