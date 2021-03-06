#pragma once
#include "Displacement.h"
#include "MathCode.h"
#include "BoolTable.h"

class NodalDisplacement : public Displacement
{
private:
	unsigned int m_node_set_id;
	unsigned int m_cs_id;
	unsigned int m_values;  // number of columns
	
	Table* m_table;
	MathCode* m_math_code;

	std::string m_file_name;
	unsigned int m_header_lines;
	unsigned int m_tot_steps;

	BoolTable m_booltable;
	bool m_set_booltable;

public:
	NodalDisplacement();
	~NodalDisplacement();

	NodalDisplacement(Table* table);
	NodalDisplacement(unsigned int nodeset_id, unsigned int cs_id, Table* table);
	NodalDisplacement(unsigned int id, unsigned int nodeset_id, unsigned int cs_id, Table* table);
	NodalDisplacement(unsigned int id, unsigned int nodeset_id, unsigned int cs_id, Table* table, const BoolTable& booltable);
	NodalDisplacement(MathCode* math_code);
	NodalDisplacement(unsigned int nodeset_id, unsigned int cs_id, MathCode* math_code);
	NodalDisplacement(unsigned int id, unsigned int nodeset_id, unsigned int cs_id, MathCode* math_code);
	NodalDisplacement(unsigned int id, unsigned int nodeset_id, unsigned int cs_id, MathCode* math_code, const BoolTable& booltable);
	NodalDisplacement(const std::string& file_name, unsigned int header_lines, unsigned int tot_steps);
	NodalDisplacement(unsigned int id, const std::string& file_name, unsigned int header_lines, unsigned int tot_steps);
	NodalDisplacement(unsigned int nodeset_id, unsigned int cs_id, const std::string& file_name, unsigned int header_lines, unsigned int tot_steps);
	NodalDisplacement(unsigned int id, unsigned int nodeset_id, unsigned int cs_id, const std::string& file_name, unsigned int header_lines, unsigned int tot_steps);
	NodalDisplacement(unsigned int id, unsigned int nodeset_id, unsigned int cs_id, const std::string& file_name, unsigned int header_lines, unsigned int tot_steps, const BoolTable& booltable);


	/// 
	/// SETTERS
	/// 
	
	void SetNodeSet(unsigned int node_set_id);
	void SetCoordinateSystem(unsigned int cs_id);
	void SetNColumns(unsigned int values);
	void SetTable(Table* table);
	void SetMathCode(MathCode* math_code);
	void SetFileName(const std::string& file_name);
	void SetHeaderLines(unsigned int header_lines);
	void SetTotSteps(unsigned int tot_steps);

	void SetBoolTable(bool init_opt, size_t init_n_times = 1);
	void SetBoolTable(bool init_opt, size_t init_n_times, bool end_opt, size_t end_n_times = 1);
	void SetBoolTable(const std::vector<bool>& bool_vec);


	/// 
	/// GETTERS
	/// 

	inline unsigned int GetNodeset() const			{ return m_node_set_id; }
	inline unsigned int GetCoordinateSystem() const	{ return m_cs_id; }
	inline unsigned int GetNColumns() const			{ return m_values; }
	inline Table const* GetTable() const			{ return m_table; }
	inline Table* GetTable()						{ return m_table; }
	inline MathCode const* GetMathCode() const		{ return m_math_code; }
	inline MathCode* GetMathCode()					{ return m_math_code; }
	inline std::string const& GetFileName() const	{ return m_file_name; }
	inline unsigned int GetHeaderLines() const		{ return m_header_lines; }
	inline unsigned int GetTotSteps() const			{ return m_tot_steps; }
	inline BoolTable const& GetBoolTable() const	{ return m_booltable; }
	inline BoolTable& GetBoolTable()				{ return m_booltable; }
	inline bool GetBoolTableOpt() const				{ return m_set_booltable; }


	/// 
	/// Overloaded operators
	/// 
	
	friend std::ostream& operator<<(std::ostream& out, NodalDisplacement const& obj);
	inline std::ofstream& WriteGiraffeFile(std::ofstream& out) override { operator<<(out, *this); return out; }
};
