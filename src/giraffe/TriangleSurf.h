#pragma once


class TriangleSurf
{
public:
	TriangleSurf();
	~TriangleSurf();

	//Writes Giraffe file
	void WriteGiraffeModelFile(FILE *f) const;
	
	
	unsigned int points[3] = { 0, 0, 0 };
	unsigned int number;
	unsigned int pilot_node;
};

