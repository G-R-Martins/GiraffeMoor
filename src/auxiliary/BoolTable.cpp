#include "PCH.h"
#include "BoolTable.h"
#include <stdarg.h>


BoolTable::BoolTable()
{}

BoolTable::BoolTable(const bool& bool_init, const int& bool_init_steps)
{
	data_table.clear();
	data_table.reserve(bool_init_steps);

	//"Bool_init_steps" with "bool_init"
	for (int i = 0; i < bool_init_steps; i++)
		data_table.emplace_back(bool_init);

	//Last element of the booltable if the opposite
	bool opposite = bool_init == true ? false : true;
	data_table.emplace_back(opposite);
	
}

BoolTable::BoolTable(const bool& bool_init, const int& bool_init_steps, const bool& generate_opposite)
{
	data_table.clear();
	data_table.reserve(bool_init_steps);

	//"Bool_init_steps" with "bool_init"
	for (int i = 0; i < bool_init_steps; i++)
		data_table.emplace_back(bool_init);

	//Last element of the booltable if the opposite
	if (generate_opposite)
	{
		bool opposite = bool_init == true ? false : true;
		data_table.emplace_back(opposite);
	}
}

BoolTable::BoolTable(const BoolTable &copied)
{
	data_table = copied.data_table;
}

BoolTable::BoolTable(const std::list<bool>& list)
{ this->Multiple_Push_Back(list); }

BoolTable::BoolTable(const std::forward_list<bool>&list)
{ this->Multiple_Push_Back(list); }

//Writes output file
void BoolTable::Write(FILE *f) const
{
	fprintf(f, "BoolTable ");
	for (int i = 0; i < data_table.size(); i++)
		fprintf(f, "%d ",(int)data_table[i]);
	fprintf(f, "\n");
}
std::ostream& operator<<(std::ostream& out, const BoolTable& btab)
{
	out << "BoolTable ";
	for (int i = 0; i < btab.GetSize(); ++i)
		out << btab.GetBoolOption(i) << " ";
	out << "\n";


	return out;
}

//Print output file
void BoolTable::Print() const
{
	printf("BoolTable ");
	for (int i = 0; i < data_table.size(); i++)
		printf("%d ", (int)data_table[i]);
	printf("\n");
}

BoolTable::~BoolTable()
{}

//Atribui valor value ao fim da tabela
void BoolTable::Set(int nargs, ...)
{
	data_table.clear();
	data_table.reserve(nargs);

	va_list valist;
	/* initialize valist for num number of arguments */
	va_start(valist, nargs);
	/* access all the arguments assigned to valist */
	for (int i = 0; i < nargs; i++)
	{
		bool bcopy = va_arg(valist, bool);
		//printf("%d\t", bcopy);
		data_table.push_back(bcopy);
	}

	/* clean memory reserved for valist */
	va_end(valist);
	//Print();
}

//Clear bool table data
void BoolTable::Clear()
{
	data_table.clear();
}

//Push back functions
void BoolTable::Push_Back(const bool& bool_value)
{
	data_table.push_back(bool_value);
}
void BoolTable::Multiple_Push_Back(const BoolTable& bt)
{
	this->data_table.insert(this->data_table.end(), bt.data_table.begin(), bt.data_table.end());
}
void BoolTable::Multiple_Push_Back(const std::list <bool>& list)
{
	for (bool b : list)
		data_table.push_back(b);
}
void BoolTable::Multiple_Push_Back(const std::forward_list <bool>& list)
{
	for (bool b : list)
		data_table.push_back(b);
}
void BoolTable::Multiple_Push_Back(const bool& bool_value, const unsigned int& n_times)
{
	for (unsigned int cont = 0; cont < n_times; ++cont)
		data_table.push_back(bool_value);
}

void BoolTable::Pop_Back()
{
	data_table.pop_back();
}

int BoolTable::Size()
{
	return (int)data_table.size();
}
size_t BoolTable::GetSize() const
{
	return data_table.size();
}

bool BoolTable::GetBoolOption(unsigned int pos) const
{
	return this->data_table[pos];
}
