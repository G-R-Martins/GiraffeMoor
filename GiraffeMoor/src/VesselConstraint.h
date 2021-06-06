#pragma once
#include "MoorConstraint.h"


class VesselConstraint// : public MoorConstraint
{
public:
	VesselConstraint();
	~VesselConstraint();

	//==========================================================================================================================

					/*--------
					|Functions|
					---------*/

	//Reads input file
	bool Read(FILE *f);

	/*-----------
	Get functions
	-----------*/

	unsigned int GetVesselID() const;
	
	unsigned int GetSizeX();
	unsigned int GetSizeY();
	unsigned int GetSizeZ();
	unsigned int GetSizeRotX();
	unsigned int GetSizeRotY();
	unsigned int GetSizeRotZ();

//private:

	//==========================================================================================================================

					/*--------
					|Variables|
					---------*/

	//Vessel constraint ID number
	unsigned int number; 
	
	//General container
	std::vector	<std::list <bool>> constraints;

	//==========================================================================================================================

	/*------------------
	Overloaded operators
	-------------------*/

	friend bool operator< (const VesselConstraint& vessel1, const VesselConstraint& vessel2);
	friend bool operator> (const VesselConstraint& vessel1, const VesselConstraint& vessel2);
	friend bool operator== (const VesselConstraint& vessel1, const VesselConstraint& vessel2);
	friend bool operator!= (const VesselConstraint& vessel1, const VesselConstraint& vessel2);
};

