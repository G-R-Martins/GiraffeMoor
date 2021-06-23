#pragma once


class Element
{
public:
	Element();
	virtual ~Element();

	//============================================================================
	
	//Interface
	virtual void WriteGiraffeModelFile(FILE *f) = 0;

	//============================================================================

	/*-------
	Variables
	--------*/

	//Material ID
	unsigned int material;

	//Section ID
	unsigned int section;

	//Element ID
	unsigned int number;

	//Number of nodes
	unsigned int n_nodes;

	//Coordinate system ID of the element
	unsigned int cs;

	//Global nodes - conectivity
	std::vector <unsigned int> nodes;

	//Marker (to comment)
	bool mark_segment_begin;
};

