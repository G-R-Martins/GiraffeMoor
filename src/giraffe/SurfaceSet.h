#pragma once


class SurfaceSet
{
	//Surface set ID
	unsigned int number;

	//Vector with surfaces identifications
	std::vector<unsigned int> surfaces;

	//============================================================================

public:
	SurfaceSet();
	SurfaceSet(unsigned int n, std::vector<unsigned int> surf);
	~SurfaceSet();

	//Writes Giraffe file
	void WriteGiraffeModelFile(FILE *f) const;



};

