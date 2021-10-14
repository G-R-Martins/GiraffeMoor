#pragma once
#include "BoolTable.h"


class SpecialConstraint
{
private:
	size_t m_number;
protected:
	BoolTable m_booltable;

public:
	SpecialConstraint();
	SpecialConstraint(size_t number, const BoolTable& booltable);
	virtual ~SpecialConstraint();

	virtual inline std::ofstream& WriteGiraffeFile(std::ofstream& out) = 0;

	/// 
	/// SETTERS
	/// 
	
	void SetIDNumber(size_t number);
	void SetBoolTable(const BoolTable& booltable);


	/// 
	/// GETTERS
	/// 

	inline size_t GetIDNumber() const { return m_number; }
	inline const BoolTable& GetBoolTable() const { return m_booltable; }
	inline BoolTable& GetBoolTable() { return m_booltable; }
};

