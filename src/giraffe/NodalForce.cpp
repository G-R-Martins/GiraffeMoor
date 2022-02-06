#include "PCH.h"
#include "NodalForce.h"


NodalForce::NodalForce()
	: m_nodeset_id(0), m_file_name("\0"), m_header_lines(0), m_steps(0), m_ptr_table(nullptr), m_ptr_math_code(nullptr)
{}
NodalForce::NodalForce(Table* time_series)
	: m_nodeset_id(0), m_file_name("\0"), m_header_lines(0), m_steps(0), m_ptr_table(time_series), m_ptr_math_code(nullptr)
{}
NodalForce::NodalForce(unsigned int id, unsigned int nodeset_id, Table * time_series)
	: m_nodeset_id(nodeset_id), m_file_name("\0"), m_header_lines(0), m_steps(0), m_ptr_table(time_series), m_ptr_math_code(nullptr)
{
	this->SetIDNumber(id);
}
NodalForce::NodalForce(MathCode* math_code)
	: m_nodeset_id(0), m_file_name("\0"), m_header_lines(0), m_steps(0), m_ptr_table(nullptr), m_ptr_math_code(math_code)
{
	this->SetMathCodeOpt(true);
}
NodalForce::NodalForce(unsigned int id, unsigned int nodeset_id, MathCode* math_code)
	: m_nodeset_id(nodeset_id), m_file_name("\0"), m_header_lines(0), m_steps(0), m_ptr_table(nullptr), m_ptr_math_code(math_code)
{
	this->SetMathCodeOpt(true);
	this->SetIDNumber(id);
}
NodalForce::NodalForce(std::string& file_name, unsigned int header_lines, unsigned int steps)
	: m_nodeset_id(0), m_file_name(file_name), m_header_lines(header_lines), m_steps(steps), m_ptr_table(nullptr), m_ptr_math_code(nullptr)
{
	this->SetExternalFileOpt(true);
}
NodalForce::NodalForce(unsigned int id, unsigned int nodeset_id, std::string& file_name, unsigned int header_lines, unsigned int steps)
	: m_nodeset_id(nodeset_id), m_file_name(file_name), m_header_lines(header_lines), m_steps(steps), m_ptr_table(nullptr), m_ptr_math_code(nullptr)
{
	this->SetExternalFileOpt(true);
	this->SetIDNumber(id);
}

NodalForce::~NodalForce()
{
	if (m_ptr_table)
	{
		m_ptr_table->table.clear();
		m_ptr_table = nullptr;
	}
	if (m_ptr_math_code)
		delete m_ptr_math_code;
}





/// 
/// Overloaded operators
/// 

std::ostream& operator<<(std::ostream& out, const NodalForce& obj)
{
	out << "\tNodalLoad " << obj.GetNumber()
		<< "\tNodeSet " << obj.m_nodeset_id
		<< "\tCS " << obj.m_cs_id
		<< "\t";

	if (obj.m_is_math_code)
		out << "MathCode\n" << obj.m_ptr_math_code;
	else if (obj.IsExternalFile())
	{
		out << "\n\t\tFile \"" << obj.m_file_name << "\"" 
			<< "\tHeaderLines " << obj.m_header_lines 
			<< "\tNTimes " << obj.m_steps 
			<< "\n";
	}
	else
		out << "NTimes " << obj.m_ptr_table->GetNLines() << "\n" << obj.m_ptr_table;

	return out;
}
