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
	static std::unordered_map<std::string_view, std::function<bool(std::string& readed)>> s_func_reading;

public:


					/*+-+-+-+-+-+-+-+
					|               |
					|   Variables   |
					|               |
					+-+-+-+-+-+-+-+-*/


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

	static bool ReadKeypoint(std::string& readed);
	static bool ReadSegmentSet(std::string& readed);
	static bool ReadSegment(std::string& readed);
	static bool ReadLine(std::string& readed);
	static bool ReadVessel(std::string& readed);

	static bool ReadDynamicRelaxation(std::string& readed);
	static bool ReadDynRelaxLines(std::string& readed);
	static bool ReadDynRelaxVessels(std::string& readed);
	static bool ReadSeaCurrentStep(std::string& readed);
	static bool ReadAnalysis(std::string& readed);
	static bool ReadSolutionStep(std::string& readed);

	static bool ReadEnvGeneral(std::string& readed);
	static bool ReadSeabed(std::string& readed);
	static bool ReadSeaCurrent(std::string& readed);
	static bool ReadSeaCurrentAt(std::string& readed);

	static bool ReadSegmentProperty(std::string& readed);
	static bool ReadPostFiles(std::string& readed);
	static bool ReadCADs(std::string& readed);
	static bool ReadAnalyticalStiffnessMatrix(std::string& readed);
	static bool ReadNumericalStiffnessMatrix(std::string& readed);
	static void ReadDisplacementFields(std::string& readed);
	static void ReadConstraints(std::string& readed);
	static bool ReadRunOption(std::string& readed);
	static bool ReadProcessors(std::string& readed);
	static bool ReadConvergenceCriteria(std::string& readed);
	static bool ReadVesselDisplacement(std::string& readed);
	static void ReadStiffnessMatrix(std::string& readed);
	static void ReadNodalLoads(std::string& readed);


	//Reads input file
	static bool ReadFile();

	//Check input data before trying to generate the FE model
	static bool CheckModel();

	//Writes Giraffe input file
	static void WriteGiraffeModelFile();

};
