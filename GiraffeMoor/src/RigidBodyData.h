#pragma once

class RigidBodyData
{
public:
	RigidBodyData();
	~RigidBodyData();

	//Writes Giraffe file
	void WriteGiraffeModelFile(FILE *f) const;
	
	//ID
	unsigned int number;
	
	//Mass
	double mass;
	
	//Inertia tensor 
	std::array<double, 6> J_G;
	
	//Barycenter position
	std::array<double, 3> G;
	
	//ID of the CAD used to render the rigid body
	/// elements of CADData stored in Post::cads_vector 
	size_t cad;

	//Comment
	std::string comment;
};

