#include "PCH.h"
#include "CoordinateSystem.h"


CoordinateSystem::CoordinateSystem()
	: number(0), E1({0.,0.,0.}), E3({0.,0.,0.})
{}

CoordinateSystem::~CoordinateSystem()
{}

//bool operator==(CoordinateSystem& cs1, CoordinateSystem& cs2)
//{
//	return cs1.number == cs2.number;
//}
//
//bool operator!=(CoordinateSystem& cs1, CoordinateSystem& cs2)
//{
//	return cs1.number != cs2.number;
//}

void CoordinateSystem::WriteGiraffeModelFile(FILE *f)
{
	fprintf(f, "\tCS\t%d\tE1\t%.11e\t%.11e\t%.11e\tE3\t%.11e\t%.11e\t%.11e\n", number, E1[0], E1[1], E1[2], E3[0], E3[1], E3[2]);
}