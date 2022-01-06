#pragma once

class RigidBodyData
{
private:
	unsigned int m_id;
	double m_mass;
	std::array<double, 6> m_J_G;  //Inertia tensor 
	std::array<double, 3> m_G;  //Barycenter position
	
	//ID of the CAD used to render the rigid body
	/// elements of CADData stored in Post::cads_vector 
	unsigned int m_cad_id;

	//Comment
	std::string m_comment;

public:
	RigidBodyData();
	RigidBodyData(unsigned int id, double mass, const std::array<double, 6>& J_G, 
		const std::array<double, 3>& G, unsigned int cad_id = 0, const std::string& comment = "\0");
	~RigidBodyData();
	

	/// 
	/// Overloaded operators
	/// 

	friend std::ostream& operator<<(std::ostream& out, const RigidBodyData& obj);
};

