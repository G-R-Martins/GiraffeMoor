#pragma once


class ConvergenceCriteria
{
	double force_tol;		//Factor applied to the system force vector norm to establish convergence criterion
	double moment_tol;		//Factor applied to the system moment vector norm to establish convergence criterion
	
	double force_min;		//Force value considered small - used when there are only zero forces - dimensional value
	double moment_min;		//Small moment value - used when there are only null moments - dimensional value
	double constraint_min;	//Constraint error value, considered small - always used when there are joints

	double disp_tol;		//Factor applied to the system's incremental displacement vector norm to establish convergence criterion
	double rot_tol;			//Factor applied to the system's incremental rotation vector norm to establish convergence criterion 
	double lag_tol;			//Factor applied to the system lagrange multiplier vector norm to establish convergence criterion

	double disp_min;		//Offset value considered small - used when there are only null offsets - dimensional value
	double rot_min;			//Rotation value considered small - used when there are only null rotations - dimensional value 
	double lag_min;			//Lagrange multiplier value considered small - used when there are only null lagrange multipliers - dimensional value 

	double divergence_ref;	//Very high value indicating model divergence

	//============================================================================

public:
	ConvergenceCriteria();
	~ConvergenceCriteria();

	/// 
	/// Functions
	/// 

	//Reads input file
	bool Read(FILE *f);	

	//Writes Giraffe file
	void WriteGiraffeModelFile(std::ostream& fout) const;

};

