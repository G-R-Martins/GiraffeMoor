#pragma once

class LineSegment
{
public:
	LineSegment();
	LineSegment(LineSegment&& other) noexcept;
	LineSegment(const LineSegment& other) = default;
	~LineSegment();

	//============================================================================

	//Reads input file
	bool Read(FILE *f);

	//============================================================================

	/*-------
	Variables
	--------*/
	
	//Segment lenth
	double length;

	//Property ID
	unsigned int property;

	//Number of divisions
	unsigned int discretization;
	
	//Number of nodes
	unsigned int n_nodes;		//nodes_segs
	unsigned int n_elements;	//elements_segs;

	//============================================================================

	LineSegment& operator=(LineSegment&& other) noexcept;
	LineSegment& operator=(const LineSegment& other) = default;
};