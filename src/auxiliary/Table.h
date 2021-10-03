#pragma once


class Table
{
public:
	Table();
	//Initialize the first line of the table
	Table(std::array<double, 7> first_line);
	~Table();
	
	//============================================================================


	/*-------
	Functions
	--------*/

	//Copy constructor
	Table(const Table& toCopy);

	//Assignment operator
	Table& operator=(Table&& other) noexcept;
	
	//Creates a new line at the end
	void SetLine(const double& time, const double& V1, const double& V2, const double& V3, const double& V4, const double& V5, const double& V6);
	void SetLine(const std::array<double, 7>& tab_line);
	
	//Creates a new line at the front
	//void SetLineFront(const double& time, const double& V1, const double& V2, const double& V3, const double& V4, const double& V5, const double& V6);
	
	void SetStartTime(const double& start, const size_t& line);

	inline size_t GetNLines() const { return table.size(); }

	//Get specific value
	double GetValue(unsigned int lin, unsigned int col) const;

	
	inline const std::array<double, 7>& GetLine(size_t line) const	{ return table[line]; }
	inline std::array<double, 7>& GetLine(size_t line)				{ return table[line]; }

	//Writes table in the Giraffe file
	friend std::ostream& operator<<(std::ostream& out, Table* tabPtr);
	friend std::ifstream& operator>>(std::ifstream& input, Table* table);
	//============================================================================

	//Deque with data
	std::deque<std::array<double, 7>> table;
};