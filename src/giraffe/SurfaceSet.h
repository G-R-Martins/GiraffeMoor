#pragma once


class SurfaceSet
{
private:
	unsigned int m_id;
	std::vector<unsigned int> m_surfaces;

public:
	SurfaceSet();
	SurfaceSet(unsigned int id, const std::vector<unsigned int>& surfaces);
	~SurfaceSet();
	

	/// 
	/// GETTERS
	/// 
	
	inline unsigned int GetIDNumber() const { return m_id; }
	inline const std::vector<unsigned int>& GetSurfaces() const { return m_surfaces; }
	inline std::vector<unsigned int>& GetSurfaces() { return m_surfaces; }
	
	
	/// 
	/// Overloaded operators
	/// 

	friend std::ostream& operator<<(std::ostream& out, const SurfaceSet& obj);
};

