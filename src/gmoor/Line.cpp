#include "PCH.h"
#include "Line.h"


Line::Line()
	: m_id(0), m_configuration("\0"),
	m_has_anchor(true), m_is_shared(false), m_using_segment_set(false),
	m_keypointA_id(0), m_keypointB_id(0), m_vessel_id({ 0, 0 }),
	m_segment_set_id(0), m_seg_TDP_id(0),
	m_nodeA_id(0), m_nodeB_id(0), m_tot_nodes(0),
	m_nodesetA_id(0), m_nodesetB_id(0),
	m_coordinate_system_id(0), m_total_length(0.0)
{
	m_segments.reserve(4);
	m_transition_nodes.reserve(2);
}

Line::~Line()
{}

Line::Line(Line&& other) noexcept
	: m_id(std::move(other.m_id)), m_configuration("\0"),
	m_has_anchor(std::move(other.m_has_anchor)), m_is_shared(std::move(other.m_is_shared)), m_using_segment_set(std::move(other.m_using_segment_set)), 
	m_keypointA_id(std::move(other.m_keypointA_id)), m_keypointB_id(std::move(other.m_keypointB_id)), m_vessel_id(std::move(other.m_vessel_id)),
	m_segment_set_id(std::move(other.m_segment_set_id)), m_seg_TDP_id(std::move(other.m_seg_TDP_id)),
	m_nodeA_id(std::move(other.m_nodeA_id)), m_nodeB_id(std::move(other.m_nodeB_id)), m_tot_nodes(std::move(other.m_tot_nodes)),
	m_nodesetA_id(std::move(other.m_nodesetA_id)), m_nodesetB_id(std::move(other.m_nodesetB_id)),
	m_coordinate_system_id(std::move(other.m_coordinate_system_id)), m_total_length(std::move(other.m_total_length)),
	m_segments(std::move(other.m_segments)), m_transition_nodes(std::move(other.m_transition_nodes))
{}

Line& Line::operator=(Line&& other) noexcept
{
	//if (tdz) delete tdz;
	m_id = std::move(other.m_id);
	m_keypointA_id = std::move(other.m_keypointA_id);
	m_keypointB_id = std::move(other.m_keypointB_id);
	m_coordinate_system_id = std::move(other.m_coordinate_system_id);
	m_vessel_id = std::move(other.m_vessel_id);
	m_nodeA_id = std::move(other.m_nodeA_id);
	m_nodeB_id = std::move(other.m_nodeB_id);
	m_tot_nodes = std::move(other.m_tot_nodes);
	m_nodesetA_id = std::move(other.m_nodesetA_id);
	m_nodesetB_id = std::move(other.m_nodesetB_id);
	m_total_length = std::move(other.m_total_length);
	m_has_anchor = std::move(other.m_has_anchor);
	m_is_shared = std::move(other.m_is_shared);
	m_segment_set_id = std::move(other.m_segment_set_id);
	m_using_segment_set = std::move(other.m_using_segment_set);

	m_segments = std::move(other.m_segments);
	m_transition_nodes = std::move(other.m_transition_nodes);
	m_configuration[0] = '\0';


	return *this;
}


/* Overloaded operators */
bool operator< (const Line& line1, const Line& line2)
{
	//Both lines with vessels identified and different between them
	// -> uses the line numbers to compare
	if (line1.m_vessel_id[0] != 0 && line2.m_vessel_id[0] != 0 && line1.m_vessel_id == line2.m_vessel_id)
	{
		return line1.m_id < line2.m_id;
	}
	//Otherwise -> uses the vessel number to compare
	else
		return line1.m_vessel_id < line2.m_vessel_id;
}
bool operator> (const Line& line1, const Line& line2)
{
	return !(line1 < line2);
}

bool operator== (const Line& line1, const Line& line2)
{
			/*			same ID number		  ||		same extremeties keypoints*/
	return ( line1.m_id == line2.m_id ||
		( line1.m_keypointA_id == line2.m_keypointA_id && line1.m_keypointB_id == line2.m_keypointB_id) );
}
bool operator!= (const Line& line1, const Line& line2)
{
	return !( line1 == line2 );
}

//Comparing line with an ID number
bool operator== (const Line& line1, const unsigned int& line2)
{
	return line1.m_vessel_id[0] == line2;
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

void Line::SetIDNumber(unsigned int id)
{
	m_id = id;
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
void Line::SetKeypointA(unsigned int keypoint_A)
{
	m_keypointA_id = keypoint_A;
}
void Line::SetKeypointB(unsigned int keypoint_B)
{
	m_keypointB_id = keypoint_B;
}
void Line::SetVesselID(unsigned int vessel_id)
{
	m_vessel_id[0] = vessel_id;
}
void Line::SetSegmentSet(unsigned int segment_set)
{
	m_segment_set_id = segment_set;
	m_using_segment_set = true;
}
void Line::SetNodeA(unsigned int node_A)
{
	m_nodeA_id = node_A;
}
void Line::SetNodeB(unsigned int node_B)
{
	m_nodeB_id = node_B;
}
void Line::SetTotalNumNodes(unsigned int tot_nodes)
{
	m_tot_nodes = tot_nodes;
}
void Line::SetNodesetA(unsigned int nodeset_A)
{
	m_nodesetA_id = nodeset_A;
}
void Line::SetNodesetB(unsigned int nodeset_B)
{
	m_nodesetB_id = nodeset_B;
}
void Line::SetCoordinateSystem(unsigned int coordinate_system)
{
	m_coordinate_system_id = coordinate_system;
}
void Line::SetTotalLength(double total_length)
{
	m_total_length = total_length;
}
void Line::SetSegments(std::vector<LineSegment>& segments)
{
	m_segments = segments;
}
void Line::SetTDPSegment(unsigned int seg)
{
	this->m_seg_TDP_id = seg;
}
