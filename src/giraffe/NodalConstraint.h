#pragma once
#include "Constraint.h"
#include "BoolTable.h"

class NodalConstraint : public Constraint
{
private:
	unsigned int m_node_set_id;
	BoolTable m_UX;
	BoolTable m_UY;
	BoolTable m_UZ;
	BoolTable m_ROTX;
	BoolTable m_ROTY;
	BoolTable m_ROTZ;

public:
	NodalConstraint();
	NodalConstraint(unsigned int node_set_id, const BoolTable& UX, const BoolTable& UY, const BoolTable& UZ,
		const BoolTable& ROTX, const BoolTable& ROTY, const BoolTable& ROTZ);
	NodalConstraint(unsigned int id, unsigned int node_set_id, const BoolTable& UX, const BoolTable& UY, const BoolTable& UZ,
		const BoolTable& ROTX, const BoolTable& ROTY, const BoolTable& ROTZ);
	~NodalConstraint();

	
	///
	/// SETTERS
	/// 
	
	void SetNodeset(unsigned int node_set_id);
	void SetUX(const BoolTable& UX);
	void SetUY(const BoolTable& UY);
	void SetUZ(const BoolTable& UZ);
	void SetROTX(const BoolTable& ROTX);
	void SetROTY(const BoolTable& ROTY);
	void SetROTZ(const BoolTable& ROTZ);

	///
	/// GETTERS
	/// 
	
	inline unsigned int GetNodeSet() const		{ return m_node_set_id; }
	inline const BoolTable& GetUX() const	{ return m_UX; }
	inline const BoolTable& GetUY() const	{ return m_UY; }
	inline const BoolTable& GetUZ() const	{ return m_UZ; }
	inline const BoolTable& GetROTX() const	{ return m_ROTX; }
	inline const BoolTable& GetROTY() const	{ return m_ROTY; }
	inline const BoolTable& GetROTZ() const	{ return m_ROTZ; }


	/// 
	/// Overloaded operators
	/// 

	friend std::ostream& operator<<(std::ostream& out, NodalConstraint const& obj);
	inline std::ofstream& WriteGiraffeFile(std::ofstream& out) override { operator<<(out, *this); return out; }
};

