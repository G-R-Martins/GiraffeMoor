#pragma once
#include "Element.h"


class Pipe : public Element
{
public:
	Pipe();
	Pipe(unsigned int id, bool segment_begin, unsigned int section_id, unsigned int cs_id, std::vector<unsigned int> nodes);
	Pipe(unsigned int id, bool segment_begin, unsigned int section_id, unsigned int cs_id, std::vector<unsigned int> nodes, const std::string& comment);
	~Pipe();


	/// 
	/// Overloaded operators
	/// 

	friend std::ostream& operator<<(std::ostream& out, const Pipe& obj);
	inline std::ofstream& WriteGiraffeFile(std::ofstream& out) override { operator<<(out, *this); return out; }
};

