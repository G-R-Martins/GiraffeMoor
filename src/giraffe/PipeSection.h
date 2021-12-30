#pragma once
#include "SegmentProperty.h"

class PipeSection
{
private:
	unsigned int m_id;
	bool m_is_beam;
	double m_diameter;
	double m_rho;
	double m_EA;
	double m_EI;
	double m_GJ;
	double m_GA;
	double m_CDt;
	double m_CDn;
	double m_CAt;
	double m_CAn;
	double m_E;
	double m_nu;

public:
	PipeSection();
	PipeSection(unsigned int id, bool is_beam, double d, double rho,
				double EA, double EI, double GJ, double GA,
				double CDt, double CDn, double CAt, double CAn,
				double E, double nu);
	PipeSection(const SegmentProperty& moor_prop);

	~PipeSection();
	

	/// 
	/// Overloaded operators
	/// 

	friend std::ostream& operator<<(std::ostream& out, const PipeSection& obj);

};

