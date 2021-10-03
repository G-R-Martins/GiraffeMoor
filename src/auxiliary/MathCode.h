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
	void SetEquation(size_t dof, const std::string& eq);
	//Changing 't0' for the real time
	void SetEquationInitialTime(const double& init);


	/// 
	/// GETTERS
	/// 
	
	inline double GetStartTime() const						{ return m_start_time; }
	inline std::string_view GetEquation(size_t dof) const	{ return m_equations[dof]; }

	
	///
	///Overloaded operator to print line in the summary file 
	///
	
	friend std::ostream& operator<<(std::ostream& out, const MathCode& mc);
	friend std::ostream& operator<<(std::ostream& out, MathCode* mcPtr);
	friend std::ifstream& operator>>(std::ifstream& input, MathCode* ptr_math_code);
};

