#pragma once


class CADData
{
private:

	size_t m_number;
	std::string m_name;

public:
	CADData();
	~CADData();

	
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
	
	
	/// 
	/// Overloaded operators
	/// 

	friend bool operator<(const CADData& obj1, const CADData& obj2);
	friend bool operator>(const CADData& obj1, const CADData& obj2);
	friend bool operator==(const CADData& obj1, const CADData& obj2);
	friend bool operator!=(const CADData& obj1, const CADData& obj2);

	friend std::ostream& operator<<(std::ostream& out, const CADData& obj);
};

