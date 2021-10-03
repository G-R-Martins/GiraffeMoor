#pragma once
#include "CADData.h"
#include "WritingFlags.h"

class Post
{
public:
	double m_mag_factor;  //Magnification factor of displacements
	WritingFlags m_writing_flags;

	std::vector<CADData> m_cad_vector;

public:
	Post();
	~Post();


					/*-------
					Functions
					--------*/

	//Writes Giraffe file
	void WriteGiraffeModelFile(std::ostream& fout) const;

	// Creates seabed VTK file
	bool CreateSeabedVTK(std::string& folder, const std::array<double, 2>& x, const std::array<double, 2>& y, const double& depth);
	
	//Creates water surface VTK file
	bool CreateWaterVTK(std::string& folder, const std::array<double, 2>& x, const std::array<double, 2>& y);



	/// 
	/// SETTERS
	/// 
	
	void SetMagFactor(double mag_factor);
	void SetAllCADs(const std::vector<CADData>& cad_vector);
	void SetAllCADs(std::vector<CADData>&& cad_vector);


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

};

