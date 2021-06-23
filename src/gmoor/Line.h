#pragma once
#include "LineSegment.h"
#include "TouchdownZone.h"

class Line
{
public:
	Line();
	Line(Line&& other) noexcept;
	Line(const Line& other) = default;
	~Line();

	//============================================================================

	//Reads input file
	bool Read(FILE *f);


	//Get functions
	const unsigned int GetNumber() const;
	
	//============================================================================

					/*--------
					|Variables|
					---------*/

	//Line ID
	unsigned int number;
	
	//Keypoints ID
	unsigned int keypoint_A; //anchor or fairlead
	unsigned int keypoint_B; //fairlead
	
	//Coordinate system number
	unsigned int cs;
	
	//Vessel ID number
	unsigned int vessel;
	
	//Extremity nodes
	unsigned int node_A;		//anchor or fairlead	
	unsigned int node_B;		//fairlead
	
	//Number of total nodes
	unsigned int tot_nodes;

	//Nodesets of extremity nodes
	unsigned int nodeset_A;		//anchor or fairlead	
	unsigned int nodeset_B;		//fairlead

	//Line total length
	double total_length;

	//Boolean to indicate if the line has an anchor
	bool hasAnchor;

	//Boolean to indicate if the line is shared between more than one vessel
	bool isShared;

	//Segment set number (if exist, must be different than zero)
	size_t segment_set;
	bool usingSegmentSet;

	//============================================================================

	/*--------
	Containers
	--------*/

	//Vector containing mooring line segments
	std::vector <LineSegment> segments;

	//Specific weigth os each segment
	std::vector<double> gamma_s;

	//Global number of nodes in transitions between segments
	std::vector<unsigned int> transition_nodes;

	//Geometric configuration description
	std::string configuration; 

	//Container with vessel IDs (if is a shared line - no anchor)
	std::vector<unsigned int> vesselIDs;


	//============================================================================

	/*-----------------------
	Touchdown zone parameters
	------------------------*/
	
	//Pointers to TDZ object
	std::unique_ptr<TouchdownZone> tdz;
	
	//How smallest is the TDP element
	double percent;
	//length of the segment before the TDP (in the anchor direction)
	double anc_tdp;
	//length of the segment after the TDP (in the fairlead direction)
	double tdp_fair;

	//============================================================================

	/*------------------
	Overloaded operators
	-------------------*/

	friend bool operator<(const Line& line1, const Line& line2);
	friend bool operator>(const Line& line1, const Line& line2);
	friend bool operator!=(const Line& line1, const Line& line2);
	friend bool operator==(const Line& line1, const Line& line2);
	friend bool operator!=(const Line& line1, const unsigned int& line2);
	friend bool operator==(const Line& line1, const unsigned int& line2);
	Line& operator=(Line&& other) noexcept;
	Line& operator=(const Line& other) = default;
};
