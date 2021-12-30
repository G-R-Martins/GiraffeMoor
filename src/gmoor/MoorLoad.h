#pragma once
#include "MathCode.h"

class MoorLoad 
{
protected:
	//============================================================================

	/*-------
	Variables
	--------*/

	//Data type
	Table* m_table;
	MathCode* m_mathCode;
	bool m_is_from_file;
	
	std::string m_file_name;
	unsigned int m_header_lines;
	unsigned int m_n_times;


	/*Node*/

	unsigned int m_node_id;
	unsigned int m_segment_id;
	unsigned int m_line_id;

	//Name -> vessel (ID), first, middle or last (node of segment)
	std::string m_description;

	//Initial step (may encompass more than one)
	unsigned int m_step;

	//============================================================================
public:
	MoorLoad();
	~MoorLoad();
	
			/*-------
			Functions
			--------*/

	//Reads GiraffeMoor file
	bool Read(FILE* f);

	///
	///Set functions
	///
	
	void SetFileOption(bool opt);
	void SetFileName(std::string_view name);
	void SetHeaderLines(unsigned int lines);
	void SetNTimes(unsigned int times);
	void SetNodeID(unsigned int node_id);
	void SetSegment(unsigned int segment_id);
	void SetLineID(unsigned int line_id);
	void SetDescription(std::string_view desc);
	void SetStep(unsigned int initial_step);

	///
	///Get functions
	///
	
	inline Table* GetTable() { return this->m_table; }
	inline MathCode* GetMathCode() { return this->m_mathCode; }

	inline bool GetFileOption() const { return this->m_is_from_file; }
	inline std::string_view GetFileName() const { return this->m_file_name; }
	inline unsigned int GetHeaderLines() const { return this->m_header_lines; }
	inline unsigned int GetNTimes() const { return this->m_n_times; }
	inline unsigned int GetNodeID() const { return this->m_node_id; }
	inline unsigned int GetNodeID() { return this->m_node_id; }
	inline unsigned int GetSegmentID() const { return this->m_segment_id; }
	inline unsigned int GetSegmentID() { return this->m_segment_id; }
	inline unsigned int GetLineID() const { return this->m_line_id; }
	inline unsigned int GetLineID() { return this->m_line_id; }
	inline std::string_view GetDescription() const { return this->m_description; }
	inline unsigned int GetStep() const { return this->m_step; }
	inline unsigned int GetStep() { return this->m_step; }
};