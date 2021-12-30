#include "PCH.h"
#include "Node.h"

Node::Node()
	: m_id(0), m_ref_coordinates({0.,0.,0.}), m_comment("\0")
{}

Node::Node(unsigned int id, const std::array<double, 3>& m_ref_coordinates, std::string comment)
	: m_id(id), m_ref_coordinates(m_ref_coordinates), m_comment(comment)
{}

Node::~Node()
{}

void Node::SetIDNumber(unsigned int id)
{
	m_id = id;
}

void Node::SetCoordinates(const std::array<double, 3>& ref_coordinates)
{
	m_ref_coordinates = ref_coordinates;
}

void Node::SetComment(std::string comment)
{
	m_comment = comment;
}


/// 
/// Overloaded operators
/// 

std::ostream& operator<<(std::ostream& out, const Node& obj)
{
	if ( !obj.m_comment.empty() )
		out << "\t//" << obj.m_comment << "\n";

	out << "\tNode " << obj.m_id 
		<< "\t\t" << obj.m_ref_coordinates[0] << " \t" << obj.m_ref_coordinates[1] << " \t" << obj.m_ref_coordinates[2] 
		<< "\n";

	return out;
}
