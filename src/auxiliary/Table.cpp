#include "PCH.h"
#include "Table.h"
#include "AuxFunctions.h"

Table::Table()
{}
Table::Table(std::array<double, 7> first_line)
{ table.emplace_back(first_line); }

Table::~Table()
{}

//Assignment operator
Table& Table::operator=(Table&& other) noexcept
{
	if (this != &other)
	{
		table.erase(table.begin(), table.end());
		table = other.table;
		other.table.erase(other.table.begin(), other.table.end());
	}
	return *this;
}
//Copy constructor
Table::Table(const Table& toCopy)
{
	table.erase(table.begin(), table.end());
	table = toCopy.table;
}


//Push back a new line
void Table::SetLine(const double& time, const double& V1, const double& V2, const double& V3, const double& V4, const double& V5, const double& V6)
{
	table.emplace_back(std::array{ time, V1, V2, V3, V4, V5, V6 });
}

void Table::SetLine(const std::array<double, 7>& tab_line)
{
	table.emplace_back(tab_line);
}

//void Table::SetLineFront(const double& time, const double& V1, const double& V2, const double& V3, const double& V4, const double& V5, const double& V6)
//{
//	table.emplace_front(std::array{ time, V1, V2, V3, V4, V5, V6 });
//}

void Table::SetStartTime(const double& start_time, const unsigned int& start_line)
{
	for (unsigned int i = start_line; i < (unsigned int)table.size(); i++)
		table[i][0] += start_time;
}


double Table::GetValue(unsigned int lin, unsigned int col) const
{
	return table[lin][col];
}


// Writes table
std::ostream& operator<<(std::ostream& out, Table* tabPtr)
{
	for (size_t i = 0; i < tabPtr->table.size(); ++i)
	{
		out << "\t\t" << tabPtr->table[i][0];
		for ( int j = 1; j < 7; ++j )
			out << "\t" << tabPtr->table[i][j];
		out << "\n";
	}


	return out;
}

