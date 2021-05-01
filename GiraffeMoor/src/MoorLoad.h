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

//protected:
	//============================================================================

			/*-------
			Variables
			--------*/

	//Data type
	Table* table;
	MathCode* mathCode;
	bool fromFile;
	std::string file_name;
	unsigned int header_lines, n_times;


	/*Node*/

	unsigned int nodeID;
	unsigned int segmentID;
	size_t lineID;

	//Name -> vessel (no ID), first, middle or last (node of segment)
	std::string description;

	//Initial step (may encompass more than one)
	unsigned int step;

};