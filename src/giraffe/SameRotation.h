#pragma once
#include "SpecialConstraint.h"


class SameRotation : public SpecialConstraint
{
private:
	unsigned int m_nodeA_id;
	unsigned int m_nodeB_id;

public:
	SameRotation();
	SameRotation(unsigned int nodeA_id, unsigned int nodeB_id);
	SameRotation(unsigned int id, unsigned int nodeA_id, unsigned int nodeB_id, const BoolTable& bool_table);
	~SameRotation();


	/// 
	/// GETTERS
	/// 

	inline unsigned int GetNodeA() const { return m_nodeA_id; }
	inline unsigned int GetNodeB() const { return m_nodeB_id; }


	/// 
	/// Overloaded operators
	/// 

	friend std::ostream& operator<<(std::ostream& out, const SameRotation& obj);
	inline std::ofstream& WriteGiraffeFile(std::ofstream& out) override { operator<<(out, *this); return out; }
};

