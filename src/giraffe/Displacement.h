#pragma once


class Displacement
{
private:
	unsigned int m_id;

	bool m_is_math_code;  // using MathCode 
	bool m_is_external_file;  // defined in external file (csv or txt)

public:
	Displacement();
	Displacement(unsigned int id, bool is_math_code, bool is_external_file);
	virtual ~Displacement();

	virtual inline std::ofstream& WriteGiraffeFile(std::ofstream& out) = 0;
	
	/// 
	/// SETTERS
	/// 

	void SetIDNumber(unsigned int id);
	void SetMathCodeOpt(bool option);
	void SetExternalFileOpt(bool option);


	/// 
	/// GETTERS
	/// 

	inline unsigned int GetNumber() const { return m_id; }
	
	inline bool IsMathCode() const { return m_is_math_code; }
	inline bool IsExternalFile() const { return m_is_external_file; }
};

