#pragma once
#include "SpecialConstraint.h"


class SameDisplacement : public SpecialConstraint
{
private:
	unsigned int m_nodeA_id;
	unsigned int m_nodeB_id;
	unsigned int m_initial_load_step_id;

public:
	SameDisplacement();
	SameDisplacement(unsigned int nodeA_id, unsigned int nodeB_id, unsigned int initial_load_step_id = 0);
	SameDisplacement(unsigned int id, unsigned int nodeA_id, unsigned int nodeB_id, const BoolTable& bool_table, unsigned int initial_load_step_id = 0);
	~SameDisplacement();


	/// 
	/// GETTERS
	/// 
	
	inline unsigned int GetNodeA() const { return m_nodeA_id; }
	inline unsigned int GetNodeB() const { return m_nodeB_id; }
	inline unsigned int GetInitialLoadStep() const { return m_initial_load_step_id; }


	/// 
	/// Overloaded operators
	/// 

	friend std::ostream& operator<<(std::ostream& out, const SameDisplacement& obj);
	inline std::ofstream& WriteGiraffeFile(std::ofstream& out) override { operator<<(out, *this); return out; }

};

