#include "PCH.h"
#include "Seabed.h"


Seabed::Seabed()
	: nodeset(0), stiffness(0.0), damping(0.0), mu(0.0), 
	pinball(0.0), radius(0.0), pilot_node(0)
{}

Seabed::~Seabed()
{}

//Reads input file
bool Seabed::Read(FILE *f)
{
	char str[200];			//salva palavras-chave lidas e valores lidos
	bool readOk = true;
	
	if (fscanf(f, "%s %lf", str, &stiffness) && readOk && strcmp(str, "Stiffness"))		readOk = false;
	else if (fscanf(f, "%s %lf", str, &damping) && readOk && strcmp(str, "Damping"))	readOk = false;
	else if (fscanf(f, "%s %lf", str, &mu) && readOk && strcmp(str, "FrictionCoefficient"))	readOk = false;

	//Error
	if (!readOk)
		return false;

	//All OK while reading
	return true;
}
