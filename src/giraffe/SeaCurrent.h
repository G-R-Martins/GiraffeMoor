#pragma once


class SeaCurrent
{
private:

	double m_depth;
	double m_speed;
	double m_azimuth;
	
public:

	SeaCurrent();
	SeaCurrent(double depth, double speed, double azimuth);
	~SeaCurrent();


	///
	/// SETTERS
	///

	void SetDepth(double depth);
	void SetSpeed(double speed);
	void SetAzimuth(double azimuth);


	///
	/// GETTERS
	///

	inline double GetDepth() const		{ return this->m_depth; }
	inline double GetSpeed() const		{ return this->m_speed; }
	inline double GetAzimuth() const	{ return this->m_azimuth; }

};

