#pragma once


class Summary
{
	Summary();
	~Summary() = default;

	/*************
	 * Variables * 
	 *************/

	//Name of the summary file (with extension)
	std::string summ_name;

	//Maximum and minumum values for the sea current speed
	double max_speed = 0.0, min_speed = 100.0;

	//Sea current constant value -> assumed to be equal to zero
	double value_const_seacur = 0.0;
	

	//Data of line(s) extremities
	struct LineExtremities
	{
		unsigned int node;
		unsigned int element;
		unsigned int nodeset;
		double tension;
	};

	//Summary of line(s) data
	struct SummLines
	{
		unsigned int number;
		std::string_view config;
		bool hasTDP;
		double tdp_pos;
		double len; 
		unsigned int segs;
		std::pair<Summary::LineExtremities, Summary::LineExtremities> extremities;
	};
	std::vector<SummLines> lines;


public:

	/* Tuple with :
		[ double, double, string ]  ->  [ initial time, end time, description ] */
	std::vector<std::tuple<double, double, std::string>> steps;


	//Summary file sections
	enum class Level
	{
		CreateSummaryFile = 0,
		Lines, Vessels, Environment, Solution, StiffMatrix,
	};

	//Writes summary file
	void CreateSumFile(const std::string& name_with_folder, const std::string& version);
	void Append2File();

	//Return Singleton
	static Summary& Summary::Get()
	{
		static Summary summary;
		return summary;
	}


	static void AddLine( const std::array<unsigned int, 2>& nodes, const std::array<unsigned int, 2>& elements,
						 const std::array<unsigned int, 2>& nodesets, const std::array<double, 2>& tensions,
						 const unsigned int& number, const std::string_view& configuration,
						 bool TDP, const double& x_tdp, const double& total_length, const unsigned int& segs );
	
	friend std::ostream& operator<<(std::ostream& out, const Summary::SummLines& line);
};

