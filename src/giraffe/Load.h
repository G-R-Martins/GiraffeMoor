#pragma once


class Load
{
protected:
	size_t m_number;
	size_t m_cs; 

	//Booleans to indicate if current nodal force uses math code or an external file
	///otherwise, must be defined in the GiraffeMoor input file after 'TimeSeries' keyword
	bool m_is_math_code;
	bool m_is_external_file;

	//==========================================================================================================================

public:
	Load();
	virtual ~Load();

	virtual inline std::ofstream& WriteGiraffeFile(std::ofstream& out) = 0;

	/// 
	/// SETTERS
	/// 
	
	void SetNumber(size_t number);
	void SetCoordinateSystem(size_t cs);
	void SetMathCodeOpt(bool option);
	void SetExternalFileOpt(bool option);


	/// 
	/// GETTERS
	/// 
	
	inline size_t GetNumber() const { return m_number; }
	inline size_t GetCoordinateSystem() const { return m_cs; }
	
	inline bool IsMathCode() const { return m_is_math_code; }
	inline bool IsExternalFile() const { return m_is_external_file; }

};

