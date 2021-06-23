#pragma once


class SeaCurrent
{
public:
	SeaCurrent();
	~SeaCurrent();

	//============================================================================

	//Reads GiraffeMoor file
	bool Read(FILE *f);	
	
	//============================================================================
	
	/*-------
	Variables
	--------*/

	//Water depth
	double depth;

	//Sea current speed
	double speed;

	//Sea current azimuth
	double azimuth;
};

