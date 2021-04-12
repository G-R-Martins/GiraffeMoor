#pragma once


class MoorPost
{
public:
	MoorPost();
	~MoorPost();
	
	//============================================================================

	/*-------
	Functions
	--------*/

	//Reads input file
	bool Read(FILE *f);
	
	/*Static function to create a single static 
	  object and/or return a referece to that element*/ 
	//static MoorPost& MoorPost::Get();

	static std::tuple<bool, std::string> GetName(size_t plat_num);
	//============================================================================

	//CAD name(s)
	//static std::vector<std::string> platform_names;
	static std::map<size_t, std::string> platform_names;
};

