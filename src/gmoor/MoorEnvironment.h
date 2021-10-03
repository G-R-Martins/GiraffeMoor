#pragma once
#include "Seabed.h"
#include "SeaCurrent.h"


class MoorEnvironment
{
private:
	// General environment variables
	static double s_gravity;
	double m_rho_fluid;
	double m_water_depth;
	
	Seabed m_seabed;

	// Sea current
	std::vector<SeaCurrent> m_sea_current_vector;
	bool m_sea_current_exist; 
	bool m_sea_current_is_constant;
	
	//============================================================================

public:

	MoorEnvironment();
	~MoorEnvironment();


	///
	/// SETTERS
	///
	
	static void SetGravity(double g);
	void SetRhoFluid(double rho_fluid);
	void SetWaterDepth(double water_depth);
	void SetBoolConstantSeaCurrent(bool is_constant);

	
	///
	/// GETTERS
	///
	
	inline static double GetGravity()		{ return MoorEnvironment::s_gravity; }
	inline double GetRhoFluid() const		{ return this->m_rho_fluid; }
	inline double GetWaterDepth() const		{ return this->m_water_depth; }

	inline Seabed& GetSeabed()				{ return this->m_seabed; }
	inline Seabed const& GetSeabed() const	{ return this->m_seabed; }

	inline SeaCurrent const& GetSeaCurrent(size_t sc) const { 
		return this->m_sea_current_vector[sc];	}
	inline SeaCurrent& GetSeaCurrent(size_t sc) { 
		return this->m_sea_current_vector[sc];	}

	inline std::vector<SeaCurrent> const& GetSeaCurrentVec() const { 
		return this->m_sea_current_vector; }
	inline std::vector<SeaCurrent>& GetSeaCurrentVec() { 
		return this->m_sea_current_vector; }


	// Getter-ish to do some checking
	
	bool ExistSeaCurrent() const			{ return this->m_sea_current_exist; }
	bool ExistSeaCurrent()					{ return this->m_sea_current_exist; }
	
	bool SeaCurrentIsConstant() const		{ return this->m_sea_current_is_constant; }
	bool SeaCurrentIsConstant()				{ return this->m_sea_current_is_constant; }

};

