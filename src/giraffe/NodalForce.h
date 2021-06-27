#pragma once
#include "Load.h"
#include "MathCode.h"


class NodalForce : public Load
{
public:
	NodalForce();
	~NodalForce();
	NodalForce(Table* time_series);
	NodalForce(MathCode* mc);
	NodalForce(const std::string& f_name, const unsigned int& h_lines, const unsigned int& ntimes);
	NodalForce(std::string_view f_name, const unsigned int& h_lines, const unsigned int& ntimes);

	//============================================================================

			/*-------
			Functions
			--------*/

	//Writes Giraffe file
	void WriteGiraffeModelFile(std::ostream& fout) const override;
	
	//============================================================================

			/*-------
			Variables
			--------*/
		
	//Data pointer
	Table* table;
	MathCode* mathCode;
	//External file
	std::string file_name;
	unsigned int header_lines, n_times;

	//Node set
	unsigned int nodeset;
};

///TODO: unique ptr