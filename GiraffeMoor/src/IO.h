#pragma once
#include "MooringModel.h"
#include "GiraffeModel.h"


enum class FirstLevelKeyword
{
	None = 0,				//Initial value
	EndOfFile = -1,			//End
	Error = -100,			//Invalid keyword
	CommentAfterBlock = 1,	//Comment after a block with only first level keyword

	//Mandatory keywords
	Environment = 10, Keypoints, Lines, Vessels, SegmentProperties, Solution,

	//Optional keywords
	VesselDisplacements = 101, Platforms, GiraffeConvergenceCriteria, Monitors,
	PostProcessing, StiffnessMatrix, GiraffeSolver, Constraints, NodalForces, SegmentSets
};

class IO
{

	/*------------------------------------------------------------------------------------+
	|                                                                                     |
	|		This class manages the reading and writing of files, although each object	  |
	|	 actually has its own reading and/or writing functions                            |
	|                                                                                     |
	|	    The summary file is also contained inside this class (maybe separate it?).    |
	|    So, its variables and the write function are included here.                      |
	|                                                                                     |
	+------------------------------------------------------------------------------------*/
		
	//==========================================================================================================================

public:

	//Manages the reading first level (blue bold words)
	static FirstLevelKeyword cur_level; //Manages the reading first level (blue bold words)

	//==========================================================================================================================

					/*+-+-+-+-+-+-+-+
					|               |
					|   Functions   |
					|               |
					+-+-+-+-+-+-+-+-*/

	//Reads input file
	static bool ReadFile();

	//Writes Giraffe input file
	static void WriteGiraffeModelFile();

	//Reads first level keyword (blue bold words)
	static bool ReadKeyword(FILE* f, fpos_t& pos, char* word);

	//Checks model
	//static bool CheckModel();
};