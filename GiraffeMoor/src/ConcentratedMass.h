#pragma once


class ConcentratedMass
{
private:

					/*--------
					|Variables|
					---------*/

	//Cylinder ID
	unsigned int ID_cylinder;

	//Local node ID
	unsigned int local_node;

	//Global node ID
	unsigned int global_node;

	//Concentrated mass
	double concentrated_mass;
	
	//Label used as comment to GIRAFFE Rigid Body Data and Element
	std::string label;

	//==============================================================================

public:
	ConcentratedMass();
	~ConcentratedMass();

					/*--------
					|Functions|
					---------*/

	//Reads input file
	bool Read(FILE *f);

	/*-------------------
	Setting private data
	--------------------*/

	void SetGlobalNode(const unsigned int& node);

	/*-------------------
	Accesing private data
	--------------------*/

	unsigned int GetCylinderID() const;
	unsigned int GetLocalNodeID() const;
	unsigned int GetGlobalNodeID() const;
	double GetMass() const;
	const std::string& GetLabel() const;
};

