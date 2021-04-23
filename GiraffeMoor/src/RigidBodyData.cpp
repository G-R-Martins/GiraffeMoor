#include "PCH.h"
#include "RigidBodyData.h"


RigidBodyData::RigidBodyData()
	: number(0), mass(0.0), J_G(std::array{ 0.,0.,0.,0.,0.,0. }), G(std::array{ 0.,0.,0. })
{}

RigidBodyData::~RigidBodyData()
{}

void RigidBodyData::WriteGiraffeModelFile(FILE *f) const
{
	if (comment.size() > 0)
	{
		fprintf(f, "\t//%s\n", comment.c_str());
	}
	fprintf(f, "\tRBData\t%d\n", number);
	fprintf(f, "\t\tMass\t%.2f\t", mass);
	fprintf(f, "\tJ11\t%.6f\tJ22\t%.6f\tJ33\t%.6f\tJ12\t%.6f\tJ13\t%.6f\tJ23\t%.6f\t", J_G[0], J_G[1], J_G[2], J_G[3], J_G[4], J_G[5]);
	fprintf(f, "\tBarycenter\t%.6f\t%.6f\t%.6f\n", G[0], G[1], G[2]);
	
	if (!platform_name.empty())
	{
		fprintf(f, "\tCADData\t1\n");
		fprintf(f, "\nCADData\t1\n\tSTLSurface\t1\t%s\n", platform_name.c_str());
	}
}
