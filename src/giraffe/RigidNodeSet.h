#pragma once
#include "SpecialConstraint.h"


class RigidNodeSet : public SpecialConstraint
{
private:
	unsigned int m_pilot_node_id;
	unsigned int m_node_set_id;
	std::string m_comment;

public:
	RigidNodeSet();
	RigidNodeSet(unsigned int pilot_node_id, unsigned int node_set_id, const std::string& comment = "");
	~RigidNodeSet();


	/// 
	/// GETTERS
	/// 

	inline unsigned int GetPilotNodeID() const { return m_pilot_node_id; }
	inline unsigned int GetNodeSet() const { return m_node_set_id; }
	inline const std::string& GetComment() const { return m_comment; }
	inline std::string& GetComment() { return m_comment; }


	/// 
	/// Overloaded operators
	/// 

	friend std::ostream& operator<<(std::ostream& out, const RigidNodeSet& obj);
	inline std::ofstream& WriteGiraffeFile(std::ofstream& out) override { operator<<(out, *this); return out; }
};

