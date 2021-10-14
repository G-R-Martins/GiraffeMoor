#pragma once


class SurfaceSet
{
private:
	size_t m_number;
	std::vector<size_t> m_surfaces;

public:
	SurfaceSet();
	SurfaceSet(size_t n, const std::vector<size_t>& surfaces);
	~SurfaceSet();
	

	/// 
	/// GETTERS
	/// 
	
	inline size_t GetNumber() const { return m_number; }
	inline const std::vector<size_t>& GetSurfaces() const { return m_surfaces; }
	inline std::vector<size_t>& GetSurfaces() { return m_surfaces; }
	
	
	/// 
	/// Overloaded operators
	/// 

	friend std::ostream& operator<<(std::ostream& out, const SurfaceSet& obj);
};

