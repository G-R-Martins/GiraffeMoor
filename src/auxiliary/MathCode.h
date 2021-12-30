#pragma once

class MathCode
{
	//Vector with equations
	std::vector<std::string> m_equations;
	double m_start_time;

public:
	MathCode();
	~MathCode();


	/// 
	/// SETTERS 
	/// 
	
	void SetStartTime(const double& start);
	void SetEquation(unsigned int dof, const std::string& eq);
	//Changing 't0' for the real time
	void SetEquationInitialTime(const double& init);


	/// 
	/// GETTERS
	/// 
	
	inline double GetStartTime() const						{ return m_start_time; }
	inline std::string_view GetEquation(unsigned int dof) const	{ return m_equations[dof]; }

	
	///
	///Overloaded operator to print line in the summary file 
	///
	
	friend std::ostream& operator<<(std::ostream& out, const MathCode& mc);
	friend std::ostream& operator<<(std::ostream& out, MathCode* mcPtr);
};

