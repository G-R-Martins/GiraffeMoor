#pragma once
#include "Contact.h"
#include "BoolTable.h"


class NSSS : public Contact
{
private:
	unsigned int m_id;
	unsigned int m_node_set_id;	//Node set ID
	unsigned int m_surface_set_id;  //Surface set ID

	double m_mu;
	double m_epn;
	double m_cn;
	double m_ept;
	double m_ct;

	double m_pinball;
	
	double m_radius;
	unsigned int m_max_interactions;

	BoolTable m_booltable;

	std::string m_comment;

public:
	NSSS();
	NSSS(const unsigned int& number, const unsigned int& node_set, const unsigned int& surface_set,
		double mu, double epn, double cn, double ept, double ct,
		double pinball, double radius, unsigned int max_interactions,
		BoolTable&& booltable, const  std::string& comment = "\0");
	~NSSS();


	/// 
	/// GETTERS
	/// 

	inline unsigned int GetNumber() const						{ return m_id; }
	inline unsigned int GetNodeSet() const					{ return m_node_set_id; }
	inline unsigned int GetSurfaceSet() const					{ return m_surface_set_id; }
	inline double GetFrictionCoefficient() const		{ return m_mu; }
	inline double GetEPn() const						{ return m_epn; }
	inline double GetCn() const							{ return m_cn; }
	inline double GetEPt() const						{ return m_ept; }
	inline double GetCt() const							{ return m_ct; }
	inline double GetPinball() const					{ return m_pinball; }
	inline double GetRadius() const						{ return m_radius; }
	inline unsigned int GetMAxIterations() const		{ return m_max_interactions; }
	inline const BoolTable& GetBoolTable() const		{ return m_booltable; }
	inline const std::string& GetComment() const	{ return m_comment; }



	/// 
	/// Overloaded operators
	/// 
	
	friend std::ostream& operator<<(std::ostream& out, const NSSS& nsss);

	inline std::ofstream& WriteGiraffeFile(std::ofstream& out) override { operator<<(out, *this); return out; }
};

