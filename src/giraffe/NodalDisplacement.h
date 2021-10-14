#pragma once
#include "Displacement.h"
#include "MathCode.h"


class NodalDisplacement : public Displacement
{
private:
	size_t m_node_set;
	size_t m_cs;
	size_t m_values;  // number of columns
	
	Table* m_table;
	MathCode* m_math_code;

	std::string m_file_name;
	unsigned int m_header_lines;
	unsigned int m_tot_steps;

public:
	NodalDisplacement();
	~NodalDisplacement();

	NodalDisplacement(Table* table);
	NodalDisplacement(size_t node_set, size_t cs, Table* table);
	NodalDisplacement(MathCode* math_code);
	NodalDisplacement(size_t node_set, size_t cs, MathCode* math_code);
	NodalDisplacement(const std::string& file_name, const unsigned int& header_lines, const unsigned int& tot_steps);
	NodalDisplacement(size_t node_set, size_t cs, const std::string& file_name, const unsigned int& header_lines, const unsigned int& tot_steps);


	/// 
	/// SETTERS
	/// 
	
	void SetNodeSet(size_t node_set);
	void SetCoordinateSystem(size_t cs);
	void SetNColumns(size_t values);
	void SetTable(Table* table);
	void SetMathCode(MathCode* math_code);
	void SetFileName(const std::string& file_name);
	void SetHeaderLines(unsigned int header_lines);
	void SetTotSteps(unsigned int tot_steps);


	/// 
	/// GETTERS
	/// 

	inline size_t GetNodeset() const				{ return m_node_set; }
	inline size_t GetCoordinateSystem() const		{ return m_cs; }
	inline size_t GetNColumns() const				{ return m_values; }
	inline Table const* GetTable() const			{ return m_table; }
	inline Table* GetTable()						{ return m_table; }
	inline MathCode const* GetMathCode() const		{ return m_math_code; }
	inline MathCode* GetMathCode()					{ return m_math_code; }
	inline std::string const& GetFileName() const	{ return m_file_name; }
	inline unsigned int GetHeaderLines() const		{ return m_header_lines; }
	inline unsigned int GetTotSteps() const			{ return m_tot_steps; }


	/// 
	/// Overloaded operators
	/// 
	
	friend std::ostream& operator<<(std::ostream& out, NodalDisplacement const& obj);
	inline std::ofstream& WriteGiraffeFile(std::ofstream& out) override { operator<<(out, *this); return out; }
};
