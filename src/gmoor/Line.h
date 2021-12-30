#pragma once
#include "LineSegment.h"

class Line
{
private:
	unsigned int m_id;
	std::string m_configuration; //Catenary, taut...

	bool m_has_anchor;
	bool m_is_shared;
	bool m_using_segment_set;

	unsigned int m_keypointA_id; //Anchor or fairlead
	unsigned int m_keypointB_id; //Fairlead
	std::vector<unsigned int> m_vessel_id;
	unsigned int m_segment_set_id;
	unsigned int m_seg_TDP_id;

	unsigned int m_nodeA_id;  //Global number
	unsigned int m_nodeB_id;  //Global number 
	unsigned int m_tot_nodes;

	unsigned int m_nodesetA_id;  //Anchor or fairlead	
	unsigned int m_nodesetB_id;  //Fairlead

	unsigned int m_coordinate_system_id;
	double m_total_length;


	std::vector<LineSegment> m_segments;
	std::vector<unsigned int> m_transition_nodes; //Global number

public:
	Line();
	Line(Line&& other) noexcept;
	Line(const Line& other) = default;
	~Line();


	void IncrementTotNodes(unsigned int add_nodes);
	void AddLength(double length);
	void AddTransitionNode(unsigned int node);
	void AddSegment(const LineSegment& seg);


	///
	/// SETTERS
	/// 

	void SetIDNumber(unsigned int id);
	void SetConfiguration(const std::string& configuration);
	void SetAnchorOpt(bool has_anchor);
	void SetSharedOpt(bool is_shared);
	void SetSegmentSetOpt(bool using_segment_set);
	void SetKeypointA(unsigned int keypoint_A);
	void SetKeypointB(unsigned int keypoint_B);
	void SetVesselID(unsigned int vessel_id);
	void SetSegmentSet(unsigned int segment_set);
	void SetNodeA(unsigned int node_A);
	void SetNodeB(unsigned int node_B);
	void SetTotalNumNodes(unsigned int tot_nodes);
	void SetNodesetA(unsigned int nodeset_A);
	void SetNodesetB(unsigned int nodeset_B);
	void SetCoordinateSystem(unsigned int coordinate_system);
	void SetTotalLength(double total_length);
	void SetSegments(std::vector<LineSegment>& segments);
	void SetTDPSegment(unsigned int seg);


	///
	/// GETTERS
	/// 

	inline unsigned int GetNumber() const										{ return m_id; }
	inline const std::string& GetConfiguration() const					{ return m_configuration; }
	inline bool GetSegmentSetOpt() const								{ return m_using_segment_set; }
	inline unsigned int GetKeypointA() const									{ return m_keypointA_id; }
	inline unsigned int GetKeypointB() const									{ return m_keypointB_id; }
	inline unsigned int GetVesselAt(unsigned int keypoint) const					{ return m_vessel_id[keypoint]; }
	inline const std::vector<unsigned int>& GetVesselID() const				{ return m_vessel_id; }
	inline std::vector<unsigned int>& GetVesselID()							{ return m_vessel_id; }
	inline unsigned int GetSegmentSet() const									{ return m_segment_set_id; }
	inline unsigned int GetNodeA() const										{ return m_nodeA_id; }
	inline unsigned int GetNodeB() const										{ return m_nodeB_id; }
	inline unsigned int GetTotalNumNodes() const								{ return m_tot_nodes; }
	inline unsigned int GetNodesetA() const									{ return m_nodesetA_id; }
	inline unsigned int GetNodesetB() const									{ return m_nodesetB_id; }
	inline unsigned int GetCoordinateSystem() const							{ return m_coordinate_system_id; }
	inline double GetTotalLength() const								{ return m_total_length; }
	inline const LineSegment& GetSegment(unsigned int seg) const				{ return m_segments[seg]; }
	inline LineSegment& GetSegment(unsigned int seg)							{ return m_segments[seg]; }
	inline const std::vector<LineSegment>& GetAllSegments() const		{ return m_segments; }
	inline std::vector<LineSegment>& GetAllSegments()					{ return m_segments; }
	inline unsigned int GetTransitionNode(unsigned int node) const					{ return m_transition_nodes[node]; }
	inline unsigned int GetTransitionNode(unsigned int node)						{ return m_transition_nodes[node]; }
	inline const std::vector<unsigned int>& GetAllTransitionNode()const { return m_transition_nodes; }
	inline std::vector<unsigned int>& GetAllTransitionNode()			{ return m_transition_nodes; }

	inline unsigned int GetTDPSegment() const									{ return m_seg_TDP_id;}
	inline unsigned int GetTDPSegment()										{ return m_seg_TDP_id;}
	inline const unsigned int Line::GetNSegments() const						{ return (unsigned int)m_segments.size(); }

	// Getter-ish
	inline bool HasAnchor() const									{ return m_has_anchor; }
	inline bool IsShared() const									{ return m_is_shared; }
	
	
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
