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
	Table* table;
	MathCode* mathCode;
	bool fromFile;
	
	std::string file_name;
	unsigned int header_lines, n_times;


	/*Node*/

	unsigned int nodeID;
	unsigned int segmentID;
	size_t lineID;

	//Name -> vessel (ID), first, middle or last (node of segment)
	std::string description;

	//Initial step (may encompass more than one)
	unsigned int step;

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
	void SetNodeID(unsigned int node);
	void SetSegment(unsigned int segment);
	void SetLineID(size_t line_ID);
	void SetDescription(std::string_view desc);
	void SetStep(unsigned int initial_step);

	///
	///Get functions
	///
	
	Table* GetTable();
	MathCode* GetMathCode();

	bool GetFileOption() const;
	std::string_view GetFileName() const;
	unsigned int GetHeaderLines() const;
	unsigned int GetNTimes() const;
	unsigned int GetNodeID() const;
	unsigned int GetNodeID();
	unsigned int GetSegmentID() const;
	unsigned int GetSegmentID();
	size_t GetLineID() const;
	size_t GetLineID();
	std::string_view GetDescription() const;
	unsigned int GetStep() const;
	unsigned int GetStep();

};