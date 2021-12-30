#pragma once


class CADData
{
private:

	unsigned int m_id;
	std::string m_name;

public:
	CADData();
	~CADData();

	
	/// 
	/// SETTERS
	/// 

	void SetIDNumber(unsigned int id);
	void SetName(const std::string& name);


	/// 
	/// GETTERS
	/// 
	
	inline unsigned int GetNumber() const { return m_id; }
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

