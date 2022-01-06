#include "PCH.h"
#include "DisplacementField.h"


DisplacementField::DisplacementField()
	: m_cs_id(0), m_solution_step_id(0), m_disp_data{}
{}

DisplacementField::DisplacementField(unsigned int cs_id, unsigned int solution_step_id)
	: m_cs_id(cs_id), m_solution_step_id(solution_step_id), m_disp_data{}
{}

DisplacementField::~DisplacementField()
{}



void DisplacementField::InsertDisplacement(const unsigned int&node_id, Matrix &e_disp)
{
	DispStruct temp;
	temp.node_id = node_id;
	for (int i = 0; i < 6; i++)
		temp.disp[i] = e_disp(i, 0);
	m_disp_data.push_back(temp);
}

void DisplacementField::InsertDisplacement(const unsigned int&node_id, Matrix &e_disp, Matrix &e_rot)
{
	DispStruct temp;
	temp.node_id = node_id;
	for (int i = 0; i < 3; i++)
		temp.disp[i] = e_disp(i, 0);
	for (long i = 0; i < 3; i++)
		temp.disp[( size_t )i + 3] = e_rot(i, 0);
	m_disp_data.push_back(temp);
}


void DisplacementField::InsertDisplacement(const unsigned int&node_id, std::array<double,6>& e_disp)
{
	DispStruct temp;
	temp.node_id = node_id;
	temp.disp = e_disp;
	m_disp_data.emplace_back(temp);
}


/// 
/// SETTERS
/// 

void DisplacementField::SetCoordinateSystem(unsigned int cs_id)
{
	m_cs_id = cs_id;
}
void DisplacementField::SetSolutionStep(unsigned int solution_step_id)
{
	m_solution_step_id = solution_step_id;
}


/// 
/// Overloaded operators
/// 

std::ostream& operator<<(std::ostream& out, const DisplacementField& obj)
{
	out << "\tDisplacementField " << obj.GetNumber()
		<< "\tNNodes " << obj.m_disp_data.size()
		<< "\tCS " << obj.m_cs_id
		<< "\tSolutionStep " << obj.m_solution_step_id
		<< "\n";

	//Write displacement data
	for (size_t i = 0; i < obj.m_disp_data.size(); ++i)
	{
		out << "\t\t" << obj.m_disp_data[i].node_id << "\t";
		for (size_t j = 0; j < 6; ++j)
			out << obj.m_disp_data[i].disp[j] << "\t";
		out << "\n";
	}


	return out;
}