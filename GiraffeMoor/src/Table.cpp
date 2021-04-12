#include "PCH.h"
#include "Table.h"

Table::Table()
{
	table.clear();
}

//Assignment operator
Table& Table::operator=(Table&& other) noexcept
{
	if (this != &other)
	{
		for (size_t i = 0; i < table.size(); i++)
			delete[] table[i];
		table.clear();

		table = other.table;

		for (size_t i = 0; i < other.table.size(); i++)
			delete[] other.table[i];
		other.table.clear();
	}
	return *this;
}

Table::Table(const Table& toCopy)
{
	table.clear();
	for (int i = 0; i < (int)toCopy.table.size(); i++)
	{
		table.push_back(new double[7]);
		for (int j = 0; j < 7; j++)
			table[i][j] = toCopy.table[i][j];
	}
}

Table::~Table()
{
	for (int i = 0; i < (int)table.size(); i++)
		delete[] table[i];
	table.clear();
}

//Push back a new line
void Table::SetLine(const double& time, const double& V1, const double& V2, const double& V3, const double& V4, const double& V5, const double& V6)
{
	table.push_back(new double[7]);
	table.back()[0] = time;
	table.back()[1] = V1;
	table.back()[2] = V2;
	table.back()[3] = V3;
	table.back()[4] = V4;
	table.back()[5] = V5;
	table.back()[6] = V6;
}

void Table::SetLineFront(const double& time, const double& V1, const double& V2, const double& V3, const double& V4, const double& V5, const double& V6)
{
	table.push_front(new double[7]);
	table.front()[0] = time;
	table.front()[1] = V1;
	table.front()[2] = V2;
	table.front()[3] = V3;
	table.front()[4] = V4;
	table.front()[5] = V5;
	table.front()[6] = V6;
}

void Table::SetStartTime(const double& start_time, const size_t& start_line)
{
	for (size_t i = start_line; i < table.size(); i++)
		table[i][0] += start_time;
}


void  Table::Write(FILE *f) const
{
	//Escrita da tabela
	for (int i = 0; i < (int)table.size(); i++)
	{
		fprintf(f, "\t%.6e", table[i][0]);
		for (int j = 1; j < 7; j++)
			fprintf(f, "\t%.6e", table[i][j]);
		fprintf(f, "\n");
	}
}

unsigned int  Table::GetLines() const
{
	return static_cast< unsigned int >(table.size());
}

//Reads input file
bool Table::Read(FILE *f)
{
	char s[1000];
	table.clear();
	fpos_t pos;
	fgetpos(f, &pos);
	bool flag_not_digit = false;
	fscanf(f, "%s", s);
	int col = 0;
	int lin = 0;
	while (!flag_not_digit)
	{
		if (col == 0)
		{
			table.push_back(new double[7]);
			for (int i = 0; i < 7; i++)
				table[lin][i] = 0.0;
		}
		
		table[lin][col]=atof(s);
		//Próxima leitura
		fgetpos(f, &pos);
		if (fscanf(f, "%s", s) == EOF)
			return true;
		if (!isdigit(s[0]) && s[0]!='-' && s[0] != '.')
			flag_not_digit = true;
		else
		{
			if (col != 6)
				col++;
			else
			{
				lin++;
				col = 0;
			}
		}
	}
	fsetpos(f, &pos);
	return true;
}