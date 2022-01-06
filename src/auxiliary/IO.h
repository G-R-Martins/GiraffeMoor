#pragma once


class IO
{

/// <summary>
/// 
///		This pure static class manages the reading and writing of files,
///		although each object has its own reading and/or writing functions.
/// 
/// </summary>		
private:
	static std::ifstream s_inp;
	//static std::unordered_map<std::string_view, std::function<bool(std::string& readed)>> s_func_reading;

public:


					/*+-+-+-+-+-+-+-+
					|               |
					|   Variables   |
					|               |
					+-+-+-+-+-+-+-+-*/


	//String (views) to input path
	static std::string folder_name;
	static std::string input_name;
	static std::string name; //with directory and extension

	//GiraffeMoor version (defined in '*.in.h' file)
	static std::string version;

	//==========================================================================================================================

					/*+-+-+-+-+-+-+-+
					|               |
					|   Functions   |
					|               |
					+-+-+-+-+-+-+-+-*/
	///
	/// Mandatory blocks
	///

	static bool ReadKeypoints(std::string& readed);
	static bool ReadSegmentSets(std::string& readed);
	static bool ReadLines(std::string& readed);
	static bool ReadVessels(std::string& readed);
	static bool ReadSegmentProperties(std::string& readed);
	static bool ReadEnvironment(std::string& readed);
	static bool ReadSolution(std::string& readed);

	///
	/// Optional blocks
	///

	static bool ReadGiraffeSolver(std::string& readed);
	static bool ReadPostProcessing(std::string& readed);
	static bool ReadStiffnessMatrix(std::string& readed);
	static bool ReadVesselDisplacements(std::string& readed);
	static bool ReadConstraints(std::string& readed);
	static bool ReadNodalLoads(std::string& readed);
	static bool ReadMonitors(std::string& readed);
	static bool ReadLineDisplacementFields(std::string& readed);


	//Reads input file (*.gmr)
	static bool ReadFile();

	static bool CheckAllMandatoryKeywords();

	//Check input data before trying to generate the FE model
	static bool CheckModel();

	//Writes Giraffe input file
	static void WriteGiraffeModelFile();

};
