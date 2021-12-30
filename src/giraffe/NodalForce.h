#pragma once
#include "Load.h"
#include "MathCode.h"


class NodalForce : public Load
{
private:
 	unsigned int m_nodeset_id;

	//External file
	std::string m_file_name;
	unsigned int m_header_lines;
	unsigned int m_steps;

	//Data pointers
	Table* m_ptr_table;
	MathCode* m_ptr_math_code;


public:

	NodalForce();

	NodalForce(Table* time_series);
	NodalForce(unsigned int nodeset_id, Table* time_series);

	NodalForce(MathCode* math_code);
	NodalForce(unsigned int nodeset_id, MathCode* math_code);

	NodalForce(const std::string& file_name, const unsigned int& header_lines, const unsigned int& steps);
	NodalForce(unsigned int nodeset_id, const std::string& file_name, const unsigned int& header_lines, const unsigned int& steps);

	~NodalForce();


	/// 
	/// GETTERS
	/// 
	
	inline unsigned int GetNodeset() const				{ return m_nodeset_id; }
	inline std::string const& GetFileName() const	{ return m_file_name; }
	inline std::string& GetFileName()				{ return m_file_name; }
	inline unsigned int GetNHeaderLines() const		{ return m_header_lines; }
	inline unsigned int GetNSteps() const			{ return m_steps; }
	inline Table const* GetTable() const			{ return m_ptr_table; }
	inline Table* GetTable()						{ return m_ptr_table; }
	inline MathCode const* GetMathCode() const		{ return m_ptr_math_code; }
	inline MathCode* GetMathCode()					{ return m_ptr_math_code; }



	/// 
	/// Overloaded operators
	/// 

	friend std::ostream& operator<<(std::ostream& out, const NodalForce& obj);
	inline std::ofstream& WriteGiraffeFile(std::ofstream& out) override { operator<<(out, *this); return out; }
};

