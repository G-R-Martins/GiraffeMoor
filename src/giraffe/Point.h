#pragma once


class Point
{
	//Point ID
	unsigned int number;

	//Point coordinates
	Matrix coordinates;

	//============================================================================
public:
	Point();
	Point(const unsigned int& n, Matrix& pos);
	~Point();

	//Writes Giraffe file
	void WriteGiraffeModelFile(FILE *f);
};

