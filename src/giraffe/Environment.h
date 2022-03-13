#pragma once
#include "SeaCurrent.h"
#include "BoolTable.h"


class Environment
{
private:
	double m_gravity;
	double m_rho_fluid;
	double m_water_depth;

	BoolTable m_bool_g;  //Gravity booltable
	BoolTable m_bool_current;  //Sea current booltable
	std::vector<SeaCurrent> m_sea_current_vector;  //sea current data
	
public:
	Environment();
	~Environment();



	///
	///  SETTERS
	///

	void SetGravity(double g);
	void SetRhoFluid(double rho);
	void SetWaterDepth(double wd);

	void SetGravityBooltable(const BoolTable& bool_grav);
	void SetSeaCurrentBooltable(const BoolTable& bool_current);

	void SetSeaCurrentVec(const std::vector<SeaCurrent>& current_vec);

	void SetNullSeaCurrent();


	///
	///  GETTERS
	///

	inline double GetGravity() const	{ return m_gravity; }
	inline double GetRhoFluid() const	{ return m_rho_fluid; }
	inline double GetWaterDepth() const	{ return m_water_depth; }


	inline const BoolTable& GetGravityBooltable() const		{ return m_bool_g; }
	inline BoolTable& GetGravityBooltable()					{ return m_bool_g; }
	inline const BoolTable& GetSeaCurrentBooltable() const	{ return m_bool_current; }
	inline BoolTable& GetSeaCurrentBooltable()				{ return m_bool_current; }

	const std::vector<SeaCurrent>& GetSeaCurrentVec() const { return m_sea_current_vector; }
	std::vector<SeaCurrent>& GetSeaCurrentVec()				{ return m_sea_current_vector; }


	/// 
	/// Overloaded operators
	/// 

	constexpr Environment& operator=(const Environment&) = default;
	friend std::ostream& operator<<(std::ostream& out, const Environment& obj);
};

