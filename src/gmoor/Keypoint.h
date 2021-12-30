#pragma once

class Keypoint
{
	//Keypoint ID
	unsigned int m_id;

	//Coordinates
	double m_x;
	double m_y;
	double m_z;

	//============================================================================

public:
	Keypoint();
	Keypoint(double x, double y, double z, unsigned int id=0);
	~Keypoint();


	/// 
	/// SETTERS
	/// 
	
	void SetIDNumber(unsigned int number);
	void SetX(double x);
	void SetY(double y);
	void SetZ(double z);


	/// 
	/// GETTERS
	/// 
	
	inline const unsigned int GetIDNumber() const							{ return this->m_id; }
	inline const std::array<double, 3> GetAllCoordinates() const	{ return std::array{ m_x, m_y, m_z }; }
	const double GetCoordinate(char coordinate) const;


	//============================================================================


	//Overloaded operators
	friend bool operator< (const Keypoint& obj1, const Keypoint& obj2);
	friend bool operator> (const Keypoint& obj1, const Keypoint& obj2);
	friend bool operator== (const Keypoint& obj1, const Keypoint& obj2);
	friend bool operator!= (const Keypoint& obj1, const Keypoint& obj2);

};

