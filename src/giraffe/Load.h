#pragma once


class Load
{
protected:
	unsigned int m_id;
	unsigned int m_cs_id;

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
	
	void SetIDNumber(unsigned int id);
	void SetCoordinateSystem(unsigned int cs);
	void SetMathCodeOpt(bool option);
	void SetExternalFileOpt(bool option);


	/// 
	/// GETTERS
	/// 
	
	inline unsigned int GetNumber() const { return m_id; }
	inline unsigned int GetCoordinateSystem() const { return m_cs_id; }
	
	inline bool IsMathCode() const { return m_is_math_code; }
	inline bool IsExternalFile() const { return m_is_external_file; }

};

