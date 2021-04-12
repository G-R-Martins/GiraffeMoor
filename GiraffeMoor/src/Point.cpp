#include "PCH.h"
#include "Point.h"


Point::Point()
	: number(0), coordinates(Matrix(3))
{	//coordinates = Matrix(3);
}


Point::~Point()
{
}

void Point::WriteGiraffeModelFile(FILE *f)
{
	fprintf(f, "\tPoint\t%d\t%.6e\t%.6e\t%.6e\n", number, coordinates(0, 0), coordinates(1, 0), coordinates(2, 0));
}
