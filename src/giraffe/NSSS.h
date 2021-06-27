#pragma once
#include "Contact.h"
#include "BoolTable.h"


class NSSS : public Contact
{
public:
	NSSS();
	~NSSS();

	//Writes Giraffe file
	void WriteGiraffeModelFile(std::ostream& fout) const override;

	//============================================================================

	/*-------
	Variables
	--------*/

	//NSSS ID
	unsigned int number;

	//Node set ID
	unsigned int node_set;

	//Surface set ID
	unsigned int surface_set;

	//Friction coefficient
	double mu;
	double epn;
	double cn;
	double ept;
	double ct;

	//Pinball
	double pinball;
	
	//Radius
	double radius;
	unsigned int max_interactions;

	//Current NSSS booltable
	BoolTable bool_table;
};

