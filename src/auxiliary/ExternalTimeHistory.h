#pragma once
#include "MathCode.h"
#include "Table.h"


class ExternalTimeHistory
{
private:
	unsigned int m_solution_step_id;

	//Boolean to indicate the type of the displacement
	bool m_is_table;
	bool m_is_math_code;
	bool m_is_external_file;

	//External file
	std::string m_file_name;
	unsigned int m_header_lines;  //in the external csv/txt file 
	unsigned int m_tot_steps;  //lines in the csv/txt file

	//Data type
	Table* m_ptr_time_series;
	MathCode* m_ptr_math_code;

	//Booleans to indicate which types were defined
	bool m_description_defined;
	bool m_id_defined;
	bool m_segment_id_defined;
	bool m_type_defined;  // MathCode, TimeSeries, or File
	bool m_step_defined;

public:
	ExternalTimeHistory();
	~ExternalTimeHistory();


	///
	/// SETTERS
	///

	void SetSolutionStep(unsigned int solution_step_id);
	void SetStartTime(double start);

	void SetStartTableTime(double start_time, unsigned int start_line);
	void SetTimeSeries();
	void SetTimeSeries(Table* ptr_time_series);

	void SetMathCode();

	void SetFileOption(bool opt);
	void SetFileName(const std::string& file_name);
	void SetFileHeaders(unsigned int header_lines);
	void SetFileNSteps(unsigned int tot_steps);
	
	void SetDescriptionOpt(bool opt);
	void SetIDOpt(bool opt);
	void SetSegmentIDOpt(bool opt);
	void SetTypeOpt(bool opt);
	void SetSolutionStepOpt(bool opt);

	///
	/// GETTERS
	///

	inline unsigned int GetStep() const { return m_solution_step_id; }

	inline unsigned int GetNHeaderLines() const { return m_header_lines; }
	inline unsigned int GetNSteps() const { return m_tot_steps; }
	inline std::string& GetFileName() { return m_file_name; }

	inline Table* GetTimeSeries() const { return m_ptr_time_series; }
	inline Table* GetTimeSeries() { return m_ptr_time_series; }
	inline MathCode* GetMathCode() const { return m_ptr_math_code; }
	inline MathCode* GetMathCode() { return m_ptr_math_code; }

	inline bool IsTable() const { return m_is_table; }
	inline bool IsMathCode() const { return m_is_math_code; }
	inline bool IsExternalFile() const { return m_is_external_file; }

	inline bool DescriptionIsDefined() const { return this->m_description_defined; }
	inline bool IDIsDefined() const { return this->m_id_defined; }
	inline bool SegmentIDIsDefined() const { return this->m_segment_id_defined; }
	inline bool TypeIsDefined() const { return this->m_type_defined; }
};

