#include "PCH.h"
#include "Keypoint.h"
#include "Log.h"


Keypoint::Keypoint()
	: m_number(0), m_x(0.0), m_y(0.0), m_z(0.0)
{}

Keypoint::Keypoint(double x, double y, double z, unsigned int ID)
	: m_number(ID), m_x(x), m_y(y), m_z(z)
{}

Keypoint::~Keypoint()
{}


/// 
/// SETTERS
/// 
void Keypoint::SetIDNumber(size_t number)
{
	this->m_number = number;
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
	return obj1.m_number < obj2.m_number;
}
bool operator>(const Keypoint& obj1, const Keypoint& obj2)
{
	return !(obj1 < obj2);
}

bool operator==(const Keypoint& obj1, const Keypoint& obj2)
{
	return obj1.m_number == obj2.m_number;
}
bool operator!=(const Keypoint& obj1, const Keypoint& obj2)
{
	return !(obj1 == obj2);
}
