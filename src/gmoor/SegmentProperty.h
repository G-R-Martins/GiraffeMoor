#pragma once


enum class WizardType { 
	NONE = 0, STUDLINK, STUDLESS
};
enum class Grade { 
	NONE = 0, ORQ, TWO, THREE, R4
};


class SegmentProperty
{
private:
	unsigned int m_id;

	double m_rho;
	double m_diameter;
	double m_diameter_inner;
	double m_diameter_contact;
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
	double m_SG;
	double m_MBS;

	bool m_is_chain;
	bool m_is_truss;
	bool m_is_beam;

	WizardType m_wizard;
	Grade m_grade;

public:
	SegmentProperty();
	~SegmentProperty();


	/// 
	/// SETTERS
	/// 
	
	void SetIDNumber(unsigned int id);
	void SetMass(double rho);
	void SetDiameter(double diameter);
	void SetInnerDiameter(double diameter_inner);
	void SetContactDiameter(double diameter_contact);
	void SetEA(double EA);
	void SetEI(double EI);
	void SetGJ(double GJ);
	void SetGA(double GA);
	void SetCDt(double CDt);
	void SetCDn(double CDn);
	void SetCAt(double CAt);
	void SetCAn(double CAn);
	void SetYoungMod(double E);
	void SetPoisson(double nu);
	void SetSG(double SG);
	void SetMBS(double MBS);
	void SetMBSFromWizard(double d);
	void SetGrade(std::string_view grade);

	void SetChainOpt(bool is_chain);
	void SetTrussOpt(bool is_truss);
	void SetBeamOpt(bool is_beam);
	
	void SetWizardType(std::string_view type);
	void SetWizard(double d);
	void SetWizardStudless(double d);
	void SetWizardStudlink(double d);
	
	
	/// 
	/// GETTERS
	/// 
	
	inline const unsigned int GetNumber() const		{ return m_id; }
	inline const double GetMass() const				{ return m_rho; }
	inline const double GetDiameter() const			{ return m_diameter; }
	inline const double GetInnerDiameter() const	{ return m_diameter_inner; }
	inline const double GetContactDiameter() const	{ return m_diameter_contact; }
	inline const double GetEA() const				{ return m_EA; }
	inline const double GetEI() const				{ return m_EI; }
	inline const double GetGJ() const				{ return m_GJ; }
	inline const double GetGA() const				{ return m_GA; }
	inline const double GetCDt() const				{ return m_CDt; }
	inline const double GetCDn() const				{ return m_CDn; }
	inline const double GetCAt() const				{ return m_CAt; }
	inline const double GetCAn() const				{ return m_CAn; }
	inline const double GetYoungMod() const			{ return m_E; }
	inline const double GetPoisson() const			{ return m_nu; }
	inline const double GetSG() const				{ return m_SG; }
	inline const double GetMBS() const				{ return m_MBS; }
	
	inline const bool IsTruss() const		{ return m_is_truss; }
	inline const bool IsChain() const		{ return m_is_chain; }
	inline const bool IsBeam() const		{ return m_is_beam; }


	/*-------------------
	 Overloaded operators
	 -------------------*/

	friend bool operator< (const SegmentProperty& obj1, const SegmentProperty& obj2);
	friend bool operator> (const SegmentProperty& obj1, const SegmentProperty& obj2);
	friend bool operator== (const SegmentProperty& obj1, const SegmentProperty& obj2);
	friend bool operator!= (const SegmentProperty& obj1, const SegmentProperty& obj2);
};