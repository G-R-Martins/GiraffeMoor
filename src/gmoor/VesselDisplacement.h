#pragma once
#include "ExternalTimeHistory.h"


class VesselDisplacement : public ExternalTimeHistory
{
private:
	unsigned int m_vessel_id;
	
public:
	VesselDisplacement();
	VesselDisplacement(const VesselDisplacement&) = default;
	VesselDisplacement(VesselDisplacement&&) noexcept = default;
	~VesselDisplacement();


	///
	/// SETTERS
	///
	
	void SetVesselID(unsigned int vessel_id);
	

	///
	/// GETTERS
	///
	
	inline unsigned int GetVesselID() const			{ return m_vessel_id; }
	

	/// 
	/// Overloaded operators
	/// 
	
	friend bool operator<(const VesselDisplacement& obj1, const VesselDisplacement& obj2);
	friend bool operator>(const VesselDisplacement& obj1, const VesselDisplacement& obj2);
	friend bool operator==(const VesselDisplacement& obj1, const VesselDisplacement& obj2);
	friend bool operator!=(const VesselDisplacement& obj1, const VesselDisplacement& obj2);

	VesselDisplacement& operator=(const VesselDisplacement&) = default;
	VesselDisplacement& operator=(VesselDisplacement&&) noexcept = default;
};
