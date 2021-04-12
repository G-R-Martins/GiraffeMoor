#pragma once


class MoorConstraint
{
public:
	MoorConstraint();
	~MoorConstraint();

	//Reads input file
	bool Read(FILE* f);

	/*-------
	Variables
	--------*/

	////Number of the line (anchor constraint) or vessel (vessel constraint)
	//unsigned int number;
	//
	////Nodeset number
	//unsigned int nodeset;
};

