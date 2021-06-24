#pragma once
#include "LineSegment.h"


class SegmentSet
{
private:

	// Set ID number
	size_t ID;

	// Number of segments
	size_t n_segments;

	// Vector with line segments
	std::vector<LineSegment> segments;

public:

	//Constructor and destructor
	SegmentSet();
	~SegmentSet() = default;
	

	//Read input file
	bool Read(FILE* f);

	//Returns the number of 'LineSegment's in the set
	const size_t& GetSegmentSetSize() const;

	const size_t& GetSetID() const;

	//Get the container with segments of the set
	const std::vector<LineSegment>& GetAllSegment() const;
		
	//Get a specific segment from the set
	LineSegment& GetSegment(const size_t& seg);


	//============================================================================

	/*------------------
	Overloaded operators
	-------------------*/

	friend bool operator<(const SegmentSet& segset1, const SegmentSet& segset2);
	friend bool operator>(const SegmentSet& segset1, const SegmentSet& segset2);
	friend bool operator==(const SegmentSet& segset1, const SegmentSet& segset2);
	friend bool operator!=(const SegmentSet& segset1, const SegmentSet& segset2);
};

