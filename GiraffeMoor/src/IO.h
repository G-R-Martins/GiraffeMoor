#pragma once
#include "MooringModel.h"
#include "GiraffeModel.h"


class IO
{
public:
	IO();
	~IO();

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

	//==========================================================================================================================

	/*------
	Keywords
	-------*/


	enum class FirstLevelKeyword
	{
		//Initial value
		None = 0,

		//EOF
		EndOfFile = -1,

		Error = -100,
		//ERROR

		//Comment after a block with only first level keyword
		CommentAfterBlock = 1, 

		//Mandatory keywords
		Environment = 10, Keypoints, Lines, Vessels, SegmentProperties, Solution,

		//Optional keywords
		VesselDisplacements = 101, Platforms, GiraffeConvergenceCriteria, Monitors,
		PostProcessing, StiffnessMatrix, GiraffeSolver, Constraints, NodalForces, SegmentSets

	} cur_level; //Manages the reading first level (blue bold words)

	//==========================================================================================================================

					/*+-+-+-+-+-+-+-+
					|               |
					|   Functions   |
					|               |
					+-+-+-+-+-+-+-+-*/

	//Reads input file
	bool ReadFile();

	//Writes Giraffe input file
	void WriteGiraffeModelFile();

	//Reads first level keyword (blue bold words)
	bool ReadKeyword(FILE* f, fpos_t& pos, char* word);

	//Checks model
	bool CheckModel();
};
