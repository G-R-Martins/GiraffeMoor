#pragma once
#include "Element.h"


class RigidBody : public Element
{
public:
	RigidBody();
	~RigidBody();


	/// 
	/// Overloaded operators
	/// 

	inline std::ofstream& WriteGiraffeFile(std::ofstream& out) override { operator<<(out, *this); return out; }
	friend std::ostream& operator<<(std::ostream& out, const RigidBody& obj);
};

