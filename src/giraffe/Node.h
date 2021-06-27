#pragma once


class Node
{
public:
	Node();
	~Node();
	
	//Writes giraffe file
	void WriteGiraffeModelFile(std::ostream& fout) const;

	//============================================================================

	/*-------
	Variables
	--------*/
	
	//Node ID
	unsigned int number;

	//Mark to comment
	bool mark_comment;

	//Array with nodes coodinates at the reference configuration
	std::array <double, 3> ref_coordinates;
	
	//Comment
	char comment[100];
};

