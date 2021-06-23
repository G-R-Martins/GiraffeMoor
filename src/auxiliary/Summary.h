#pragma once


class Summary
{
	Summary();
	~Summary() = default;
	/// <summary>
	///	
	/// This Singleton manages the summary of the model and
	/// the creation and edition of the '.sum' file.
	/// 
	/// 
	/// The lines summary is made with two auxiliary structs:
	///		- LineExtremities: which handle the summary of extremities 
	///                        nodes (e.g.: anchors and fairleads)
	///		- SummLines: which include general information (e.g.: length)
	///                  and condenses the 'LineExtremities' data in a 'std::pair'
	///		This section has also a overloading of the operator '<<' to print out
	/// </summary>


	/*************
	 * Variables * 
	 *************/

	//Name of the summary file (with extension)
	std::string summ_name;

	//Data of line(s) extremities
	struct LineExtremities
	{
		unsigned int node = 0;
		unsigned int element = 0;
		unsigned int nodeset = 0;
		double tension = 0.0;
	};

	//Summary of line(s) data
	struct SummLines
	{
		unsigned int number = 0;
		std::string_view config;
		bool hasTDP = true;
		double tdp_pos = 0.0;
		double len = 0.0;
		unsigned int segs = 0;
		std::pair<Summary::LineExtremities, Summary::LineExtremities> extremities;
	};
	std::vector<SummLines> lines;

	/* vector of tuples with:
		[ double, double, string ]  ->  [ initial time, end time, description ] */
	std::vector<std::tuple<double, double, std::string>> steps;
	
	/*************
	 * Functions * 
	 *************/

	//Implementations of corresponding static functions
	void CreateSumFile_Impl(const std::string& name_with_folder, const std::string& version);
	void Append2File_Impl();
	void AddLine_Impl(const std::array<unsigned int, 2>& nodes, const std::array<unsigned int, 2>& elements,
						 const std::array<unsigned int, 2>& nodesets, const std::array<double, 2>& tensions,
						 const unsigned int& number, const std::string_view& configuration,
						 bool TDP, const double& x_tdp, const double& total_length, const unsigned int& segs );
	std::vector<std::tuple<double, double, std::string>>& GetSteps_Impl();

	//===========================================================================================================

public:

	//Create/return Singleton instance
	static Summary& Summary::getInstance() { static Summary summary; return summary; }

	//Deleting copy and assignment 
	Summary(const Summary&) = delete;
	Summary(Summary&&) = delete;
	Summary& operator=(const Summary&) = delete;

	
	/********************
	 * Static functions *
	 ********************/

	static void CreateSumFile(const std::string& fullname, const std::string& version) { 
		return getInstance().CreateSumFile_Impl(fullname, version); }
	
	static void Append2File() { 
		return getInstance().Append2File_Impl(); }
	
	static void AddLine( const std::array<unsigned int, 2>& nodes, const std::array<unsigned int, 2>& elements,
						 const std::array<unsigned int, 2>& nodesets, const std::array<double, 2>& tensions,
						 const unsigned int& number, const std::string_view& configuration,
						 bool TDP, const double& x_tdp, const double& total_length, const unsigned int& segs ) { 
		return getInstance().AddLine_Impl(nodes, elements, nodesets, tensions, number, configuration, TDP, x_tdp, total_length, segs); }
	
	static auto& GetSteps() { 
		return getInstance().GetSteps_Impl(); }

	///
	///Overloaded operator to print line in the summary file 
	///
	friend std::ostream& operator<<(std::ostream& out, const Summary::SummLines& line);
};

