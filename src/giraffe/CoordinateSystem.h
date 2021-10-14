#pragma once


class CoordinateSystem
{
private:
	size_t m_number;
	
	//Versor
	std::array<double, 3> m_E1;
	std::array<double, 3> m_E3;

public:
	CoordinateSystem();
	CoordinateSystem(size_t ID, const std::array<double, 3>& E1, const std::array<double, 3>& E3);
	~CoordinateSystem();


	///
	/// SETTERS
	/// 
	
	void SetIDNumber(size_t ID);
	void SetE1(const std::array<double, 3>& coordinates);
	void SetE3(const std::array<double, 3>& coordinates);
	void SetVersor(const std::array<double, 3>& E1, const std::array<double, 3>& E3);


	///
	/// GETTERS
	/// 

	inline size_t GetNumber() const { return m_number; }
	inline double GetCoordinate(int versor, size_t coord) const { return (versor == 1 ? m_E1[coord] : m_E3[coord]); }
	inline std::array<double, 3> const& GetVersor(int versor) const { return (versor == 1 ? m_E1 : m_E3); }


	/// 
	/// Overloaded operators
	/// 

	friend std::ostream& operator<<(std::ostream& out, const CoordinateSystem& obj);

};


