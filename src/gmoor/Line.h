#pragma once
#include "LineSegment.h"
#include "TouchdownZone.h"

class Line
{
private:
	size_t m_number;
	std::string m_configuration; //Catenary, taut...

	bool m_has_anchor;
	bool m_is_shared;
	bool m_using_segment_set;

	size_t m_keypoint_A; //Anchor or fairlead
	size_t m_keypoint_B; //Fairlead
	std::vector<size_t> m_vesselID;
	size_t m_segment_set;
	size_t m_seg_TDP;

	size_t m_node_A;  //Global number
	size_t m_node_B;  //Global number 
	size_t m_tot_nodes;

	size_t m_nodeset_A;  //Anchor or fairlead	
	size_t m_nodeset_B;  //Fairlead

	size_t m_coordinate_system;
	double m_total_length;


	std::vector<LineSegment> m_segments;
	std::vector<unsigned int> m_transition_nodes; //Global number

public:
	Line();
	Line(Line&& other) noexcept;
	Line(const Line& other) = default;
	~Line();


	void IncrementTotNodes(size_t add_nodes);
	void AddLength(double length);
	void AddTransitionNode(unsigned int node);
	void AddSegment(const LineSegment& seg);


	///
	/// SETTERS
	/// 

	void SetIDNumber(size_t number);
	void SetConfiguration(const std::string& configuration);
	void SetAnchorOpt(bool has_anchor);
	void SetSharedOpt(bool is_shared);
	void SetSegmentSetOpt(bool using_segment_set);
	void SetKeypointA(size_t keypoint_A);
	void SetKeypointB(size_t keypoint_B);
	void SetVesselID(size_t vesselID);
	void SetSegmentSet(size_t segment_set);
	void SetNodeA(size_t node_A);
	void SetNodeB(size_t node_B);
	void SetTotalNumNodes(size_t tot_nodes);
	void SetNodesetA(size_t nodeset_A);
	void SetNodesetB(size_t nodeset_B);
	void SetCoordinateSystem(size_t coordinate_system);
	void SetTotalLength(double total_length);
	void SetSegments(std::vector<LineSegment>& segments);
	void SetGamma(size_t seg, double gamma_sub);
	void SetTDPSegment(size_t seg);


	///
	/// GETTERS
	/// 

	inline size_t GetNumber() const										{ return m_number; }
	inline const std::string& GetConfiguration() const					{ return m_configuration; }
	inline bool GetSegmentSetOpt() const								{ return m_using_segment_set; }
	inline size_t GetKeypointA() const									{ return m_keypoint_A; }
	inline size_t GetKeypointB() const									{ return m_keypoint_B; }
	inline size_t GetVesselAt(size_t keypoint) const					{ return m_vesselID[keypoint]; }
	inline const std::vector<size_t>& GetVesselID() const				{ return m_vesselID; }
	inline std::vector<size_t>& GetVesselID()							{ return m_vesselID; }
	inline size_t GetSegmentSet() const									{ return m_segment_set; }
	inline size_t GetNodeA() const										{ return m_node_A; }
	inline size_t GetNodeB() const										{ return m_node_B; }
	inline size_t GetTotalNumNodes() const								{ return m_tot_nodes; }
	inline size_t GetNodesetA() const									{ return m_nodeset_A; }
	inline size_t GetNodesetB() const									{ return m_nodeset_B; }
	inline size_t GetCoordinateSystem() const							{ return m_coordinate_system; }
	inline double GetTotalLength() const								{ return m_total_length; }
	inline const LineSegment& GetSegment(size_t seg) const				{ return m_segments[seg]; }
	inline LineSegment& GetSegment(size_t seg)							{ return m_segments[seg]; }
	inline const std::vector<LineSegment>& GetAllSegments() const		{ return m_segments; }
	inline std::vector<LineSegment>& GetAllSegments()					{ return m_segments; }
	inline size_t GetTransitionNode(size_t node) const					{ return m_transition_nodes[node]; }
	inline size_t GetTransitionNode(size_t node)						{ return m_transition_nodes[node]; }
	inline const std::vector<unsigned int>& GetAllTransitionNode()const { return m_transition_nodes; }
	inline std::vector<unsigned int>& GetAllTransitionNode()			{ return m_transition_nodes; }

	inline size_t GetTDPSegment() const									{ return m_seg_TDP;}
	inline size_t GetTDPSegment()										{ return m_seg_TDP;}
	inline const size_t Line::GetNSegments() const						{ return m_segments.size(); }

	// Getter-ish
	inline bool HasAnchor() const									{ return m_has_anchor; }
	inline bool IsShared() const									{ return m_is_shared; }
	
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
