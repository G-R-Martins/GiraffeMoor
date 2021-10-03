#pragma once

class SegmentProperty
{
private:
	size_t m_number;

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

public:
	SegmentProperty();
	~SegmentProperty();


	//Writes Giraffe file data
	void WriteGiraffeModelFile(std::ostream& fout) const;

	/// 
	/// SETTERS
	/// 
	
	void SetIDNumber(size_t number);
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
	
	void SetChainOpt(bool is_chain);
	void SetTrussOpt(bool is_truss);
	void SetBeamOpt(bool is_beam);

	bool SetWizardStudless(double d, std::string_view grade);
	bool SetWizardStudlink(double d, std::string_view grade);
	
	
	/// 
	/// GETTERS
	/// 
	
	inline const size_t GetNumber() const			{ return m_number; }
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
	
	inline const bool IsTruss() const		{ return (m_is_truss || m_is_chain); }
	inline const bool IsChain() const		{ return (m_is_truss || m_is_chain); }
	inline const bool IsBeam() const		{ return m_is_beam; }



	/*-------------------
	 Overloaded operators
	 -------------------*/

	friend bool operator< (const SegmentProperty& obj1, const SegmentProperty& obj2);
	friend bool operator> (const SegmentProperty& obj1, const SegmentProperty& obj2);
	friend bool operator== (const SegmentProperty& obj1, const SegmentProperty& obj2);
	friend bool operator!= (const SegmentProperty& obj1, const SegmentProperty& obj2);
};