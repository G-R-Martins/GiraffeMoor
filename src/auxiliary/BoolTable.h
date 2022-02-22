#pragma once


class BoolTable
{
	std::vector<bool> m_data_table;

public:
	BoolTable();
	BoolTable(bool init_opt, size_t init_n_times = 1);  
	BoolTable(bool init_opt, size_t init_n_times, bool end_opt, size_t end_n_times = 1);
	BoolTable(bool init_opt, size_t init_n_times, bool mid_opt, size_t mid_n_times, bool end_opt, size_t end_n_times = 1);
	
	BoolTable(const std::list<bool>& bool_list);
	BoolTable(const std::forward_list<bool>& bool_list);
	BoolTable(const std::vector<bool>& bool_vec);

	BoolTable(BoolTable const& copied);
	BoolTable(BoolTable&& other) noexcept = default;

	~BoolTable();


	void Clear();					//Clear values
	void Reset(bool bool_opt, size_t n_times);
	void Reset(const std::vector<bool>& bool_vec);
		
	void Push_Back(bool bool_opt);
	void Multiple_Push_Back(const BoolTable& booltable);
	void Multiple_Push_Back(const std::vector<bool>& bool_vec);
	void Multiple_Push_Back(const std::list <bool>& bool_list);
	void Multiple_Push_Back(const std::forward_list<bool>& bool_list);
	void Multiple_Push_Back(bool bool_opt, size_t n_times);
	void Multiple_Push_Back(bool init_opt, size_t init_n_times, bool end_opt, size_t end_n_times = 1);
	
	void Pop_Back();
	
	
	/// 
	/// Get functions
	/// 
	
	size_t GetSize() const;
	bool GetBoolOption(unsigned int pos) const;


	///
	/// Overloaded operators
	///
	
	BoolTable& operator=(const BoolTable& bt)= default;
	BoolTable& operator=(BoolTable&& other) noexcept = default;

	friend std::ostream& operator<<(std::ostream& out, const BoolTable& btab);
};

