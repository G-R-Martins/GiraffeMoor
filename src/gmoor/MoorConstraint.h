#pragma once


class MoorConstraint
{
private:
	// Constrained object ID
	// -> anchor, line or vessel
	unsigned int m_id;
	unsigned int m_nodeset_id;

	//General container
	std::vector<std::list<bool>> m_constraints;

public:

	MoorConstraint();
	MoorConstraint(const MoorConstraint&) = default;
	MoorConstraint(MoorConstraint&&) = default;
	~MoorConstraint();


	/// 
	/// SETTERS
	/// 

	void SetIDNumber(unsigned int id);
	void SetNodeset(unsigned int nodeset_id);
	void SetDof(unsigned int dof_id, const std::list<bool>& constraints);
	void PushToDof(unsigned int dof, bool constraint);
	void PushX(bool constraint);
	void PushY(bool constraint);
	void PushZ(bool constraint);
	void PushRotX(bool constraint);
	void PushRotY(bool constraint);
	void PushRotZ(bool constraint);


	/// 
	/// GETTERS
	/// 

	// anchors, line, or vessel
	inline unsigned int GetNumber() const { return m_id; }
	inline unsigned int GetNodeset() const { return m_nodeset_id; }

	inline const std::vector<std::list<bool>>& GetAllConstraints() const { return m_constraints; }
	inline std::vector<std::list<bool>>& GetAllConstraints() { return m_constraints; }
	inline std::list<bool>const& GetConstraint(unsigned int dof) const { return m_constraints[dof]; }
	inline std::list<bool>const& GetX() const { return m_constraints[0]; }
	inline std::list<bool>const& GetY() const { return m_constraints[1]; }
	inline std::list<bool>const& GetZ() const { return m_constraints[2]; }
	inline std::list<bool>const& GetRotX() const { return m_constraints[3]; }
	inline std::list<bool>const& GetRotY() const { return m_constraints[4]; }
	inline std::list<bool>const& GetRotZ() const { return m_constraints[5]; }

	inline unsigned int GetNConstraintsDOF(unsigned int dof) const { return (unsigned int)m_constraints[dof].size(); }
	inline unsigned int GetNConstraintsX() const { return (unsigned int)m_constraints[0].size(); }
	inline unsigned int GetNConstraintsY() const { return (unsigned int)m_constraints[1].size(); }
	inline unsigned int GetNConstraintsZ() const { return (unsigned int)m_constraints[2].size(); }
	inline unsigned int GetNConstraintsRotX() const { return (unsigned int)m_constraints[3].size(); }
	inline unsigned int GetNConstraintsRotY() const { return (unsigned int)m_constraints[4].size(); }
	inline unsigned int GetNConstraintsRotZ() const { return (unsigned int)m_constraints[5].size(); }


	/// 
	/// Overloaded operators
	/// 

	friend bool operator<(const MoorConstraint& obj1, const MoorConstraint& obj2);
	friend bool operator>(const MoorConstraint& obj1, const MoorConstraint& obj2);
	friend bool operator==(const MoorConstraint& obj1, const MoorConstraint& obj2);
	friend bool operator!=(const MoorConstraint& obj1, const MoorConstraint& obj2);

	MoorConstraint& operator=(const MoorConstraint&) = default;
	MoorConstraint& operator=(MoorConstraint&&) = default;

};


