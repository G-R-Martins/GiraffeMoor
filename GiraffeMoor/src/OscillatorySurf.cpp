#include "PCH.h"
#include "OscillatorySurf.h"

OscillatorySurf::OscillatorySurf()
	: number(0), A1(0.0), A2(0.0), A12(0.0), lambda1(0.0), lambda2(0.0), 
	phi1(0.0), phi2(0.0), waves1(0.0), waves2(0.0), cs(0), pilot_node(0)
{}

OscillatorySurf::~OscillatorySurf()
{
}

void OscillatorySurf::WriteGiraffeModelFile(FILE *f) const
{
	fprintf(f, "\tRigidOscillatorySurface_1\t%d\tA1\t%.6e\tA2\t%.6e\tA12\t%.6e\tLambda1\t%.6e\tLambda2\t%.6e\tPhi1\t%.6e\tPhi2\t%.6e\tWaves1\t%.6e\tWaves2\t%.6e\tCS\t%d\tPilotNode\t%d\n", 
		number, A1, A2, A12, lambda1, lambda2, phi1, phi2, waves1, waves2, cs, pilot_node);
}