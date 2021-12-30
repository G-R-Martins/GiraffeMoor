#pragma once


class Node
{
private:
	unsigned int m_id;
	std::array<double, 3> m_ref_coordinates;
	std::string m_comment;

public:
	Node();
	Node(unsigned int id, const std::array<double, 3>& m_ref_coordinates, std::string comment = "\0");
	~Node();
	
	
	///
	/// SETTERS
	/// 
	
	void SetIDNumber(unsigned int number);
	void SetCoordinates(const std::array<double, 3>& ref_coordinates);
	void SetComment(std::string comment);
	

	///
	/// GETTERS
	/// 
	
	inline unsigned int GetIDNumber() const							{ return m_id; }
	inline const std::array<double, 3>& GetCoordinates() const	{ return m_ref_coordinates; }
	inline std::array<double, 3>& GetCoordinates()				{ return m_ref_coordinates; }
	inline const std::string& GetComment() const			{ return m_comment; }
	inline std::string& GetComment()						{ return m_comment; }

	

	/// 
	/// Overloaded operators
	/// 

	friend std::ostream& operator<<(std::ostream& out, const Node& obj);

};

