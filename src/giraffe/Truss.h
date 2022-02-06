#pragma once
#include "Element.h"


class Truss : public Element
{
public:
	Truss();
	Truss(unsigned int id, bool segment_begin, unsigned int section_id, unsigned int node1, unsigned int node2);
	Truss(unsigned int id, bool segment_begin, unsigned int section_id, unsigned int node1, unsigned int node2, const std::string& comment);
	~Truss();


	/// 
	/// Overloaded operators
	/// 

	friend std::ostream& operator<<(std::ostream& out, const Truss& obj);
	inline std::ofstream& WriteGiraffeFile(std::ofstream& out) override { operator<<(out, *this); return out; }
};


