#pragma once
#include "BoolTable.h"


class SpecialConstraint
{
private:
	unsigned int m_id;
protected:
	BoolTable m_booltable;

public:
	SpecialConstraint();
	SpecialConstraint(unsigned int id, const BoolTable& booltable);
	virtual ~SpecialConstraint();

	virtual inline std::ofstream& WriteGiraffeFile(std::ofstream& out) = 0;

	/// 
	/// SETTERS
	/// 
	
	void SetIDNumber(unsigned int id);
	void SetBoolTable(const BoolTable& booltable);


	/// 
	/// GETTERS
	/// 

	inline unsigned int GetIDNumber() const { return m_id; }
	inline const BoolTable& GetBoolTable() const { return m_booltable; }
	inline BoolTable& GetBoolTable() { return m_booltable; }
};

