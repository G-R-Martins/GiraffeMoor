#pragma once


class MoorConstraint
{
public:
	MoorConstraint();
	~MoorConstraint();

	//Reads input file
	bool Read(FILE* f);

	
	///TODO: transformar vessel e anchor constraint em subclasses
	///		 assim como 'Static' e 'Dynamic' com respeito a 'Solution'
	
	/*-------
	Variables
	--------*/

	////Number of the line (anchor constraint) or vessel (vessel constraint)
	//unsigned int number;
	//
	////Nodeset number
	//unsigned int nodeset;
};

