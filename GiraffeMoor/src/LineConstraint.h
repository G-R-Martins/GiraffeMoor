#pragma once


class LineConstraint
{
private:

		/*--------
		|Variables|
		---------*/

	//Vessel constraint ID number
	unsigned int number; 

	//General container
	std::vector	<std::vector <bool>> constraints;

public:
	LineConstraint();
	~LineConstraint();

	//==========================================================================================================================

		/*--------
		|Functions|
		---------*/

	//Reads input file
	bool Read(FILE* f);

	/*-----------
	Get functions
	-----------*/

	unsigned int GetNumberID() const;

	unsigned int GetSizeX(), GetSizeY(), GetSizeZ();
	unsigned int GetSizeRotX(), GetSizeRotY(), GetSizeRotZ();

	const std::vector<bool>& GetDoFConstraints(const size_t& dof);

	//==========================================================================================================================

		/*------------------
		Overloaded operators
		-------------------*/

	friend bool operator< (const LineConstraint& line1, const LineConstraint& line2);
	friend bool operator> (const LineConstraint& line1, const LineConstraint& line2);
	friend bool operator== (const LineConstraint& line1, const LineConstraint& line2);
	friend bool operator!= (const LineConstraint& line1, const LineConstraint& line2);
};

