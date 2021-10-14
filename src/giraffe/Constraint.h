#pragma once


class Constraint
{
	size_t m_number;
public:
	Constraint();
	virtual ~Constraint();

	virtual inline std::ofstream& WriteGiraffeFile(std::ofstream& out) = 0;


	/// 
	/// SETTERS
	/// 

	void SetIDNumber(size_t number);

	/// 
	/// GETTERS
	/// 

	inline size_t GetNumber() const { return m_number; }
};

