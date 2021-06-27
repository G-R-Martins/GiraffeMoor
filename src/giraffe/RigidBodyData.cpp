#include "PCH.h"
#include "RigidBodyData.h"


RigidBodyData::RigidBodyData()
	: number{ 0 }, mass{ 0.0 }, J_G{ 0.,0.,0.,0.,0.,0. }, G{ 0.,0.,0. }, cad{ 0 }, comment{"\0"}
{}

RigidBodyData::~RigidBodyData()
{}

void RigidBodyData::WriteGiraffeModelFile(std::ostream& fout) const
{
	if (!comment.empty())
	{
		fout << "\t//" << comment <<
			"\n\tRBData " << number <<
			"\n\t\tMass " << mass <<
			"\n\t\tJ11 " << J_G[0] << "\tJ22 " << J_G[1] << "\tJ33 " << J_G[2] <<
			"\n\t\tJ12 " << J_G[3] << "\tJ13 " << J_G[4] << "\tJ23 " << J_G[5] <<
			"\n\t\tBarycenter " << G[0] << "\t" <<  G[1] << "\t" << G[2] <<
			"\n";
	}
	if (cad)
		fout << "\t\tCADData " << cad << "\n";
}
