#pragma once
#include "Solution.h"


class Static : public Solution
{
public:
	Static();
	~Static();
	
	inline std::ofstream& WriteGiraffeFile(std::ofstream& out) override { operator<<(out, *this); return out; }


	/// 
	/// Overloaded operators
	/// 

	friend std::ofstream& operator<<(std::ofstream& out, Static const& obj);
};

