#include "PCH.h"
#include "Post.h"
#include "Log.h"


Post::Post()
	: m_mag_factor(1.0), m_writing_flags{ true, false, false, false, false, false, false, false, false, false }
{}

Post::~Post()
{}


bool Post::CreateSeabedVTK(std::string& folder, const std::array<double, 2>& x, const std::array<double, 2>& y, const double& depth)
{
	std::ofstream vtk_file(folder + "seabed.vtk", std::ios::out | std::ios::binary);
	if (!vtk_file)
	{
		Log::SetWarning("\n  GIRAFFE |> Post files: Seabed surface VTK file could not be created. Using Giraffe 'ContactSurfaces' instead.");
		return false;
	}

	//Comment
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

bool Post::CreateWaterVTK(std::string& folder, const std::array<double, 2>& x, const std::array<double, 2>& y)
{
	std::ofstream vtk_file(folder + "water.vtk", std::ios::out | std::ios::binary);
	if (!vtk_file)
	{
		Log::SetWarning("\n  GIRAFFE |> Post files: Water surface VTK file could not be created.");
		return false;
	}

	//Comment
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

void Post::SetMagFactor(double mag_factor)
{
	m_mag_factor = mag_factor;
}

void Post::SetAllCADs(const std::vector<CADData>& cad_vector)
{
	m_cad_vector = cad_vector;
}

void Post::SetAllCADs(std::vector<CADData>&& cad_vector)
{
	m_cad_vector = std::move(cad_vector);
}

void Post::SetFlags(WritingFlags&& flags)
{
	this->m_writing_flags = flags;
}



/// 
/// Overloaded operators
/// 

std::ostream& operator<<(std::ostream& out, const Post* obj)
{
	out << "\tMagFactor " << obj->m_mag_factor 
		<< obj->m_writing_flags << '\n';

	return out;
}