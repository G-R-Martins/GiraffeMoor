#include "PCH.h"
#include "CoordinateSystem.h"


CoordinateSystem::CoordinateSystem()
	: number(0), E1({0.,0.,0.}), E3({0.,0.,0.})
{}
CoordinateSystem::CoordinateSystem(unsigned int ID, const std::array<double,3>& e1, const std::array<double,3>& e3)
	: number(ID), E1(e1), E3(e3)
{}

CoordinateSystem::~CoordinateSystem()
{}


void CoordinateSystem::WriteGiraffeModelFile(std::ostream& fout) const
{
	fout << "\tCS " << number <<
		std::setprecision(11) << 
		"\tE1 " << E1[0] << " " << E1[1] << " " << E1[2] <<
		"\tE3 " << E3[0] << " " << E3[1] << " " << E3[2] <<
		std::setprecision(6) << 
		"\n";
}


//Set functions
void CoordinateSystem::SetCSID(unsigned int ID)
{ this->number = ID; }

void CoordinateSystem::SetE1(const std::array<double, 3>& coordinates)
{ this->E1 = coordinates; }

void CoordinateSystem::SetE3(const std::array<double, 3>& coordinates)
{ this->E3 = coordinates; }

void CoordinateSystem::SetCoordinateSystem(const std::array<double, 3>& e1, const std::array<double, 3>& e3)
{ this->E1 = e1; this->E3 = e3; }


//Get functions
unsigned int CoordinateSystem::GetCSID()
{ return this->number; }

double CoordinateSystem::GetCoordinate(size_t versor_number, size_t coordinate)
{
	if ( versor_number == 1 )
		return this->E1[coordinate];
	else
		return this->E3[coordinate];
}

std::array<double, 3> const& CoordinateSystem::GetVersor(size_t versor_number)
{
	if ( versor_number == 1 )
		return this->E1;
	else
		return this->E3;
}
