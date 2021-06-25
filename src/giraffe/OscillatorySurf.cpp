#include "PCH.h"
#include "OscillatorySurf.h"

OscillatorySurf::OscillatorySurf()
	: number(0), A1(0.0), A2(0.0), A12(0.0), lambda1(0.0), lambda2(0.0), 
	phi1(0.0), phi2(0.0), waves1(0.0), waves2(0.0), cs(0), pilot_node(0)
{}

OscillatorySurf::~OscillatorySurf()
{}

void OscillatorySurf::WriteGiraffeModelFile(std::ostream& fout) const
{
	fout << "\tRigidOscillatorySurface_1 " << number <<
		"\tA1 " << A1 <<
		"\tA2 " << A2 <<
		"\tA12 " << A12 <<
		"\tLambda1 " << lambda1 <<
		"\tLambda2 " << lambda2 <<
		"\tPhi1 " << phi1 <<
		"\tPhi2 " << phi2 <<
		"\tWaves1" << waves1 <<
		"\tWaves2 " << waves2 <<
		"\tCS " << cs <<
		"\tPilotNode " << pilot_node <<
		"\n";
}