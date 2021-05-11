#pragma once


class CADData
{
private:
	/*--------
	 Variables
	 --------*/

	size_t number;
	std::string name;

public:
	CADData() : number(0), name("\0") {};
	~CADData() = default;

	//IO
	bool Read(FILE* f);
	void WriteGiraffeModelFile(FILE* f);

	/*-------
	  Getters
	 -------*/

	size_t GetNumber() const;
	const std::string& GetName() const;
	
};

