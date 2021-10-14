#include "PCH.h"
#include "DisplacementField.h"


DisplacementField::DisplacementField()
	: m_cs(0), m_solution_step(0), m_disp_data{}
{}

DisplacementField::DisplacementField(size_t cs, size_t solution_step)
	: m_cs(cs), m_solution_step(solution_step), m_disp_data{}
{}

DisplacementField::~DisplacementField()
{}



void DisplacementField::InsertDisplacement(const int &node, Matrix &e_disp)
{
	DispStruct temp;
	temp.node = node;
	for (int i = 0; i < 6; i++)
		temp.disp[i] = e_disp(i, 0);
	m_disp_data.push_back(temp);
}

void DisplacementField::InsertDisplacement(const unsigned int& node, Matrix &e_disp)
{
	DispStruct temp;
	temp.node = node;
	for (int i = 0; i < 6; i++)
		temp.disp[i] = e_disp(i, 0);
	m_disp_data.push_back(temp);
}

void DisplacementField::InsertDisplacement(const int &node, Matrix &e_disp, Matrix &e_rot)
{
	DispStruct temp;
	temp.node = node;
	for (int i = 0; i < 3; i++)
		temp.disp[i] = e_disp(i, 0);
	for (long i = 0; i < 3; i++)
		temp.disp[( size_t )i + 3] = e_rot(i, 0);
	m_disp_data.push_back(temp);
}

void DisplacementField::InsertDisplacement(const unsigned int&node, Matrix &e_disp, Matrix &e_rot)
{
	DispStruct temp;
	temp.node = node;
	for (int i = 0; i < 3; i++)
		temp.disp[i] = e_disp(i, 0);
	for (long i = 0; i < 3; i++)
		temp.disp[(size_t)i + 3] = e_rot(i, 0);
	m_disp_data.push_back(temp);
}

void DisplacementField::InsertDisplacement(const unsigned int&node, std::array<double,6>& e_disp)
{
	DispStruct temp;
	temp.node = node;
	temp.disp = e_disp;
	m_disp_data.emplace_back(temp);
}


/// 
/// SETTERS
/// 

void DisplacementField::SetCoordinateSystem(size_t cs)
{
	m_cs = cs;
}
void DisplacementField::SetSolutionStep(size_t solution_step)
{
	m_solution_step = solution_step;
}


/// 
/// Overloaded operators
/// 

std::ostream& operator<<(std::ostream& out, const DisplacementField& obj)
{
	out << "\tDisplacementField " << obj.GetNumber()
		<< "\tNNodes " << obj.m_disp_data.size()
		<< "\tCS " << obj.m_cs 
		<< "\tSolutionStep " << obj.m_solution_step
		<< "\n";

	//Write displacement data
	for (size_t i = 0; i < obj.m_disp_data.size(); ++i)
	{
		out << "\t\t" << obj.m_disp_data[i].node << "\t";
		for (size_t j = 0; j < 6; ++j)
			out << obj.m_disp_data[i].disp[j] << "\t";
		out << "\n";
	}


	return out;
}