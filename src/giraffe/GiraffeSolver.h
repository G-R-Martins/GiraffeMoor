#pragma once



class GiraffeSolver
{
private:

	bool m_run_Giraffe;
	unsigned int m_cores;

	// Linear system solver option.
	// if is not direct, it will be defined as 'iterative'
	bool m_is_direct;


	struct ConvergenceCriteria
	{
		double force_tol = 1.0e-4;		//Factor applied to the system force vector norm to establish convergence criterion
		double moment_tol = 1.0e-4;		//Factor applied to the system moment vector norm to establish convergence criterion

		double force_min = 1.0e0;		//Force value considered small - used when there are only zero forces - dimensional value
		double moment_min = 1.0e0;		//Small moment value - used when there are only null moments - dimensional value
		double constraint_min = 1.0e-7;	//Constraint error value, considered small - always used when there are joints

		double disp_tol = 1.0e-4;		//Factor applied to the system's incremental displacement vector norm to establish convergence criterion
		double rot_tol = 1.0e-4;		//Factor applied to the system's incremental rotation vector norm to establish convergence criterion 
		double lag_tol = 1.0e-4;		//Factor applied to the system lagrange multiplier vector norm to establish convergence criterion

		double disp_min = 1.0e-5;		//Offset value considered small - used when there are only null offsets - dimensional value
		double rot_min = 1.0e-5;		//Rotation value considered small - used when there are only null rotations - dimensional value 
		double lag_min = 1.0e-6;		//Lagrange multiplier value considered small - used when there are only null lagrange multipliers - dimensional value 

		double divergence_ref = 1.0e15;	//Very high value indicating model divergence
	} m_conv_criteria;

public:
	GiraffeSolver();
	~GiraffeSolver();

	
	//Writes Giraffe input file (.inp)
	void WriteGiraffeModelFile(std::ostream& fout) const;


	///
	/// SETTERS
	///
	
	void SetRunGiraffeOpt(bool run_opt);
	void SetCores(unsigned int cores);
	void SetLinSolverOpt(bool is_direct);

	void SetLinSolverOpt(std::string_view type);


	///
	/// GETTERS
	///

	inline const ConvergenceCriteria& GetConvCriteria() const	{ return m_conv_criteria; }
	inline ConvergenceCriteria& GetConvCriteria()				{ return m_conv_criteria; }

	inline bool RunGiraffe() const { return m_run_Giraffe; }
	inline bool RunGiraffe() { return m_run_Giraffe; }

	///
	/// Overloaded operator 
	/// 
	
	friend std::ostream& operator<<(std::ostream& fout, const GiraffeSolver::ConvergenceCriteria& conv_criteria);
};

