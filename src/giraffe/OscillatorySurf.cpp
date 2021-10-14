#include "PCH.h"
#include "OscillatorySurf.h"

OscillatorySurf::OscillatorySurf()
	: m_number(0), m_A1(0.0), m_A2(0.0), m_A12(0.0), 
	m_lambda1(0.0), m_lambda2(0.0), m_phi1(0.0), m_phi2(0.0), 
	m_waves1(0.0), m_waves2(0.0), m_cs(0), m_pilot_node(0)
{}

OscillatorySurf::OscillatorySurf(size_t number, double A1, double A2,
	double A12, double lambda1, double lambda2, double phi1, double phi2,
	double waves1, double waves2, size_t cs, size_t pilot_node)
	: m_number(number), m_A1(A1), m_A2(A2), m_A12(A12),
	m_lambda1(lambda1), m_lambda2(lambda2), m_phi1(phi1), m_phi2(phi2),
	m_waves1(waves1), m_waves2(waves2), m_cs(cs), m_pilot_node(pilot_node)
{}

OscillatorySurf::~OscillatorySurf()
{}



/// 
/// Overloaded operators
/// 

std::ostream& operator<<(std::ostream& out, const OscillatorySurf& obj)
{
	out << "\tRigidOscillatorySurface_1 " << obj.m_number 
		<< "\tA1 "		<< obj.m_A1 
		<< "\tA2 "		<< obj.m_A2 
		<< "\tA12 "		<< obj.m_A12 
		<< "\tLambda1 " << obj.m_lambda1 
		<< "\tLambda2 " << obj.m_lambda2 
		<< "\tPhi1 "	<< obj.m_phi1 
		<< "\tPhi2 "	<< obj.m_phi2 
		<< "\tWaves1 "	<< obj.m_waves1 
		<< "\tWaves2 "	<< obj.m_waves2 
		<< "\tCS "		<< obj.m_cs 
		<< "\tPilotNode " << obj.m_pilot_node 
		<< "\n";

	return out;
}