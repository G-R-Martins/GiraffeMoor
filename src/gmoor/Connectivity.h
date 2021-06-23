#pragma once
#include "Cylinder.h"

class Connectivity
{
public:
	Connectivity();
	~Connectivity();

	struct CylinderConnectivity
	{
		//Node ID
		unsigned int ID = 0;

		//Specification of the platform node
		  //Must be "first", "middle" or "last"
		std::string specification;
	};

	//==========================================================================================================================
	
					/*--------
					|Functions|
					---------*/
	
	//Reads input file
	bool Read(FILE *f);	

	//For loop using lambda function
	void ForEachLambda(std::vector<CylinderConnectivity>& NodesVec, const std::function<void(CylinderConnectivity)>& func);

	/*-------------------
	Accesing private data
	--------------------*/

	//Returns the pilot node specification
	const std::string& GetPilotSpecification() const;

	//Returns the pilot node ID
	unsigned int GetPilotID() const;

	//Returns the node specification
	const std::string& GetNodeSpecification(const unsigned int& node) const;

	//Returns the connectivity label
	const std::string& GetLabel() const;
	
	//Returns the node ID
	unsigned int GetNodeID(const unsigned int& node) const;

	//Push node back in the vector of the nodeset
	void PushNodeBack(std::vector<unsigned int>& nodes_list, const unsigned int& plat_num);


private:
	//==========================================================================================================================

					/*-------
					Variables
					--------*/

	//Pilot node
	CylinderConnectivity pilot;

	//Vector with nodes conected to pilot node
	std::vector<CylinderConnectivity> connectivity_nodes;

	//String to be used as a comment to node set and special contraint
	std::string label;
};

