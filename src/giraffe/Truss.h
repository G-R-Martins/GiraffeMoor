#pragma once
#include "Element.h"


class Truss : public Element
{
public:
	Truss();
	~Truss();


	/// 
	/// Overloaded operators
	/// 

	friend std::ostream& operator<<(std::ostream& out, const Truss& obj);
	inline std::ofstream& WriteGiraffeFile(std::ofstream& out) override { operator<<(out, *this); return out; }
};


