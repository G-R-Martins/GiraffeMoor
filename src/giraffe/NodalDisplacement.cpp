#include "PCH.h"
#include "NodalDisplacement.h"


NodalDisplacement::NodalDisplacement()
	: m_node_set_id(0), m_cs_id(0), m_values(6),
	m_table(nullptr), m_math_code(nullptr), m_file_name("\0"), m_header_lines(0), m_tot_steps(0),
	m_booltable(), m_set_booltable(false)
{}	

NodalDisplacement::NodalDisplacement(Table* table)
	: m_node_set_id(0), m_cs_id(0), m_values(6),
	m_table(nullptr), m_math_code(nullptr), m_file_name("\0"), m_header_lines(0), m_tot_steps(0),
	m_booltable(), m_set_booltable(false)
{}
NodalDisplacement::NodalDisplacement(unsigned int nodeset_id, unsigned int cs_id, Table* table)
	: m_node_set_id(nodeset_id), m_cs_id(cs_id), m_values(6),
	m_table(table), m_math_code(nullptr), m_file_name("\0"), m_header_lines(0), m_tot_steps(0),
	m_booltable(), m_set_booltable(false)
{}

NodalDisplacement::NodalDisplacement(unsigned int id, unsigned int nodeset_id, unsigned int cs_id, Table* table)
	: m_node_set_id(nodeset_id), m_cs_id(cs_id), m_values(6),
	m_table(table), m_math_code(nullptr), m_file_name("\0"), m_header_lines(0), m_tot_steps(0),
	m_booltable(), m_set_booltable(false)
{
	this->SetIDNumber(id);
}

NodalDisplacement::NodalDisplacement(unsigned int id, unsigned int nodeset_id, unsigned int cs_id, Table* table, const BoolTable& booltable)
	: m_node_set_id(nodeset_id), m_cs_id(cs_id), m_values(6),
	m_table(table), m_math_code(nullptr), m_file_name("\0"), m_header_lines(0), m_tot_steps(0),
	m_booltable(booltable), m_set_booltable(true)
{
	this->SetIDNumber(id);
}

NodalDisplacement::NodalDisplacement(MathCode* math_code)
	: m_node_set_id(0), m_cs_id(0), m_values(6),
	m_table(nullptr), m_math_code(math_code), m_file_name("\0"), m_header_lines(0), m_tot_steps(0),
	m_booltable(), m_set_booltable(false)
{
	SetMathCodeOpt(true);
}
NodalDisplacement::NodalDisplacement(unsigned int nodeset_id, unsigned int cs_id, MathCode* math_code)
	: m_node_set_id(nodeset_id), m_cs_id(cs_id), m_values(6),
	m_table(nullptr), m_math_code(math_code), m_file_name("\0"), m_header_lines(0), m_tot_steps(0),
	m_booltable(), m_set_booltable(false)
{
	SetMathCodeOpt(true);
}

NodalDisplacement::NodalDisplacement(unsigned int id, unsigned int nodeset_id, unsigned int cs_id, MathCode* math_code)
	: m_node_set_id(nodeset_id), m_cs_id(cs_id), m_values(6),
	m_table(nullptr), m_math_code(math_code), m_file_name("\0"), m_header_lines(0), m_tot_steps(0),
	m_booltable(), m_set_booltable(false)
{
	this->SetIDNumber(id);
	SetMathCodeOpt(true);
}

NodalDisplacement::NodalDisplacement(unsigned int id, unsigned int nodeset_id, unsigned int cs_id, MathCode* math_code, const BoolTable& booltable)
	: m_node_set_id(nodeset_id), m_cs_id(cs_id), m_values(6),
	m_table(nullptr), m_math_code(math_code), m_file_name("\0"), m_header_lines(0), m_tot_steps(0),
	m_booltable(booltable), m_set_booltable(true)
{
	this->SetIDNumber(id);
	SetMathCodeOpt(true);
}

NodalDisplacement::NodalDisplacement(const std::string& file_name, unsigned int header_lines, unsigned int tot_steps)
	: m_node_set_id(0), m_cs_id(0), m_values(6),
	m_table(nullptr), m_math_code(nullptr), m_file_name(file_name), m_header_lines(header_lines), m_tot_steps(tot_steps),
	m_booltable(), m_set_booltable(false)
{
	SetExternalFileOpt(true);
}
NodalDisplacement::NodalDisplacement(unsigned int id, const std::string& file_name, unsigned int header_lines, unsigned int tot_steps)
	: m_node_set_id(0), m_cs_id(0), m_values(6),
	m_table(nullptr), m_math_code(nullptr), m_file_name(file_name), m_header_lines(header_lines), m_tot_steps(tot_steps),
	m_booltable(), m_set_booltable(false)
{
	SetExternalFileOpt(true);
	this->SetIDNumber(id);
}
NodalDisplacement::NodalDisplacement(unsigned int nodeset_id, unsigned int cs_id, const std::string& file_name, unsigned int header_lines, unsigned int tot_steps)
	: m_node_set_id(nodeset_id), m_cs_id(cs_id), m_values(6),
	m_table(nullptr), m_math_code(nullptr), m_file_name(file_name), m_header_lines(header_lines), m_tot_steps(tot_steps),
	m_booltable(), m_set_booltable(false)
{
	SetExternalFileOpt(true);
}

NodalDisplacement::NodalDisplacement(unsigned int id, unsigned int nodeset_id, unsigned int cs_id, const std::string& file_name, unsigned int header_lines, unsigned int tot_steps)
	: m_node_set_id(nodeset_id), m_cs_id(cs_id), m_values(6),
	m_table(nullptr), m_math_code(nullptr), m_file_name(file_name), m_header_lines(header_lines), m_tot_steps(tot_steps),
	m_booltable(), m_set_booltable(false)
{
	this->SetIDNumber(id);
	SetExternalFileOpt(true);
}

NodalDisplacement::NodalDisplacement(unsigned int id, unsigned int nodeset_id, unsigned int cs_id, const std::string& file_name, unsigned int header_lines, unsigned int tot_steps, const BoolTable& booltable)
	: m_node_set_id(nodeset_id), m_cs_id(cs_id), m_values(6),
	m_table(nullptr), m_math_code(nullptr), m_file_name(file_name), m_header_lines(header_lines), m_tot_steps(tot_steps),
	m_booltable(booltable), m_set_booltable(true)
{
	this->SetIDNumber(id);
	SetExternalFileOpt(true);
}


NodalDisplacement::~NodalDisplacement()
{}


/// 
/// SETTERS
/// 

void NodalDisplacement::SetNodeSet(unsigned int node_set_id)
{
	m_node_set_id = node_set_id;
}

void NodalDisplacement::SetCoordinateSystem(unsigned int cs_id)
{
	m_cs_id = cs_id;
}

void NodalDisplacement::SetNColumns(unsigned int values)
{
	m_values = values;
}

void NodalDisplacement::SetTable(Table* table)
{
	m_table = table;
}

void NodalDisplacement::SetMathCode(MathCode* math_code)
{
	m_math_code = math_code;
}

void NodalDisplacement::SetFileName(const std::string& file_name)
{
	m_file_name = file_name;
}

void NodalDisplacement::SetHeaderLines(unsigned int header_lines)
{
	m_header_lines = header_lines;
}

void NodalDisplacement::SetTotSteps(unsigned int tot_steps)
{
	m_tot_steps = tot_steps;
}

void NodalDisplacement::SetBoolTable(bool init_opt, size_t init_n_times)
{
	m_set_booltable = true;
	m_booltable.Multiple_Push_Back(init_opt, init_n_times);
}

void NodalDisplacement::SetBoolTable(bool init_opt, size_t init_n_times, bool end_opt, size_t end_n_times)
{
	m_set_booltable = true;
	m_booltable.Multiple_Push_Back(init_opt, init_n_times, end_opt, end_n_times);
}


void NodalDisplacement::SetBoolTable(const std::vector<bool>& bool_vec)
{
	m_set_booltable = true;
	m_booltable.Multiple_Push_Back(bool_vec);
}



/// 
/// Overloaded operators
/// 

std::ostream& operator<<(std::ostream& out, NodalDisplacement const& obj)
{
	out << "\tNodalDisplacement " << obj.GetNumber()
		<< "\tNodeSet " << obj.m_node_set_id
		<< "\tCS " << obj.m_cs_id << "\t";

	if (obj.m_set_booltable)
		out << "\t" << obj.GetBoolTable();

	if (obj.IsMathCode())
		out << "MathCode\n" << obj.m_math_code;
	else if (obj.IsExternalFile())
	{
		out << "\n\t\tFile \"" << obj.m_file_name << "\""
			<< "\tHeaderLines " << obj.m_header_lines
			<< "\tNTimes " << obj.m_tot_steps << "\n";
	}
	else
		out << "NTimes " << obj.m_table->GetNLines() << "\n" << obj.m_table;

	return out;
}
