#pragma once


class Constraint
{
	unsigned int m_id;
public:
	Constraint();
	virtual ~Constraint();

	virtual inline std::ofstream& WriteGiraffeFile(std::ofstream& out) = 0;


	/// 
	/// SETTERS
	/// 

	void SetIDNumber(unsigned int id);

	/// 
	/// GETTERS
	/// 

	inline unsigned int GetNumber() const { return m_id; }
};

