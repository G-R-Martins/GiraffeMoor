#pragma once
#include "SineWaveDisplacement.h"
#include "Line.h"


class Vessel
{
public:
	Vessel();
	~Vessel();
	
	//============================================================================

					/*--------
					|Variables|
					---------*/

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
		// [ J11, J22, J33, J12, J13, J23 ]
	std::array <double, 6> inertiaTensor;


	/* ---------------------------------------------
	 Container with nodes to couple vessel and lines 
	 ----------------------------------------------*/
	
	std::unordered_set<unsigned int> nodes_rigid_nodeset;

	//============================================================================

					/*--------
					|Functions|
					---------*/

	//Reads GiraffeMoor file
	bool Read(FILE* f);


	/*------------------
	Overloaded operators
	-------------------*/

	friend bool operator<(Vessel& vessel1, Vessel& vessel2);
	friend bool operator>(Vessel& vessel1, Vessel& vessel2);
	friend bool operator!=(Vessel& vessel1, Vessel& vessel2);
	friend bool operator==(Vessel& vessel1, Vessel& vessel2);

};

