#pragma once
#include "Solution.h"


class Dynamic :	public Solution
{
private:
	double m_alpha_ray;  //Rayleigh
	double m_beta_ray;  //Rayleigh

	double m_gamma_new;  //Newmark
	double m_beta_new;  //Newmark

	int m_update;

	bool m_zero_ic;  //zero initial conditions
public:
	Dynamic();
	Dynamic(double alpha_ray, double beta_ray, double gamma_new, double beta_new, int update);
	Dynamic(unsigned int id, double start_time, double end_time, double i_time_step, double min_time_step, double max_time_step,
		unsigned int max_it, unsigned int min_it, unsigned int conv_increase, double inc_factor, unsigned int sample, 
		double alpha_ray, double beta_ray, double gamma_new, double beta_new, int update, bool zero_ic=false);
	~Dynamic();
	

	/// 
	/// SETTERS
	/// 
	
	void SetRayleighDamping(double alpha_ray, double beta_ray);
	void SetRayleighAlpha(double alpha_ray);
	void SetRayleighBeta(double beta_ray);
	void SetNewmarkCoefficients(double gamma_new, double beta_new);
	void SetNewmarkGamma(double gamma_new);
	void SetNewmarkBeta(double beta_new);
	void SetUpdate(int update);
	void SetZeroIC(bool zero_ic);


	/// 
	/// GETTERS
	/// 
	
	inline double GetRayleighAlpha() const	{ return m_alpha_ray; }
	inline double GetRayleighBeta() const	{ return m_beta_ray; }
	inline double GetNewmarkGamma() const	{ return m_gamma_new; }
	inline double GetNewmarkBeta() const	{ return m_beta_new; }
	inline int GetUpdate() const			{ return m_update; }
	inline int GetZeroIC() const			{ return m_zero_ic; }


	/// 
	/// Overloaded operators
	/// 

	friend std::ofstream& operator<<(std::ofstream& out, Dynamic const& obj);
	inline std::ofstream& WriteGiraffeFile(std::ofstream& out) override { operator<<(out, *this); return out; }
};

