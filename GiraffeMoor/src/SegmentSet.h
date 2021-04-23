#pragma once
#include "LineSegment.h"


class SegmentSet
{
private:

	// Set ID number
	unsigned int ID;

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
	size_t& SegmentSetSize();

	//Get a segment from the set
	LineSegment& GetSegment(const size_t& seg);


	//============================================================================

	/*------------------
	Overloaded operators
	-------------------*/

	friend bool operator<(const SegmentSet& segset1, const SegmentSet& segset2);
	friend bool operator>(const SegmentSet& segset1, const SegmentSet& segset2);
	friend bool operator==(const SegmentSet& segset1, const SegmentSet& segset2);
	friend bool operator!=(const SegmentSet& segset1, const SegmentSet& segset2);
	////Move
	//SegmentSet& operator=(SegmentSet&& other) noexcept = default;
	////Copy assignment
	//SegmentSet& operator=(const SegmentSet& other) = default;


};

