#pragma once

class LineSegment
{
	double m_length;
	unsigned int m_property_id;  //Property ID
	unsigned int m_discretization;
	unsigned int m_tot_nodes;
	unsigned int m_tot_elements;
	unsigned int m_nodeset_id;  //TODO:  definir o nodeset do segmento
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
	void SetProperty(unsigned int property);
	void SetDiscretization(unsigned int discretization);
	void SetNNodes(unsigned int tot_nodes);
	void SetNElements(unsigned int tot_elements);
	void SetNodeSet(unsigned int nodeset);
	void SetEpsilon(double epsilon);
	void SetGamma(double gamma);


	///
	/// GETTERS
	/// 

	inline double GetLength() const					{ return this->m_length; }
	inline unsigned int GetProperty() const				{ return this->m_property_id; }
	inline unsigned int GetDiscretization() const	{ return this->m_discretization; }
	inline unsigned int GetNNodes() const			{ return this->m_tot_nodes; }
	inline unsigned int GetNElements() const		{ return this->m_tot_elements; }
	inline unsigned int GetNodeSet() const			{ return this->m_nodeset_id; }
	inline double GetEpsilon() const				{ return this->m_epsilon; }
	inline double GetGamma() const					{ return this->m_gamma; }


	//============================================================================

	//Overloaded operators
	LineSegment& operator=(LineSegment&& other) noexcept;
	LineSegment& operator=(const LineSegment& other) = default;
};