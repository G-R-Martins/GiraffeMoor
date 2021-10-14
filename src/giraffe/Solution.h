#pragma once


class Solution
{
private:
	size_t m_number;
	double m_start_time;
	double m_end_time;

	double m_time_step;
	double m_max_time_step;
	double m_min_time_step;
	int m_max_it;
	int m_min_it;
	int m_convergence_increase;
	double m_increase_factor;
	int m_sample;

public:
	Solution();
	virtual ~Solution();

	virtual inline std::ofstream& WriteGiraffeFile(std::ofstream& out) = 0;
	
	/// 
	/// SETTERS
	/// 
	
	void SetIDNumber(size_t number);
	void SetStartTime(double start_time);
	void SetEndTime(double end_time);

	void SetTimeStep(double time_step);
	void SetTimeStep(double time_step, double min_time_step, double max_time_step=0.0);
	
	void SetIterations(int max_it, int min_it);
	void SetMaxIterations(int max_it);
	void SetMinIterations(int min_it);

	void SetIncrese(int convergence_increase, double increase_factor);
	void SetConvergenceIncrese(int convergence_increase);
	void SetIncreseFactor(double increase_factor);

	void SetSample(int sample);


	/// 
	/// GETTERS
	/// 
	
	inline size_t GetNumber() const				{ return m_number; }
	inline double GetStartTime() const			{ return m_start_time; }
	inline double GetEndTime() const			{ return m_end_time; }
	
	inline double GetTimeStep() const			{ return m_time_step; }
	inline double GetMaxTimeStep() const		{ return m_max_time_step; }
	inline double GetMinTimeStep() const		{ return m_min_time_step; }
	
	inline int GetMaxIt() const					{ return m_max_it; }
	inline int GetMinIt() const					{ return m_min_it; }
	
	inline int GetConvergenceCriteria() const	{ return m_convergence_increase; }
	inline double GetIncreaseFactor() const		{ return m_increase_factor; }
	
	inline int GetSample() const				{ return m_sample; }

};

