#pragma once


class BoolTable
{
public:
	BoolTable();
	//"Bool_init_steps" with "bool_init" and a step (to the end) with the opposite of "bool_init"
	BoolTable(const bool& bool_init, const int& bool_init_steps);
	BoolTable(const bool& bool_init, const int& bool_init_steps, const bool& generate_opposite);
	BoolTable(BoolTable &copied);
	BoolTable(const std::list <bool>& list);
	BoolTable(const std::forward_list<bool>& list);
	
	~BoolTable();

	void Write(FILE *f) const;		//Writes BoolTable
	void Print() const;
	void Set(int nargs, ...);		//Atribui valor value ao fim da tabela
	void Clear();					//Seta a tabela de dados booleanos
	void Push_Back(const bool& bool_value);
	void Multiple_Push_Back(const BoolTable& bt);
	void Multiple_Push_Back(const std::list <bool>& list);
	void Multiple_Push_Back(const std::forward_list<bool>& list);
	void Multiple_Push_Back(const bool& bool_value, const unsigned int& n_times);
	void Pop_Back();
	int Size();

private:
	std::vector<bool> data_table;
};

