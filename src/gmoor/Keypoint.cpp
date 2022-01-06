#include "PCH.h"
#include "Keypoint.h"


Keypoint::Keypoint()
	: m_id(0), m_x(0.0), m_y(0.0), m_z(0.0)
{}

Keypoint::Keypoint(double x, double y, double z, unsigned int id)
	: m_id(id), m_x(x), m_y(y), m_z(z)
{}

Keypoint::~Keypoint()
{}


/// 
/// SETTERS
/// 
void Keypoint::SetIDNumber(unsigned int id)
{
	this->m_id = id;
}

void Keypoint::SetX(double x)
{
	this->m_x = x;
}
void Keypoint::SetY(double y)
{
	this->m_y = y;
}
void Keypoint::SetZ(double z)
{
	this->m_z = z;
}


/// 
/// GETTERS
/// 

const double Keypoint::GetCoordinate(char coordinate) const
{
	switch (coordinate)
	{
	case 'x':
		return this->m_x;
	case 'y':
		return this->m_y;
	case 'z':
		return this->m_z;
	default:
		std::cerr << "Invalid direction to define anchor rotation constraint. It must 'x', 'y' or 'z'";
		std::exit( EXIT_FAILURE );
	}
}


/*-------------------
 Overloaded operators
 -------------------*/
bool operator<(const Keypoint& obj1, const Keypoint& obj2)
{
	return obj1.m_id < obj2.m_id;
}
bool operator>(const Keypoint& obj1, const Keypoint& obj2)
{
	return !(obj1 < obj2);
}

bool operator==(const Keypoint& obj1, const Keypoint& obj2)
{
	return obj1.m_id == obj2.m_id;
}
bool operator!=(const Keypoint& obj1, const Keypoint& obj2)
{
	return !(obj1 == obj2);
}
