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


	/// 
	/// SETTERS
	/// 
	
	void SetIDNumber(size_t id);
	

	/// 
	/// GETTERS
	/// 
	
	inline size_t GetIDNumber() const { return this->ID; };
	inline LineSegment& GetLastSegment() { return this->segments.back(); };
	inline const LineSegment& GetLastSegment() const { return this->segments.back(); };

	//Returns the number of 'LineSegment' in the set
	const size_t& GetSegmentSetSize() const;

	//Get the container with segments of the set
	const std::vector<LineSegment>& GetAllSegment() const;
	std::vector<LineSegment>& GetAllSegment();
		
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

