#include "PCH.h"
#include "Post.h"
#include "Log.h"


Post::Post()
	: mag_factor(1.0), write{ false, false, false, false, false, false, false, false, false, false }
	/*WriteMesh_flag(true), WriteRenderMesh_flag(false), WriteRigidContactSurfaces_flag(false), WriteFlexibleContactSurfaces_flag(false),
	WriteConstraints_flag(false), WriteSpecialConstraints_flag(false), WriteForces_flag(false), WriteContactForces_flag(false),
	WriteRenderRigidBodies_flag(false), WriteRenderParticles_flag(false)*/
{}

Post::~Post()
{}

void Post::WriteGiraffeModelFile(std::ostream& fout) const
{
	fout << "\tMagFactor " << mag_factor <<
		std::setprecision(6) <<
		"\n\tWriteMesh " << write.mesh_flag <<
		"\n\tWriteRenderMesh " << write.renderMesh_flag <<
		"\n\tWriteRigidContactSurfaces " << write.rigidContactSurfaces_flag <<
		"\n\tWriteFlexibleContactSurfaces " << write.flexibleContactSurfaces_flag <<
		"\n\tWriteForces " << write.forces_flag <<
		"\n\tWriteConstraints " << write.constraints_flag <<
		"\n\tWriteSpecialConstraints " << write.specialConstraints_flag <<
		"\n\tWriteContactForces " << write.contactForces_flag <<
		"\n\tWriteRenderRigidBodies " << write.renderRigidBodies_flag <<
		"\n\tWriteRenderParticles " << write.renderParticles_flag << "\n";
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

