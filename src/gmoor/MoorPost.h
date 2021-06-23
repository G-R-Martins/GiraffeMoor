#pragma once
#include "CADData.h"

class MoorPost
{
public:
	MoorPost();
	~MoorPost() = default;
	
	//============================================================================

	/*-------
	Functions
	--------*/
	//Reads input file
	bool Read(FILE *f);

	
	//============================================================================

	/*-------
	Variables
	--------*/


	struct WritingOpt
	{
		bool mesh_flag{ true }, renderMesh_flag{ false }, rigidContactSurfaces_flag{ false },
			flexibleContactSurfaces_flag{ false }, constraints_flag{ false }, forces_flag{ false },
			specialConstraints_flag{ false }, contactForces_flag{ false }, renderParticles_flag, renderRigidBodies_flag{ false };
	} write;

	std::vector<CADData> platform_cads;

};

