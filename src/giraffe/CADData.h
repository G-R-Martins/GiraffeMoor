#pragma once


class CADData
{
private:

	size_t m_number;
	std::string m_name;

public:
	CADData();
	~CADData();

	//IO
	bool Read(FILE* f);
	void WriteGiraffeModelFile(std::ostream& fout) const;

	
	/// 
	/// SETTERS
	/// 

	void SetIDNumber(size_t number);
	void SetName(const std::string& name);


	/// 
	/// GETTERS
	/// 

	inline size_t GetNumber() const { return m_number; }
	inline const std::string& GetName() const { return m_name; }
	
};

