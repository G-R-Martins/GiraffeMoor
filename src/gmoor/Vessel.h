#pragma once
#include "SineWaveDisplacement.h"
#include "Line.h"


class Vessel
{
	//Vessel number
	unsigned int number;

	//Keypoint ID
	unsigned int keypoint;

	//Vessel node number
	unsigned int node;

	//Vessel node set ID
	unsigned int nodeset;
	
	//Vessel node set ID
	unsigned int rigid_nodeset;

	//Vessel element number
	unsigned int element;


	/*-------------------
	Equivalent properties 
	--------------------*/

	//Concentrated mass
	float mass;
	
	//Inertia tensor
	/// [ J11, J22, J33, J12, J13, J23 ]
	std::array<double, 6> inertiaTensor;


	//Container with nodes to couple vessel and lines 
	std::unordered_set<unsigned int> nodes_rigid_nodeset;

	//============================================================================

public:
	Vessel();
	~Vessel();

					/*--------
					|Functions|
					---------*/

	//Reads GiraffeMoor file
	bool Read(FILE* f);

	//Add node to the rigid nodeset
	void AddNode2RigidNodeset(unsigned int n);

	///
	/// Set functions
	///
	void SetNumber(unsigned int num);
	void SetKeypoint(unsigned int kp);
	void SetNode(unsigned int n);
	void SetNodeset(unsigned int ns);
	void SetRigidNodeset(unsigned int rigid_ns);
	void SetElement(unsigned int elem);
	void SetMass(float m);
	void SetInertiaTensor(const std::array<double, 6>& tensor);
	void SetNodesRigidNodeset(const std::unordered_set<unsigned int>& nodes);

	///
	/// GSet functions
	///
	unsigned int GetNumber() const;
	unsigned int GetKeypoint() const;
	unsigned int GetNode() const;
	unsigned int GetNodeset() const;
	unsigned int GetRigidNodeset() const;
	unsigned int GetElement() const;
	float GetMass() const;

	std::array<double, 6> const& GetInertiaTensor() const;
	std::unordered_set<unsigned int> const& GetNodesRigidNodeset() const;
	std::unordered_set<unsigned int>& GetNodesRigidNodeset();


	//============================================================================

	/*------------------
	Overloaded operators
	-------------------*/

	friend bool operator<(Vessel& vessel1, Vessel& vessel2);
	friend bool operator>(Vessel& vessel1, Vessel& vessel2);
	friend bool operator!=(Vessel& vessel1, Vessel& vessel2);
	friend bool operator==(Vessel& vessel1, Vessel& vessel2);

};

