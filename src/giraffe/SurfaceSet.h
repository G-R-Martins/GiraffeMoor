#pragma once


class SurfaceSet
{
public:
	SurfaceSet();
	~SurfaceSet();

	//Writes Giraffe file
	void WriteGiraffeModelFile(FILE *f) const;
	
	//============================================================================

	/*-------
	Variables
	--------*/

	//Surface set ID
	unsigned int number;

	//Vector with surfaces identifications
	std::vector <unsigned int> surfaces;
};

