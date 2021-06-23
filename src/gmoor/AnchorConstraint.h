#pragma once

class AnchorConstraint// : public MoorConstraint
{

	//Number of the line
	unsigned int number;
	
	//Anchor nodeset
	unsigned int nodeset;

	//Rotations
	int rotx, roty, rotz;

public:
	AnchorConstraint();
	~AnchorConstraint();
	
	//Reads input file
	bool Read(FILE *f);
	
	/*-------
	  Getters  
	 -------*/

	unsigned int GetNumberID() const ;
	unsigned int GetNodeSet() const;
	int GetRot(char rot) const;

	void SetNodeSet(const unsigned int& node_set);


	
	/*------------------
	Overloaded operators
	-------------------*/

	friend bool operator< (const AnchorConstraint& anchor1, const AnchorConstraint& anchor2);
	friend bool operator> (const AnchorConstraint& anchor1, const AnchorConstraint& anchor2);
	friend bool operator== (const AnchorConstraint& anchor1, const AnchorConstraint& anchor2);
	friend bool operator!= (const AnchorConstraint& anchor1, const AnchorConstraint& anchor2);
};
