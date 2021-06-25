#include "PCH.h"
#include "Table.h"

Table::Table()
{}
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

void Table::SetLineFront(const double& time, const double& V1, const double& V2, const double& V3, const double& V4, const double& V5, const double& V6)
{
	table.emplace_front(std::array{ time, V1, V2, V3, V4, V5, V6 });
}

void Table::SetStartTime(const double& start_time, const size_t& start_line)
{
	for (size_t i = start_line; i < table.size(); i++)
		table[i][0] += start_time;
}


unsigned int Table::GetLines() const
{
	return static_cast< unsigned int >(table.size());
}

//Reads input file
bool Table::Read(FILE *f)
{
	char s[256];
	fpos_t pos;
	bool flag_not_digit = false;

	//Reads data
	for (size_t lin = 0; !flag_not_digit; ++lin)
	{
		//Creates a new line and set the time
		if (!flag_not_digit && !fgetpos(f, &pos) && fscanf(f, "%s", s) != EOF ///check for digit and read next word
			&& (isdigit(s[0]) || s[0] == '.')) ///check for valid input (must be a positive number)
			table.emplace_back(std::array{ atof(s), 0.0, 0.0 , 0.0 , 0.0 , 0.0 , 0.0 });
		else 
			break;

		//Reads values
		///					   check digit        save position     read word and check for EOF       
		for (size_t col = 1; !flag_not_digit && !fgetpos(f, &pos) && fscanf(f, "%s", s) != EOF
			 && col != 6; ++col)///update column
		{
			//Check if a number was readed and assign to the current position on table
			if (!isdigit(s[0]) && s[0] != '-' && s[0] != '.')
				flag_not_digit = true;
			else
				table[lin][col] = atof(s);
		}
	}

	fsetpos(f, &pos);
	return true;
}

std::ostream& operator<<(std::ostream& out, Table* tabPtr)
{
	//Writes table
	for (size_t i = 0; i < tabPtr->table.size(); ++i)
	{
		out << "\t" << tabPtr->table[i][0];
		for ( int j = 1; j < 7; ++j )
			out << "\t" << tabPtr->table[i][j];
		out << "\n";
	}


	return out;
}
