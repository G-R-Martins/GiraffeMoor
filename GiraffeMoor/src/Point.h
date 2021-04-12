#pragma once


class Point
{
public:
	Point();
	~Point();

	//Writes Giraffe file
	void WriteGiraffeModelFile(FILE *f);

	//============================================================================

	/*-------
	Variables
	--------*/
	
	//Point ID
	unsigned int number;

	//Point coordinates
	Matrix coordinates;
};

