#pragma once


class Seabed
{
private:
	bool m_is_flat;

	unsigned int m_pilot_node_id;
	unsigned int m_nodeset_id;
	
	double m_stiffness;  // used for penetration and NSSS contact
	double m_stiffness_tangential_factor;  // used for penetration and NSSS contact
	double m_damping;
	double m_mu;  // friction coefficient
	double m_pinball;
	double m_radius;  // NSSS contact

public:
	Seabed();
	~Seabed();

	/// 
	/// SETTERS
	/// 

	void SetFlatOption(bool is_flat);
	void SetPilotNode(unsigned int pilot_node_id);
	
	void SetNodeset(unsigned int nodeset_id);

	void SetStiffness(double stiffness);  
	void SetStiffnessTangentialFactor(double factor);  
	void SetDamping(double damping);
	void SetFrictionCoefficient(double mu);
	void SetPinball(double pinball);
	void SetRadius(double radius);
	
	
	/// 
	/// GETTERS
	/// 

	inline double GetStiffness() const					{ return this->m_stiffness; }
	inline double GetStiffnessTangentialFactor() const	{ return this->m_stiffness_tangential_factor; }
	inline double GetDamping() const					{ return this->m_damping; }
	inline double GetFrictionCoefficient() const		{ return this->m_mu; }
	inline double GetPinball() const					{ return this->m_pinball; }
	inline double GetRadius() const						{ return this->m_radius; }

};

