#pragma once


class VesselConstraint
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

	unsigned int GetNumberID() const;
	
	unsigned int GetSizeX(), GetSizeY(), GetSizeZ();
	unsigned int GetSizeRotX(), GetSizeRotY(), GetSizeRotZ();

	const std::list<bool>& GetDoFConstraints(const size_t& dof);

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

