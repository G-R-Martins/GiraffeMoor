#include "PCH.h"
#include "BoolTable.h"


BoolTable::BoolTable()
{
	m_data_table.clear();
}

BoolTable::BoolTable(bool init_opt, size_t init_n_times)
{
	m_data_table = std::vector<bool>(init_n_times, init_opt);
}

BoolTable::BoolTable(bool init_opt, size_t init_n_times, bool end_opt, size_t end_n_times)
{
	m_data_table.reserve(init_n_times + end_n_times);

	for (int i = 0; i < init_n_times; ++i)
		m_data_table.emplace_back(init_opt);
	for (int i = 0; i < end_n_times; ++i)
		m_data_table.emplace_back(end_opt);
}

BoolTable::BoolTable(bool init_opt, size_t init_n_times, bool mid_opt, size_t mid_n_times, bool end_opt, size_t end_n_times)
{
	m_data_table.reserve(init_n_times + mid_n_times + end_n_times);

	for (int i = 0; i < init_n_times; ++i)
		m_data_table.emplace_back(init_opt);
	for (int i = 0; i < mid_n_times; ++i)
		m_data_table.emplace_back(mid_opt);
	for (int i = 0; i < end_n_times; ++i)
		m_data_table.emplace_back(end_opt);
}


BoolTable::BoolTable(const std::list<bool>& bool_list)
{
	this->Multiple_Push_Back(bool_list);
}

BoolTable::BoolTable(const std::forward_list<bool>& bool_list)
{
	this->Multiple_Push_Back(bool_list);
}
BoolTable::BoolTable(const std::vector<bool>& bool_vec)
{
	this->Multiple_Push_Back(bool_vec);
}


BoolTable::BoolTable(const BoolTable& copied)
{
	m_data_table = copied.m_data_table;
}


BoolTable::~BoolTable()
{}



//Clear bool table data
void BoolTable::Clear()
{
	m_data_table.clear();
}

void BoolTable::Reset(bool bool_opt, size_t n_times)
{
	m_data_table.clear();
	Multiple_Push_Back(bool_opt, n_times);
}

void BoolTable::Reset(const std::vector<bool>& bool_vec)
{
	m_data_table.clear();
	Multiple_Push_Back(bool_vec);
}

//Push back functions
void BoolTable::Push_Back(bool bool_opt)
{
	m_data_table.push_back(bool_opt);
}
void BoolTable::Multiple_Push_Back(const BoolTable& booltable)
{
	this->m_data_table.insert(this->m_data_table.end(), booltable.m_data_table.begin(), booltable.m_data_table.end());
}
void BoolTable::Multiple_Push_Back(const std::vector<bool>& bool_vec)
{
	this->m_data_table.insert(this->m_data_table.end(), bool_vec.begin(), bool_vec.end());
}
void BoolTable::Multiple_Push_Back(const std::list <bool>& bool_list)
{
	for (bool b : bool_list)
		m_data_table.push_back(b);
}
void BoolTable::Multiple_Push_Back(const std::forward_list <bool>& bool_list)
{
	for (bool b : bool_list)
		m_data_table.push_back(b);
}
void BoolTable::Multiple_Push_Back(bool bool_opt, size_t n_times)
{
	for (size_t cont = 0; cont < n_times; ++cont)
		m_data_table.push_back(bool_opt);
}

void BoolTable::Multiple_Push_Back(bool init_opt, size_t init_n_times, bool end_opt, size_t end_n_times)
{
	for (int i = 0; i < init_n_times; ++i)
		m_data_table.emplace_back(init_opt);
	for (int i = 0; i < end_n_times; ++i)
		m_data_table.emplace_back(end_opt);
}

void BoolTable::Pop_Back()
{
	m_data_table.pop_back();
}

size_t BoolTable::GetSize() const
{
	return m_data_table.size();
}

bool BoolTable::GetBoolOption(unsigned int pos) const
{
	return this->m_data_table[pos];
}



std::ostream& operator<<(std::ostream& out, const BoolTable& btab)
{
	out << "BoolTable ";
	for (int i = 0; i < btab.GetSize(); ++i)
		out << btab.GetBoolOption(i) << " ";


	return out;
}