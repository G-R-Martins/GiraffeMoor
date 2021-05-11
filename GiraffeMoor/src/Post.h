#pragma once
#include "CADData.h"


class Post
{
public:
	Post();
	~Post();

	//============================================================================

					/*-------
					Functions
					--------*/

	//Writes Giraffe file
	void WriteGiraffeModelFile(FILE *f) const;

	// Creates seabed VTK file

	bool CreateSeabedVTK(std::string folder, const std::array<double, 2>& x, const std::array<double, 2>& y, const double& depth);
	
	//Creates water surface VTK file
	bool CreateWaterVTK(std::string folder, const std::array<double, 2>& x, const std::array<double, 2>& y);


	//============================================================================
	
					/*-------
					Variables
					--------*/
	//Magnification factor of displacements
	double mag_factor;

	struct WritingOpt
	{
		bool mesh_flag;
		bool renderMesh_flag;
		bool rigidContactSurfaces_flag;
		bool flexibleContactSurfaces_flag;
		bool constraints_flag;
		bool forces_flag;
		bool specialConstraints_flag;
		bool contactForces_flag;
		bool renderParticles_flag;
		bool renderRigidBodies_flag;
	} write;

	//Vector with CADs for post proessing
	std::vector<CADData> cads_vector;
};

