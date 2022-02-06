#pragma once
#include "Element.h"


class RigidBody : public Element
{
public:
	RigidBody();
	RigidBody(unsigned int id, unsigned int RB_data_material_id, unsigned int cs_id, unsigned int node);
	RigidBody(unsigned int id, unsigned int RB_data_material_id, unsigned int cs_id, unsigned int node, const std::string& comment);
	~RigidBody();


	/// 
	/// Overloaded operators
	/// 

	inline std::ofstream& WriteGiraffeFile(std::ofstream& out) override { operator<<(out, *this); return out; }
	friend std::ostream& operator<<(std::ostream& out, const RigidBody& obj);
};

