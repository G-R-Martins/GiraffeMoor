#pragma once

class LineSegment
{
	double m_length;
	size_t m_property;  //Property ID
	unsigned int m_discretization;
	unsigned int m_tot_nodes;
	unsigned int m_tot_elements;
	unsigned int m_nodeset;  //TODO:  definir o nodeset do segmento
 	double m_epsilon;  // Epsilon used to establish contact
	double m_gamma;  // immersed  

public:
	LineSegment();
	LineSegment(LineSegment&& other) noexcept;
	LineSegment(const LineSegment&) = default;
	~LineSegment();

	
	///
	/// SETTERS
	/// 

	void SetLength(double length);
	void SetProperty(size_t property);
	void SetDiscretization(unsigned int discretization);
	void SetNNodes(unsigned int nodes);
	void SetNElements(unsigned int elements);
	void SetNodeSet(unsigned int nodeset);
	void SetEpsilon(double epsilon);
	void SetGamma(double gamma);


	///
	/// GETTERS
	/// 

	inline double GetLength() const					{ return this->m_length; }
	inline size_t GetProperty() const				{ return this->m_property; }
	inline unsigned int GetDiscretization() const	{ return this->m_discretization; }
	inline unsigned int GetNNodes() const			{ return this->m_tot_nodes; }
	inline unsigned int GetNElements() const		{ return this->m_tot_elements; }
	inline unsigned int GetNodeSet() const			{ return this->m_nodeset; }
	inline double GetEpsilon() const				{ return this->m_epsilon; }
	inline double GetGamma() const					{ return this->m_gamma; }


	//============================================================================

	//Overloaded operators
	LineSegment& operator=(LineSegment&& other) noexcept;
	LineSegment& operator=(const LineSegment& other) = default;
};