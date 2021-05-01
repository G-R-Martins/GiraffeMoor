#include "PCH.h"
#include "Post.h"
#include "Log.h"



Post::Post()
	: WriteMesh_flag(true), WriteRenderMesh_flag(false), WriteRigidContactSurfaces_flag(false), WriteFlexibleContactSurfaces_flag(false),
	WriteConstraints_flag(false), WriteSpecialConstraints_flag(false), WriteForces_flag(false), WriteContactForces_flag(false),
	WriteRenderRigidBodies_flag(false), WriteRenderParticles_flag(false), mag_factor(1.0)
{}

Post::~Post()
{}

void Post::WriteGiraffeModelFile(FILE *f) const
{
	fprintf(f, "\tMagFactor\t%.6f\n\tWriteMesh\t%d\n\tWriteRenderMesh\t%d\n\tWriteRigidContactSurfaces\t%d\n\tWriteFlexibleContactSurfaces\t%d\n\tWriteForces\t%d\n\tWriteConstraints\t%d\n\tWriteSpecialConstraints\t%d\n\tWriteContactForces\t%d\n\tWriteRenderRigidBodies\t%d\n\tWriteRenderParticles\t%d\n", 
		mag_factor, WriteMesh_flag, WriteRenderMesh_flag, WriteRigidContactSurfaces_flag, WriteFlexibleContactSurfaces_flag, WriteForces_flag, WriteConstraints_flag, WriteSpecialConstraints_flag, WriteContactForces_flag, WriteRenderRigidBodies_flag, WriteRenderParticles_flag);
}

bool Post::CreateSeabedVTK(std::string folder, const std::array<double, 2>& x, const std::array<double, 2>& y, const double& depth)
{
	std::ofstream vtk_file(folder + "seabed.vtk", std::ios::out | std::ios::binary);
	if (!vtk_file)
	{
		Log::AddWarning("\n   + Seabed vtk file could not be created. Using Giraffe 'ContactSurfaces' instead.");
		return false;
	}

	//Comment
	//vtk_file << "'''\n\tSeabed VTK DataFile\n\tCreated by GiraffeMoor v" << version << "\n'''\n" << std::endl;
	vtk_file << "# vtk DataFile Version 3.0\n";

	//Header
	vtk_file << "misc file\nASCII\nDATASET POLYDATA\nPOINTS 4 float\n";
	
	//Coordinates
	vtk_file << x[1] << "\t" << y[1] << "\t" << depth << "\n";
	vtk_file << x[1] << "\t" << y[0] << "\t" << depth << "\n";
	vtk_file << x[0] << "\t" << y[0] << "\t" << depth << "\n";
	vtk_file << x[0] << "\t" << y[1] << "\t" << depth << "\n";

	//Connectivity
	vtk_file << "POLYGONS 1 5 \n4 0 1 2 3\n";

	return true;
}	

bool Post::CreateWaterVTK(std::string folder, const std::array<double, 2>& x, const std::array<double, 2>& y)
{
	std::ofstream vtk_file(folder + "water.vtk", std::ios::out | std::ios::binary);
	if (!vtk_file)
	{
		Log::AddWarning("\n   + Water surface vtk file could not be created");
		return false;
	}

	//Comment
	//vtk_file << "'''\n\tWater surface VTK DataFile\n\tCreated by GiraffeMoor v" << version << "\n'''\n" << std::endl;
	vtk_file << "# vtk DataFile Version 3.0\n";

	//Header
	vtk_file << "misc file\nASCII\nDATASET POLYDATA\nPOINTS 4 float\n";

	//Coordinates
	vtk_file << x[1] << "\t" << y[1] << "\t0.0\n";	// +x  :  +y
	vtk_file << x[1] << "\t" << y[0] << "\t0.0\n";	// +x  :  -y
	vtk_file << x[0] << "\t" << y[0] << "\t0.0\n";	// -x  :  -y
	vtk_file << x[0] << "\t" << y[1] << "\t0.0\n";	// -x  :  +y

	//Connectivity
	vtk_file << "POLYGONS 1 5 \n4 0 1 2 3\n";

	return true;
}

