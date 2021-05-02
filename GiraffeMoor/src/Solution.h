#pragma once


class Solution
{
public:
	Solution();
	virtual ~Solution();

	//Interface
	virtual void WriteGiraffeModelFile(FILE *f) = 0;
	
	//============================================================================

	/*-------
	Variables
	--------*/

	//Solution ID
	unsigned int solution_number;
	
	//Solution step start time
	double start_time;
	
	//Solution step end time
	double end_time;
};
