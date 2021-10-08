#pragma once


class MoorConstraint
{
private:
	// Constrained object ID
	// -> anchor, line or vessel
	size_t m_number;
	size_t m_nodeset;

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

	void SetIDNumber(size_t number);
	void SetNodeset(size_t nodeset);
	void SetDof(size_t dof, const std::list<bool>& constraints);
	void PushToDof(size_t dof, bool constraint);
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
	inline size_t GetNumber() const { return m_number; }
	inline size_t GetNodeset() const { return m_nodeset; }

	inline const std::vector<std::list<bool>>& GetAllConstraints() const { return m_constraints; }
	inline std::vector<std::list<bool>>& GetAllConstraints() { return m_constraints; }
	inline std::list<bool>const& GetConstraint(size_t dof) const { return m_constraints[dof]; }
	inline std::list<bool>const& GetX() const { return m_constraints[0]; }
	inline std::list<bool>const& GetY() const { return m_constraints[1]; }
	inline std::list<bool>const& GetZ() const { return m_constraints[2]; }
	inline std::list<bool>const& GetRotX() const { return m_constraints[3]; }
	inline std::list<bool>const& GetRotY() const { return m_constraints[4]; }
	inline std::list<bool>const& GetRotZ() const { return m_constraints[5]; }

	inline size_t GetNConstraintsDOF(unsigned int dof) const { return m_constraints[dof].size(); }
	inline size_t GetNConstraintsX() const { return m_constraints[0].size(); }
	inline size_t GetNConstraintsY() const { return m_constraints[1].size(); }
	inline size_t GetNConstraintsZ() const { return m_constraints[2].size(); }
	inline size_t GetNConstraintsRotX() const { return m_constraints[3].size(); }
	inline size_t GetNConstraintsRotY() const { return m_constraints[4].size(); }
	inline size_t GetNConstraintsRotZ() const { return m_constraints[5].size(); }


	/// 
	/// Overloaded operators
	/// 

	friend bool operator<(const MoorConstraint& obj1, const MoorConstraint& obj2);
	friend bool operator>(const MoorConstraint& obj1, const MoorConstraint& obj2);
	friend bool operator==(const MoorConstraint& obj1, const MoorConstraint& obj2);
	friend bool operator!=(const MoorConstraint& obj1, const MoorConstraint& obj2);

	MoorConstraint& operator=(const MoorConstraint&) = default;
	MoorConstraint& operator=(MoorConstraint&&) = default;

	friend std::ifstream& operator>>(std::ifstream& input, MoorConstraint* constraint);



};


