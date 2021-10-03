#pragma once
#include "CADData.h"
#include "WritingFlags.h"


class MoorPost
{
private:
	WritingFlags m_writing_flags;
	std::vector<CADData> m_platform_cads;
	
public:
	MoorPost();
	~MoorPost();
	
	void AddPlatformCAD(const CADData& cad);
	

	/// 
	/// GETTERS
	/// 

	inline const WritingFlags& GetWritingFlags() const	{ return m_writing_flags; }
	inline WritingFlags& GetWritingFlags()				{ return m_writing_flags; }
	
	inline const CADData& GetPlatformCAD(size_t platform) const		{ return m_platform_cads[platform]; }
	inline CADData& GetPlatformCAD(size_t platform)					{ return m_platform_cads[platform]; }
	inline const std::vector<CADData>& GetAllPlatformCADs() const	{ return m_platform_cads; }
	inline std::vector<CADData>& GetAllPlatformCADs()				{ return m_platform_cads; }

};

