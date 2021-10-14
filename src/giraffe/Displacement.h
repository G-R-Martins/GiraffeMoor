#pragma once


class Displacement
{
private:
	size_t m_number;

	bool m_is_math_code;  // using MathCode 
	bool m_is_external_file;  // defined in external file (csv or txt)

public:
	Displacement();
	Displacement(size_t number, bool is_math_code, bool is_external_file);
	virtual ~Displacement();

	virtual inline std::ofstream& WriteGiraffeFile(std::ofstream& out) = 0;
	
	/// 
	/// SETTERS
	/// 

	void SetIDNumber(size_t number);
	void SetMathCodeOpt(bool option);
	void SetExternalFileOpt(bool option);


	/// 
	/// GETTERS
	/// 

	inline size_t GetNumber() const { return m_number; }
	
	inline bool IsMathCode() const { return m_is_math_code; }
	inline bool IsExternalFile() const { return m_is_external_file; }
};

