#pragma once


class VesselConstraint
{
	//Vessel constraint ID number
	unsigned int number; 

	//General container
	std::vector	<std::list <bool>> constraints;

	//==========================================================================================================================

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

	unsigned int GetNumberID() const;
	
	unsigned int GetSizeX(), GetSizeY(), GetSizeZ();
	unsigned int GetSizeRotX(), GetSizeRotY(), GetSizeRotZ();

	std::list<bool>const & GetDoFConstraints(const size_t& dof);


	//==========================================================================================================================
	/*------------------
	Overloaded operators
	-------------------*/

	friend bool operator< (const VesselConstraint& vessel1, const VesselConstraint& vessel2);
	friend bool operator> (const VesselConstraint& vessel1, const VesselConstraint& vessel2);
	friend bool operator== (const VesselConstraint& vessel1, const VesselConstraint& vessel2);
	friend bool operator!= (const VesselConstraint& vessel1, const VesselConstraint& vessel2);
};

