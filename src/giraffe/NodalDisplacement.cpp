#include "PCH.h"
#include "NodalDisplacement.h"


NodalDisplacement::NodalDisplacement()
	: m_node_set(0), m_cs(0), m_values(6),
	m_table(nullptr), m_math_code(nullptr), m_file_name("\0"), m_header_lines(0), m_tot_steps(0)
{}	

NodalDisplacement::NodalDisplacement(Table* table)
	: m_node_set(0), m_cs(0), m_values(6),
	m_table(nullptr), m_math_code(nullptr), m_file_name("\0"), m_header_lines(0), m_tot_steps(0)
{}
NodalDisplacement::NodalDisplacement(size_t node_set, size_t cs, Table* table)
	: m_node_set(node_set), m_cs(cs), m_values(6),
	m_table(table), m_math_code(nullptr), m_file_name("\0"), m_header_lines(0), m_tot_steps(0)
{}

NodalDisplacement::NodalDisplacement(MathCode* math_code)
	: m_node_set(0), m_cs(0), m_values(6),
	m_table(nullptr), m_math_code(math_code), m_file_name("\0"), m_header_lines(0), m_tot_steps(0)
{
	SetMathCodeOpt(true);
}
NodalDisplacement::NodalDisplacement(size_t node_set, size_t cs, MathCode* math_code)
	: m_node_set(node_set), m_cs(cs), m_values(6),
	m_table(nullptr), m_math_code(math_code), m_file_name("\0"), m_header_lines(0), m_tot_steps(0)

{
	SetMathCodeOpt(true);
}

NodalDisplacement::NodalDisplacement(const std::string& file_name, const unsigned int& header_lines, const unsigned int& tot_steps)
	: m_node_set(0), m_cs(0), m_values(6),
	m_table(nullptr), m_math_code(nullptr), m_file_name(file_name), m_header_lines(header_lines), m_tot_steps(tot_steps)
{
	SetExternalFileOpt(true);
}
NodalDisplacement::NodalDisplacement(size_t node_set, size_t cs, const std::string& file_name, const unsigned int& header_lines, const unsigned int& tot_steps)
	: m_node_set(node_set), m_cs(cs), m_values(6),
	m_table(nullptr), m_math_code(nullptr), m_file_name(file_name), m_header_lines(header_lines), m_tot_steps(tot_steps)
{
	SetExternalFileOpt(true);
}


NodalDisplacement::~NodalDisplacement()
{}


/// 
/// SETTERS
/// 

void NodalDisplacement::SetNodeSet(size_t node_set)
{
	m_node_set = node_set;
}

void NodalDisplacement::SetCoordinateSystem(size_t cs)
{
	m_cs = cs;
}

void NodalDisplacement::SetNColumns(size_t values)
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



/// 
/// Overloaded operators
/// 

std::ostream& operator<<(std::ostream& out, NodalDisplacement const& obj)
{
	out << "\tNodalDisplacement " << obj.GetNumber()
		<< "\tNodeSet " << obj.m_node_set
		<< "\tCS " << obj.m_cs << "\t";

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
