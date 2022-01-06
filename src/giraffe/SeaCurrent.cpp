#include "PCH.h"
#include "SeaCurrent.h"


SeaCurrent::SeaCurrent()
	: m_depth(0.0), m_speed(0.0), m_azimuth(0.0)
{}

SeaCurrent::SeaCurrent(double depth, double speed, double azimuth)
	: m_depth(depth), m_speed(speed), m_azimuth(azimuth)
{}


SeaCurrent::~SeaCurrent()
{}



/// 
/// SETTERS
/// 

void SeaCurrent::SetDepth(double depth)
{
	m_depth = depth;
}
void SeaCurrent::SetSpeed(double speed)
{
	m_speed = speed;
}
void SeaCurrent::SetAzimuth(double azimuth)
{
	m_azimuth = azimuth;
}

