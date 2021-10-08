#pragma once
#include "SineWaveDisplacement.h"


class VesselDisplacement
{
private:

	size_t m_vesselID;	
	size_t m_solution_step; 
	
	//Boolean to indicate the type of the displacement
	bool m_is_table;
	bool m_is_sine_wave;
	bool m_is_math_code;
	bool m_is_external_file;

	//External file
	std::string m_file_name;
	unsigned int m_header_lines;  //in the external csv/txt file 
	unsigned int m_tot_steps;  //lines in the csv/txt file
	

	Table* m_ptr_time_series;
	SineWaveDisplacement* m_ptr_sine_wave;
	MathCode* m_ptr_math_code;

public:
	VesselDisplacement();
	VesselDisplacement(const VesselDisplacement&) = default;
	VesselDisplacement(VesselDisplacement&&) = default;
	~VesselDisplacement();


	///
	/// SETTERS
	///
	
	void SetVesselID(size_t vesselID);
	void SetSolutionStep(size_t solution_step);
	void SetStartTime(double start);
	void SetStartTableTime(double start_time, size_t start_line);
	void SetTimeSeries();
	void SetTimeSeries(std::ifstream& input);
	void SetSineWave();
	void SetMathCode();
	void SetFileName(const std::string& file_name);
	void SetFileHeaders(unsigned int header_lines);
	void SetFileNSteps(unsigned int tot_steps);


	///
	/// GETTERS
	///
	
	inline size_t GetVesselID() const					{ return m_vesselID; }
	inline size_t GetStep() const						{ return m_solution_step; }

	inline unsigned int GetNHeaderLines() const			{ return m_header_lines; }
	inline unsigned int GetNSteps() const				{ return m_tot_steps; }
	inline std::string& GetFileName()					{ return m_file_name; }

	inline Table* GetTimeSeries() const					{ return m_ptr_time_series; }
	inline Table* GetTimeSeries()						{ return m_ptr_time_series; }
	inline SineWaveDisplacement* GetSineWave() const	{ return m_ptr_sine_wave; }
	inline MathCode* GetMathCode() const				{ return m_ptr_math_code; }
	inline MathCode* GetMathCode()						{ return m_ptr_math_code; }

	inline bool IsTable() const							{ return m_is_table; }
	inline bool IsMathCode() const						{ return m_is_math_code; }
	inline bool IsSineWave() const						{ return m_is_sine_wave; }
	inline bool IsExternalFile() const					{ return m_is_external_file; }


	/// 
	/// Overloaded operators
	/// 
	

	friend bool operator<(const VesselDisplacement& obj1, const VesselDisplacement& obj2);
	friend bool operator>(const VesselDisplacement& obj1, const VesselDisplacement& obj2);
	friend bool operator==(const VesselDisplacement& obj1, const VesselDisplacement& obj2);
	friend bool operator!=(const VesselDisplacement& obj1, const VesselDisplacement& obj2);

	VesselDisplacement& operator=(const VesselDisplacement&) = default;
	VesselDisplacement& operator=(VesselDisplacement&&) = default;
};
