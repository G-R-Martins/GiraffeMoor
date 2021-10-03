#pragma once


class Vessel
{
private:

	// Vessel number ID
	size_t m_number;

	// Keypoint ID
	unsigned int m_keypoint;

	// Vessel node number
	unsigned int m_node;

	// Vessel node set ID
	unsigned int m_nodeset;
	
	// Vessel node set ID
	unsigned int m_rigid_nodeset;

	// Vessel element number
	unsigned int m_element;

	// Concentrated mass
	float m_mass;
	
	// Inertia tensor
	/// [ J11, J22, J33, J12, J13, J23 ]
	std::array<float, 6> m_inertia_tensor;

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
	
	void SetIDNumber(size_t number);
	void SetKeypoint(unsigned int keypoint);
	void SetNode(unsigned int node);
	void SetNodeset(unsigned int nodeset);
	void SetRigidNodeset(unsigned int rigid_nodeset);
	void SetElement(unsigned int element);
	void SetMass(float mass);
	void SetInertiaTensor(const std::array<float, 6>& inertia_tensor);
	void SetNodesRigidNodeset(const std::unordered_set<unsigned int>& nodes_rigid_nodeset);


	///
	/// GETTERS
	///
	
	inline size_t GetNumber() const				{ return this->m_number; }
	inline unsigned int GetKeypoint() const		{ return this->m_keypoint; }
	inline unsigned int GetNode() const			{ return this->m_node; }
	inline unsigned int GetNodeset() const		{ return this->m_nodeset; }
	inline unsigned int GetRigidNodeset() const	{ return this->m_rigid_nodeset; }
	inline unsigned int GetElement() const		{ return this->m_element; }
	inline float GetMass() const				{ return this->m_mass; }

	inline std::array<float, 6> const& GetInertiaTensor() const					{ return this->m_inertia_tensor; }
	inline std::unordered_set<unsigned int> const& GetNodesRigidNodeset() const { return this->m_nodes_rigid_nodeset; }
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

