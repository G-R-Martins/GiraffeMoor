#pragma once
#include "SpecialConstraint.h"


class RigidNodeSet : public SpecialConstraint
{
private:
	size_t m_pilot_node;
	size_t m_node_set;
	std::string m_comment;

public:
	RigidNodeSet();
	RigidNodeSet(size_t pilot_node, size_t node_set, const std::string& comment = "");
	~RigidNodeSet();


	/// 
	/// GETTERS
	/// 

	inline size_t GetNodeSet() const { return m_node_set; }
	inline const std::string& GetComment() const { return m_comment; }
	inline std::string& GetComment() { return m_comment; }


	/// 
	/// Overloaded operators
	/// 

	friend std::ostream& operator<<(std::ostream& out, const RigidNodeSet& obj);
	inline std::ofstream& WriteGiraffeFile(std::ofstream& out) override { operator<<(out, *this); return out; }
};

