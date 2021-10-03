#pragma once

class Keypoint
{
	//Keypoint ID
	size_t m_number;

	//Coordinates
	double m_x;
	double m_y;
	double m_z;

	//============================================================================

public:
	Keypoint();
	Keypoint(double x, double y, double z, unsigned int ID=0);
	~Keypoint();


	/// 
	/// SETTERS
	/// 
	
	void SetIDNumber(size_t number);
	void SetX(double x);
	void SetY(double y);
	void SetZ(double z);


	/// 
	/// GETTERS
	/// 
	
	inline const size_t GetIDNumber() const							{ return this->m_number; }
	inline const std::array<double, 3> GetAllCoordinates() const	{ return std::array{ m_x, m_y, m_z }; }
	const double GetCoordinate(char coordinate) const;


	//============================================================================


	//Overloaded operators
	friend bool operator< (const Keypoint& obj1, const Keypoint& obj2);
	friend bool operator> (const Keypoint& obj1, const Keypoint& obj2);
	friend bool operator== (const Keypoint& obj1, const Keypoint& obj2);
	friend bool operator!= (const Keypoint& obj1, const Keypoint& obj2);

};

