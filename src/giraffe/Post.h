#pragma once
#include "CADData.h"
#include "WritingFlags.h"

class Post
{
private:
	double m_mag_factor;  //Magnification factor of displacements
	WritingFlags m_writing_flags;

	std::vector<CADData> m_cad_vector;

public:
	Post();
	~Post();


	// Create VTK files
	bool CreateSeabedVTK(std::string& folder, const std::array<double, 2>& x, const std::array<double, 2>& y, const double& depth);
	bool CreateWaterVTK(std::string& folder, const std::array<double, 2>& x, const std::array<double, 2>& y);



	/// 
	/// SETTERS
	/// 
	
	void SetMagFactor(double mag_factor);
	void SetAllCADs(const std::vector<CADData>& cad_vector);
	void SetAllCADs(std::vector<CADData>&& cad_vector);
	void SetFlags(WritingFlags&& flags);

	/// 
	/// GETTERS
	/// 

	inline bool GetMagFactor() const { return m_mag_factor; }
	
	inline const WritingFlags& GetWritingFlags() const { return m_writing_flags; }
	inline WritingFlags& GetWritingFlags() { return m_writing_flags; }	

	inline const CADData& GetCAD(size_t platform) const { return m_cad_vector[platform]; }
	inline CADData& GetCAD(size_t platform) { return m_cad_vector[platform]; }
	inline const std::vector<CADData>& GetAllCADs() const { return m_cad_vector; }
	inline std::vector<CADData>& GetAllCADs() { return m_cad_vector; }



	/// 
	/// Overloaded operators
	/// 

	friend std::ostream& operator<<(std::ostream& out, const Post* obj);
};

