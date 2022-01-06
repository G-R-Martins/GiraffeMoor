#pragma once


class Table
{
public:
	Table();
	//Initialize the first line of the table
	Table(std::array<double, 7> first_line);
	~Table();
	
	//============================================================================


	//Copy
	Table(const Table& toCopy);
	Table& operator=(const Table& other) noexcept = default;

	//Assignment
	Table(Table&& other) = default;
	Table& operator=(Table&& other) noexcept;
	
	//Creates a new line at the end
	void SetLine(const double& time, const double& V1, const double& V2, const double& V3, const double& V4, const double& V5, const double& V6);
	void SetLine(const std::array<double, 7>& tab_line);
	
	//Creates a new line at the front
	//void SetLineFront(const double& time, const double& V1, const double& V2, const double& V3, const double& V4, const double& V5, const double& V6);
	
	void SetStartTime(const double& start, const unsigned int& line);

	inline unsigned int GetNLines() const { return (unsigned int)table.size(); }

	//Get specific value
	double GetValue(unsigned int lin, unsigned int col) const;

	
	inline const std::array<double, 7>& GetLine(unsigned int line) const	{ return table[line]; }
	inline std::array<double, 7>& GetLine(unsigned int line)				{ return table[line]; }

	//Writes table in the Giraffe file
	friend std::ostream& operator<<(std::ostream& out, Table* tabPtr);

	//============================================================================

	//Deque with data
	std::deque<std::array<double, 7>> table;
};