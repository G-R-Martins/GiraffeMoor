#pragma once


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

	bool WriteMesh_flag;
	bool WriteRenderMesh_flag;
	bool WriteRigidContactSurfaces_flag;
	bool WriteFlexibleContactSurfaces_flag;
	bool WriteConstraints_flag;
	bool WriteForces_flag;
	bool WriteSpecialConstraints_flag;
	bool WriteContactForces_flag;
	bool WriteRenderParticles_flag;
	bool WriteRenderRigidBodies_flag;

	//Magnification factor of displacements
	double mag_factor;
};

