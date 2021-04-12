#pragma once


class OscillatorySurf
{
public:

	/*-------
	Functions
	--------*/

	OscillatorySurf();
	~OscillatorySurf();

	void WriteGiraffeModelFile(FILE *f) const;

	//============================================================================

	/*--------
	Parameters
	---------*/

	unsigned int number;
	double A1;
	double A2;
	double A12;
	double lambda1;
	double lambda2;
	double phi1;
	double phi2;
	double waves1;
	double waves2;
	unsigned int cs;
	unsigned int pilot_node;
};
