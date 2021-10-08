#include "PCH.h"
#include "Line.h"
#include "LoopReading.h"
#include "Log.h"


Line::Line()
	: m_number(0), m_configuration("\0"),
	m_has_anchor(true), m_is_shared(false), m_using_segment_set(false),
	m_keypoint_A(0), m_keypoint_B(0), m_vesselID({ 0, 0 }),
	m_segment_set(0), m_seg_TDP(0),
	m_node_A(0), m_node_B(0), m_tot_nodes(0), 
	m_nodeset_A(0), m_nodeset_B(0),
	m_coordinate_system(0), m_total_length(0.0),
	tdz(nullptr), percent(0.0), anc_tdp(0.0), tdp_fair(0.0) 
{
	m_segments.reserve(4);
	m_transition_nodes.reserve(2);
}

Line::~Line()
{}

Line::Line(Line&& other) noexcept
	: m_number(std::move(other.m_number)), m_configuration("\0"),
	m_has_anchor(std::move(other.m_has_anchor)), m_is_shared(std::move(other.m_is_shared)), m_using_segment_set(std::move(other.m_using_segment_set)), 
	m_keypoint_A(std::move(other.m_keypoint_A)), m_keypoint_B(std::move(other.m_keypoint_B)), m_vesselID(std::move(other.m_vesselID)), 
	m_segment_set(std::move(other.m_segment_set)), m_seg_TDP(std::move(other.m_seg_TDP)),
	m_node_A(std::move(other.m_node_A)), m_node_B(std::move(other.m_node_B)), m_tot_nodes(std::move(other.m_tot_nodes)), 
	m_nodeset_A(std::move(other.m_nodeset_A)), m_nodeset_B(std::move(other.m_nodeset_B)),
	m_coordinate_system(std::move(other.m_coordinate_system)), m_total_length(std::move(other.m_total_length)), 
	m_segments(std::move(other.m_segments)), m_transition_nodes(std::move(other.m_transition_nodes)),
	//laying_direction(std::move(other.laying_direction)), tdz(std::move(other.tdz)),
	percent(std::move(other.percent)), anc_tdp(std::move(other.anc_tdp)), tdp_fair(std::move(other.tdp_fair))
{
	other.tdz = nullptr;
}

Line& Line::operator=(Line&& other) noexcept
{
	//if (tdz) delete tdz;
	m_number = std::move(other.m_number);
	m_keypoint_A = std::move(other.m_keypoint_A);
	m_keypoint_B = std::move(other.m_keypoint_B);
	m_coordinate_system = std::move(other.m_coordinate_system);
	m_vesselID = std::move(other.m_vesselID);
	m_node_A = std::move(other.m_node_A);
	m_node_B = std::move(other.m_node_B);
	m_tot_nodes = std::move(other.m_tot_nodes);
	m_nodeset_A = std::move(other.m_nodeset_A);
	m_nodeset_B = std::move(other.m_nodeset_B);
	m_total_length = std::move(other.m_total_length);
	m_has_anchor = std::move(other.m_has_anchor);
	m_is_shared = std::move(other.m_is_shared);
	m_segment_set = std::move(other.m_segment_set);
	m_using_segment_set = std::move(other.m_using_segment_set);

	m_segments = std::move(other.m_segments);
	m_transition_nodes = std::move(other.m_transition_nodes);
	m_configuration[0] = '\0';
	//tdz = std::move(other.tdz);
	percent = std::move(other.percent);
	anc_tdp = std::move(other.anc_tdp);
	tdp_fair = std::move(other.tdp_fair);


	//TDZ pointer
	other.tdz = nullptr;

	return *this;
}


/* Overloaded operators */
bool operator< (const Line& line1, const Line& line2)
{
	//Both lines with vessels identified and different between them
	// -> uses the line numbers to compare
	if (line1.m_vesselID[0] != 0 && line2.m_vesselID[0] != 0 && line1.m_vesselID == line2.m_vesselID)
	{
		return line1.m_number < line2.m_number;
	}
	//Otherwise -> uses the vessel number to compare
	else
		return line1.m_vesselID < line2.m_vesselID;
}
bool operator> (const Line& line1, const Line& line2)
{
	return !(line1 < line2);
}

bool operator== (const Line& line1, const Line& line2)
{
			/*			same ID number		  ||		same extremeties keypoints*/
	return ( line1.m_number == line2.m_number || 
		( line1.m_keypoint_A == line2.m_keypoint_A && line1.m_keypoint_B == line2.m_keypoint_B ) );
}
bool operator!= (const Line& line1, const Line& line2)
{
	return !( line1 == line2 );
}

//Comparing line with an ID number
bool operator== (const Line& line1, const unsigned int& line2)
{
	return line1.m_vesselID[0] == line2;
}
bool operator!= (const Line& line1, const unsigned int& line2)
{
	return !( line1 == line2 );
}



void Line::IncrementTotNodes(unsigned int add_nodes)
{
	this->m_tot_nodes += add_nodes;
}
void Line::AddLength(double length)
{
	this->m_total_length += length;
}
void Line::AddTransitionNode(unsigned int node)
{
	this->m_transition_nodes.push_back(node);
}
void Line::AddSegment(const LineSegment& seg)
{
	m_segments.emplace_back(seg);
}



/// 
/// SETTERS
/// 

void Line::SetIDNumber(size_t number)
{
	m_number = number;
}
void Line::SetConfiguration(const std::string& configuration)
{
	m_configuration = configuration;
}
void Line::SetAnchorOpt(bool has_anchor)
{
	m_has_anchor = has_anchor;
}
void Line::SetSharedOpt(bool is_shared)
{
	m_is_shared = is_shared;
}
void Line::SetSegmentSetOpt(bool using_segment_set)
{
	m_using_segment_set = using_segment_set;
}
void Line::SetKeypointA(size_t keypoint_A)
{
	m_keypoint_A = keypoint_A;
}
void Line::SetKeypointB(size_t keypoint_B)
{
	m_keypoint_B = keypoint_B;
}
void Line::SetVesselID(size_t vesselID)
{
	m_vesselID[0] = vesselID;
}
void Line::SetSegmentSet(size_t segment_set)
{
	m_segment_set = m_segment_set;
}
void Line::SetNodeA(unsigned int node_A)
{
	m_node_A = node_A;
}
void Line::SetNodeB(unsigned int node_B)
{
	m_node_B = node_B;
}
void Line::SetTotalNumNodes(unsigned int tot_nodes)
{
	m_tot_nodes = tot_nodes;
}
void Line::SetNodesetA(unsigned int nodeset_A)
{
	m_nodeset_A = nodeset_A;
}
void Line::SetNodesetB(unsigned int nodeset_B)
{
	m_nodeset_B = nodeset_B;
}
void Line::SetCoordinateSystem(unsigned int coordinate_system)
{
	m_coordinate_system = coordinate_system;
}
void Line::SetTotalLength(double total_length)
{
	m_total_length = total_length;
}
void Line::SetSegments(std::vector<LineSegment>& segments)
{
	m_segments = segments;
}
void Line::SetTDPSegment(size_t seg)
{
	this->m_seg_TDP = seg;
}
