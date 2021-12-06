#pragma once
#include "Contact.h"
#include "BoolTable.h"


class NSSS : public Contact
{
private:
	size_t m_number;
	size_t m_node_set;	//Node set ID
	size_t m_surface_set;  //Surface set ID

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
	NSSS(const size_t& number, const size_t& node_set, const size_t& surface_set,
		double mu, double epn, double cn, double ept, double ct,
		double pinball, double radius, unsigned int max_interactions,
		BoolTable&& booltable, const  std::string& comment = "\0");
	~NSSS();


	/// 
	/// GETTERS
	/// 

	inline size_t GetNumber() const						{ return m_number; }
	inline size_t GetNodeSet() const					{ return m_node_set; }
	inline size_t GetSurfaceSet() const					{ return m_surface_set; }
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

