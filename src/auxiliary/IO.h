#pragma once

//It changes the folder to search for input file
#define _DEV_

enum class FirstLevelKeyword
{
	None = 0,				//Initial value
	EndOfFile = -1,			//End
	Error = -100,			//Invalid keyword
	CommentAfterBlock = 1,	//Comment after a block with only first level keyword (this can, and will, be improved changing the logic of the reading process)

	//Mandatory keywords
	Environment = 10, Keypoints, Lines, Vessels, SegmentProperties, Solution,

	//Optional keywords
	VesselDisplacements = 101, DisplacementFields, Platforms, GiraffeConvergenceCriteria, Monitors,
	PostProcessing, StiffnessMatrix, GiraffeSolver, Constraints, NodalForces, SegmentSets
};

class IO
{

/// <summary>
/// 
///		This pure static class manages the reading and writing of files,
///		although each object has its own reading and/or writing functions.
/// 
/// </summary>		
	
public:
					/*+-+-+-+-+-+-+-+
					|               |
					|   Variables   |
					|               |
					+-+-+-+-+-+-+-+-*/

	//Manages the reading first level (blue bold words in the Notepad++ language)
	static FirstLevelKeyword cur_level;

	//String (views) to input path
	static std::string folder_name, input_name;
	static std::string name; //with directory and extension

	//GiraffeMoor version (defined in '*.in.h' file)
	static std::string version;

	//==========================================================================================================================

					/*+-+-+-+-+-+-+-+
					|               |
					|   Functions   |
					|               |
					+-+-+-+-+-+-+-+-*/

	//Reads input file
	static bool ReadFile();

	//Check input data before trying to generate the FE model
	static bool CheckModel();

	//Writes Giraffe input file
	static void WriteGiraffeModelFile();

	//Reads first level keyword (blue bold words)
	static bool ReadKeyword(FILE* f, fpos_t& pos, char* word);

};
