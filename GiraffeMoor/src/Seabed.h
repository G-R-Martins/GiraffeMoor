#pragma once


class Seabed
{
public:
	Seabed();
	~Seabed();

	//Reads GiraffeMoor file
	bool Read(FILE *f);

	//============================================================================

	/*-------
	Variables
	--------*/

	//Seabed nodeset ID
	unsigned int nodeset;

	//Seabed stiffness (used for penetration and NSSS contact)
	double stiffness;

	//Seabed damping
	double damping;

	//Seabed friction coefficient
	double mu;

	//Seabed pinball value
	double pinball;

	//Seabed radius value (NSSS contact)
	double radius;

	//Boolean to indicate if seabed is flat
	bool flatseabed = true;

	//Seabed pilot node ID
	unsigned int pilot_node;
};

