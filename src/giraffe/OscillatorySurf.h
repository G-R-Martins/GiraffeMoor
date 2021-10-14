#pragma once


class OscillatorySurf
{
private:
	size_t m_number;
	double m_A1;
	double m_A2;
	double m_A12;
	double m_lambda1;
	double m_lambda2;
	double m_phi1;
	double m_phi2;
	double m_waves1;
	double m_waves2;
	size_t m_cs;
	size_t m_pilot_node;

public:

	/*-------
	Functions
	--------*/

	OscillatorySurf();
	OscillatorySurf(size_t number, double A1, double A2, double A12, double lambda1, 
		double lambda2, double phi1, double phi2, double waves1, double waves2, size_t cs, size_t pilot_node);
	~OscillatorySurf();

	
	/// 
	/// GETTERS
	/// 
	
	inline size_t GetIDNumber() const { return m_number; }
	inline double GetA1() const { return m_A1; }
	inline double GetA2() const { return m_A2; }
	inline double GetA12() const { return m_A12; }
	inline double GetLambda1() const { return m_lambda1; }
	inline double GetLambda2() const { return m_lambda2; }
	inline double GetPhi1() const { return m_phi1; }
	inline double GetPhi2() const { return m_phi2; }
	inline double GetWaves1() const { return m_waves1; }
	inline double GetWaves2() const { return m_waves2; }
	inline size_t GetCS() const { return m_cs; }
	inline size_t GetPilotNode() const { return m_pilot_node; }

	/// 
	/// Overloaded operators
	/// 

	friend std::ostream& operator<<(std::ostream& out, const OscillatorySurf& obj);

};
