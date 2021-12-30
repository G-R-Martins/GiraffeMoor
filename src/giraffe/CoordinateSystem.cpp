#include "PCH.h"
#include "CoordinateSystem.h"


CoordinateSystem::CoordinateSystem()
	: m_id(0), m_E1({0.,0.,0.}), m_E3({0.,0.,0.})
{}
CoordinateSystem::CoordinateSystem(unsigned int id, const std::array<double,3>& E1, const std::array<double,3>& E3)
	: m_id(id), m_E1(E1), m_E3(E3)
{}

CoordinateSystem::~CoordinateSystem()
{}



/// 
/// SETTERS
/// 

void CoordinateSystem::SetIDNumber(unsigned int id)
{
	m_id = id;
}

void CoordinateSystem::SetE1(const std::array<double, 3>& coordinates)
{
	m_E1 = coordinates;
}

void CoordinateSystem::SetE3(const std::array<double, 3>& coordinates)
{
	m_E3 = coordinates;
}

void CoordinateSystem::SetVersor(const std::array<double, 3>& E1, const std::array<double, 3>& E3)
{
	m_E1 = E1;
	m_E3 = E3;
}



/// 
/// Overloaded operators
/// 

std::ostream& operator<<(std::ostream& out, const CoordinateSystem& obj)
{
	out << "\tCS " << obj.m_id
		<< std::setprecision(11) 
		<< "\tE1 " << obj.m_E1[0] << " " << obj.m_E1[1] << " " << obj.m_E1[2] 
		<< "\tE3 " << obj.m_E3[0] << " " << obj.m_E3[1] << " " << obj.m_E3[2] <<
		std::setprecision(8) << 
		"\n";

	return out;
}



