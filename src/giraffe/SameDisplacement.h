#pragma once
#include "SpecialConstraint.h"


class SameDisplacement : public SpecialConstraint
{
private:
	size_t m_node_A;
	size_t m_node_B;
	size_t m_initial_load_step;

public:
	SameDisplacement();
	SameDisplacement(size_t node_A, size_t node_B, size_t initial_load_step = 0);
	~SameDisplacement();


	/// 
	/// GETTERS
	/// 
	
	inline size_t GetNodeA() const { return m_node_A; }
	inline size_t GetNodeB() const { return m_node_B; }
	inline size_t GetInitialLoadStep() const { return m_initial_load_step; }


	/// 
	/// Overloaded operators
	/// 

	friend std::ostream& operator<<(std::ostream& out, const SameDisplacement& obj);
	inline std::ofstream& WriteGiraffeFile(std::ofstream& out) override { operator<<(out, *this); return out; }

};

