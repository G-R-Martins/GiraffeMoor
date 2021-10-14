#pragma once
#include "Element.h"


class Pipe : public Element
{
public:
	Pipe();
	~Pipe();


	/// 
	/// Overloaded operators
	/// 

	friend std::ostream& operator<<(std::ostream& out, const Pipe& obj);
	inline std::ofstream& WriteGiraffeFile(std::ofstream& out) override { operator<<(out, *this); return out; }
};

