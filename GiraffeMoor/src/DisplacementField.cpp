#include "PCH.h"
#include "DisplacementField.h"


DisplacementField::DisplacementField()
	: cs(0), solution_step(0)
{
	disp_data.clear();
}

DisplacementField::~DisplacementField()
{}

void  DisplacementField::WriteGiraffeModelFile(FILE *f)
{
	fprintf(f, "\tDisplacementField\t%d\tNNodes\t%d\tCS\t%d\tSolutionStep\t%d\n", number, (int)disp_data.size(), cs, solution_step);
	//Write displacement data
	for (int i = 0; i < (int)disp_data.size(); i++)
	{
		fprintf(f, "\t%d\t", disp_data[i].node);
		for (int j = 0; j < 6; j++)
			fprintf(f, "%.12e\t", disp_data[i].disp[j]);
		fprintf(f, "\n");
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
