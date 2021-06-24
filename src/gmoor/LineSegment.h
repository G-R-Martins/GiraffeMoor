#pragma once

class LineSegment
{
	//Segment lenth
	double length;

	//Property ID
	unsigned int property;

	//Number of divisions
	unsigned int discretization;
	
	//Number of nodes
	unsigned int n_nodes;
	unsigned int n_elements;

	//============================================================================

public:
	LineSegment();
	LineSegment(LineSegment&& other) noexcept;
	LineSegment(const LineSegment&) = default;
	~LineSegment();


	//Reads input file
	bool Read(FILE *f);


	//Set functions
	void SetLength(double len);
	void SetProperty(unsigned int prop);
	void SetDiscretization(unsigned int disc);
	void SetNNodes(unsigned int nodes);
	void SetNElements(unsigned int elements);
	
	//Get functions
	double GetLength() const;
	unsigned int GetProperty() const;
	unsigned int GetDiscretization() const;
	unsigned int GetNNodes() const;
	unsigned int GetNElements() const;


	//============================================================================

	//Overloaded operators
	LineSegment& operator=(LineSegment&& other) noexcept;
	LineSegment& operator=(const LineSegment& other) = default;
};