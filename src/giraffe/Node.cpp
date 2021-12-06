#include "PCH.h"
#include "Node.h"

Node::Node()
	: m_number(0), m_ref_coordinates({0.,0.,0.}), m_comment("\0")
{}

Node::Node(size_t number, const std::array<double, 3>& m_ref_coordinates, std::string comment)
	: m_number(number), m_ref_coordinates(m_ref_coordinates), m_comment(comment)
{}

Node::~Node()
{}

void Node::SetIDNumber(size_t number)
{
	m_number = number;
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

	out << "\tNode " << obj.m_number 
		<< "\t\t" << obj.m_ref_coordinates[0] << " \t" << obj.m_ref_coordinates[1] << " \t" << obj.m_ref_coordinates[2] 
		<< "\n";

	return out;
}
