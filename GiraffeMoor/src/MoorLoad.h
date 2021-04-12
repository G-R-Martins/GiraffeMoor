#pragma once
#include "MathCode.h"

class MoorLoad 
{
public:
	MoorLoad();
	~MoorLoad();
	
	//============================================================================

			/*-------
			Functions
			--------*/

	//Reads GiraffeMoor file
	bool Read(FILE* f);

	//============================================================================

			/*-------
			Variables
			--------*/

	//Data pointer
	Table* table;
	MathCode* mathCode;

	/*Node*/

	unsigned int nodeID;
	unsigned int segmentID;
	size_t lineID;

	//Name -> vessel (no ID), first, middle or last (node of segment)
	std::string description;

	//Initial step (may encompass more than one)
	unsigned int step;

	
};