#pragma once
#include "MoorConstraint.h"

class AnchorConstraint// : public MoorConstraint
{
public:
	AnchorConstraint();
	~AnchorConstraint();
	

	//Reads input file
	bool Read(FILE *f);

	/*-------
	Variables
	--------*/

	//Number of the line
	unsigned int number;
	
	//Anchor nodeset
	unsigned int nodeset;

	int rotx;
	int roty;
	int rotz;

	
	//============================================================================

	/*------------------
	Overloaded operators
	-------------------*/

	friend bool operator< (const AnchorConstraint& anchor1, const AnchorConstraint& anchor2);
	friend bool operator> (const AnchorConstraint& anchor1, const AnchorConstraint& anchor2);
	friend bool operator== (const AnchorConstraint& anchor1, const AnchorConstraint& anchor2);
	friend bool operator!= (const AnchorConstraint& anchor1, const AnchorConstraint& anchor2);
	
};

