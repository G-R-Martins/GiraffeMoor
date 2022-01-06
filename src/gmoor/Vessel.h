#pragma once


class Vessel
{
private:

	// Vessel number ID
	unsigned int m_id;

	// Keypoint ID
	unsigned int m_keypoint_id;

	// Vessel node number
	unsigned int m_node_id;

	// Vessel node set ID
	unsigned int m_nodeset_id;
	
	// Vessel node set ID
	unsigned int m_rigid_nodeset_id;

	// Vessel element number
	unsigned int m_element_id;

	// Concentrated mass
	double m_mass;
	
	// Inertia tensor
	/// [ J11, J22, J33, J12, J13, J23 ]
	std::array<double, 6> m_inertia_tensor;

	// Contains the nodes to couple vessel and lines 
	std::unordered_set<unsigned int> m_nodes_rigid_nodeset;

	//============================================================================

public:
	Vessel();
	~Vessel();

	//Add node to the rigid nodeset
	void AddNode2RigidNodeset(unsigned int node);

	
	///
	/// SETTERS
	///
	
	void SetIDNumber(unsigned int id);
	void SetKeypoint(unsigned int keypoint_id);
	void SetNode(unsigned int node_id);
	void SetNodeset(unsigned int nodeset_id);
	void SetRigidNodeset(unsigned int rigid_nodeset_id);
	void SetElement(unsigned int element_id);
	void SetMass(double mass);
	void SetInertiaTensor(const std::array<double, 6>& inertia_tensor);
	void SetNodesRigidNodeset(const std::unordered_set<unsigned int>& nodes_rigid_nodeset);


	///
	/// GETTERS
	///
	
	inline unsigned int GetNumber() const			{ return this->m_id; }
	inline unsigned int GetKeypoint() const		{ return this->m_keypoint_id; }
	inline unsigned int GetNode() const			{ return this->m_node_id; }
	inline unsigned int GetNodeset() const		{ return this->m_nodeset_id; }
	inline unsigned int GetRigidNodeset() const	{ return this->m_rigid_nodeset_id; }
	inline unsigned int GetElement() const		{ return this->m_element_id; }
	inline double GetMass() const			{ return this->m_mass; }

	inline std::array<double, 6> const& GetInertiaTensor() const			{ return this->m_inertia_tensor; }
	inline std::unordered_set<unsigned int> const& GetNodesRigidNodeset() const	{ return this->m_nodes_rigid_nodeset; }
	inline std::unordered_set<unsigned int>& GetNodesRigidNodeset()				{ return this->m_nodes_rigid_nodeset; }


	//============================================================================

	/*------------------
	Overloaded operators
	-------------------*/

	friend bool operator<(Vessel& vessel1, Vessel& vessel2);
	friend bool operator>(Vessel& vessel1, Vessel& vessel2);
	friend bool operator!=(Vessel& vessel1, Vessel& vessel2);
	friend bool operator==(Vessel& vessel1, Vessel& vessel2);

};

