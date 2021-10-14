#pragma once
#include "Vessel.h"
#include "Cylinder.h"
#include "Connectivity.h"
#include "ConcentratedMass.h"

#include "Line.h"
#include "SegmentProperty.h"

class Platform
{
protected:

	//============================================================================
	
					/*--------
					|Variables|
					---------*/

	//Platform ID
	unsigned int number;

	//First node
	mutable unsigned int node0;

	//Number of total nodes
	unsigned int tot_nodes;

	//Number of connections with the vessel pilot node
	unsigned int vessel_connections;

	//Number of the vessel of the platform
	unsigned int vessel_ID;
	
	/*------------------
	Containers with data
	-------------------*/

	//Container with cylinders
	std::vector <Cylinder> cylinders_container;

	//Container with connectivity data
	std::deque <Connectivity> connectivity_container;
	
	//Container with concentrated mass data
	std::deque <ConcentratedMass> concentrated_mass_container;
	

public:

	Platform();
	~Platform();

	//============================================================================
	
					/*--------
					|Functions|
					---------*/

	//Reads input file
	bool Read(FILE *f);

	//Generates rigid body elements from concentrated mass
	bool GenerateRigidBodyElements(size_t element, unsigned int &nodeset, unsigned int &rb_data, unsigned int &special_constraint, unsigned int &nodal_constraint) const;
	
	//Generates node sets, rigid node sets 
	bool GenerateNodeSetsSpecialConstraints(unsigned int &nodeset, unsigned int &nodal_constraint, unsigned int &special_constraint);

	//Generates fairleads nodal constraints and rigid node sets
	bool FairleadsNodalConstraintsNodeSets(unsigned int &nodeset, unsigned int &nodal_constraint, const int& max_fairleads) const;
	
	//Adds a vessel connection (it is updated during "Connectivity" reading)
	void AddVesselConnection();

	//Generates vessel nodal constraint
	bool VesselNodalConstraint(unsigned int &nodeset, unsigned int &nodal_constraint);

	//Generates vessel rigid node set(s)
	bool VesselRigidNodeset(unsigned int& nodeset, unsigned int& special_constraint, const std::vector<Vessel>& vessel_vector);

	//Generates fairleads connections (same displacement)
	bool FairleadsConnections(unsigned int& special_constraint, const std::vector<Line>& line_vector) const;

	//Generates CS, nodes and elements (except rigid bodies)
	bool GenerateCSNodesElements(unsigned int& node, unsigned int& element, unsigned int& CoordSystem, const std::vector<SegmentProperty>& segment_property_vector);
	
	//Set first node
	void SetPlatformFirstNode(const unsigned int& node) const;

	//Get number of a specific node of a specific cylinder
	enum /*class*/ NodeSpecification /*: int*/
	{
		First = 0,
		Middle,
		Last
	};
	unsigned int GetSpecificNode(const unsigned int& cylinderID, const NodeSpecification& specification) const;

	//Get the number of the vessel
	unsigned int GetVesselNumber();

	//============================================================================

	/*------------------
	Overloaded operators
	-------------------*/

	friend bool operator<(Platform& plat1, Platform& plat2);
	friend bool operator>(Platform& plat1, Platform& plat2);
	friend bool operator!=(Platform& plat1, Platform& plat2);
	friend bool operator==(Platform& plat1, Platform& plat2);
};
