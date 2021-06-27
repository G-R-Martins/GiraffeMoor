#include "PCH.h"
#include "DisplacementField.h"


DisplacementField::DisplacementField()
	: cs(0), solution_step(0)
{
	disp_data.clear();
}

DisplacementField::DisplacementField(unsigned int n_nodes)
	: cs(0), solution_step(0)
{
	disp_data.reserve(n_nodes);
}

DisplacementField::~DisplacementField()
{}

void  DisplacementField::WriteGiraffeModelFile(std::ostream& fout) const
{
	fout << "\tDisplacementField " << number <<
		"\tNNodes " << disp_data.size() <<
		"\tCS " << cs << "\tSolutionStep " << solution_step <<
		"\n";
	//Write displacement data
	for (size_t i = 0; i < disp_data.size(); ++i)
	{
		fout << "\t" << disp_data[i].node << "\t";
		for ( size_t j = 0; j < 6; ++j )
			fout << disp_data[i].disp[j] << "\t";
		fout << "\n";
	}
}

void DisplacementField::InsertDisplacement(const int &node, Matrix &e_disp)
{
	DispStruct temp;
	temp.node = node;
	for (int i = 0; i < 6; i++)
		temp.disp[i] = e_disp(i, 0);
	disp_data.push_back(temp);
}

void DisplacementField::InsertDisplacement(const unsigned int& node, Matrix &e_disp)
{
	DispStruct temp;
	temp.node = node;
	for (int i = 0; i < 6; i++)
		temp.disp[i] = e_disp(i, 0);
	disp_data.push_back(temp);
}

void DisplacementField::InsertDisplacement(const int &node, Matrix &e_disp, Matrix &e_rot)
{
	DispStruct temp;
	temp.node = node;
	for (int i = 0; i < 3; i++)
		temp.disp[i] = e_disp(i, 0);
	for (long i = 0; i < 3; i++)
		temp.disp[( size_t )i + 3] = e_rot(i, 0);
	disp_data.push_back(temp);
}

void DisplacementField::InsertDisplacement(const unsigned int&node, Matrix &e_disp, Matrix &e_rot)
{
	DispStruct temp;
	temp.node = node;
	for (int i = 0; i < 3; i++)
		temp.disp[i] = e_disp(i, 0);
	for (long i = 0; i < 3; i++)
		temp.disp[(size_t)i + 3] = e_rot(i, 0);
	disp_data.push_back(temp);
}

void DisplacementField::InsertDisplacement(const unsigned int&node, std::array<double,6>& e_disp)
{
	DispStruct temp;
	temp.node = node;
	temp.disp = e_disp;
	disp_data.emplace_back(temp);
}
