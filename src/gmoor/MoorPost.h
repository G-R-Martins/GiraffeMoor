#pragma once
#include "CADData.h"
#include "WritingFlags.h"


class MoorPost
{
private:
	WritingFlags m_writing_flags;
	std::vector<CADData> m_vessel_cads;
	
public:
	MoorPost();
	~MoorPost();
	
	CADData* AddVesselCAD();

	void PushBackVesselCAD();


	/// 
	/// GETTERS
	/// 

	inline const WritingFlags& GetWritingFlags() const	{ return m_writing_flags; }
	inline WritingFlags& GetWritingFlags()				{ return m_writing_flags; }
	
	inline const CADData& GetVesselCAD(unsigned int platform) const		{ return m_vessel_cads[platform]; }
	inline CADData& GetVesselCAD(unsigned int platform)					{ return m_vessel_cads[platform]; }
	inline const std::vector<CADData>& GetAllVesselCADs() const	{ return m_vessel_cads; }
	inline std::vector<CADData>& GetAllVesselCADs()				{ return m_vessel_cads; }

};

