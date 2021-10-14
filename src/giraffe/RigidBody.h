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

	friend std::ostream& operator<<(std::ostream& out, const RigidBody& obj);
	inline std::ofstream& WriteGiraffeFile(std::ofstream& out) override { operator<<(out, *this); return out; }
};

