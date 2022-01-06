#pragma once
#include "LineSegment.h"


class SegmentSet
{
private:

	// Set ID number
	unsigned int m_id;

	// Number of segments
	unsigned int m_tot_segments;

	// Vector with line segments
	std::vector<LineSegment> m_segments;

public:

	//Constructor and destructor
	SegmentSet();
	~SegmentSet() = default;
	

	inline LineSegment* AddSegment();
	inline void PushBackSegment();

	/// 
	/// SETTERS
	/// 
	
	void SetIDNumber(unsigned int id);
	

	/// 
	/// GETTERS
	/// 
	
	inline unsigned int GetIDNumber() const { return this->m_id; };
	inline LineSegment& GetLastSegment() { return this->m_segments.back(); };
	inline const LineSegment& GetLastSegment() const { return this->m_segments.back(); };

	//Returns the number of 'LineSegment' in the set
	inline const unsigned int GetSegmentSetSize() const { return (unsigned int)this->m_segments.size(); };

	//Get the container with segments of the set
	inline const std::vector<LineSegment>& GetAllSegment() const { return this->m_segments; };
	inline std::vector<LineSegment>& GetAllSegment() { return this->m_segments; }
		
	//Get a specific segment from the set
	inline LineSegment& GetSegment(const unsigned int& seg) { return this->m_segments[seg]; };


	
	/// 
	/// Overloaded operators
	/// 

	friend bool operator<(const SegmentSet& segset1, const SegmentSet& segset2);
	friend bool operator>(const SegmentSet& segset1, const SegmentSet& segset2);
	friend bool operator==(const SegmentSet& segset1, const SegmentSet& segset2);
	friend bool operator!=(const SegmentSet& segset1, const SegmentSet& segset2);
};



LineSegment* SegmentSet::AddSegment()
{
	return &this->m_segments.emplace_back();
}
void SegmentSet::PushBackSegment()
{
	m_segments.emplace_back();
}
