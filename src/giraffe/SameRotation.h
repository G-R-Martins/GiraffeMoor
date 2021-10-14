#pragma once
#include "SpecialConstraint.h"


class SameRotation : public SpecialConstraint
{
private:
	size_t m_node_A;
	size_t m_node_B;

public:
	SameRotation();
	SameRotation(size_t node_A, size_t node_B);
	~SameRotation();


	/// 
	/// GETTERS
	/// 

	inline size_t GetNodeA() const { return m_node_A; }
	inline size_t GetNodeB() const { return m_node_B; }


	/// 
	/// Overloaded operators
	/// 

	friend std::ostream& operator<<(std::ostream& out, const SameRotation& obj);
	inline std::ofstream& WriteGiraffeFile(std::ofstream& out) override { operator<<(out, *this); return out; }
};

