#pragma once


class Table
{
public:
	Table();
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
	
	//Creates a new line at the front
	void SetLineFront(const double& time, const double& V1, const double& V2, const double& V3, const double& V4, const double& V5, const double& V6);
	
	void SetStartTime(const double& start, const size_t& line);

	//Get number of lines
	unsigned int GetLines() const;
	
	//Writes table in the Giraffe file
	void Write(FILE *f) const;

	//Reads input file
	bool Read(FILE *f);
	
	//============================================================================

	//Deque with data
	//std::deque<std::array<double,7>> table;
	std::deque<std::array<double,7>> table;
};