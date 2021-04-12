#include "PCH.h"
#include "AnchorConstraint.h"
#include "Log.h"

AnchorConstraint::AnchorConstraint()
	: number(0), nodeset(0), rotx(0), roty(0), rotz(0)
	{}

AnchorConstraint::~AnchorConstraint()
{}

//Overloaded operators
bool operator< (const AnchorConstraint& anchor1, const  AnchorConstraint& anchor2)
{
	return anchor1.number < anchor2.number;
}

bool operator> (const AnchorConstraint& anchor1, const  AnchorConstraint& anchor2)
{
	return anchor1.number > anchor2.number;
}

bool operator== (const AnchorConstraint& anchor1, const  AnchorConstraint& anchor2)
{
	return anchor1.number == anchor2.number;
}

bool operator!= (const AnchorConstraint& anchor1, const  AnchorConstraint& anchor2)
{
	return anchor1.number != anchor2.number;
}

//Reads input file
bool AnchorConstraint::Read(FILE *f)
{
	char str[200];			//salva palavras-chave lidas e valores lidos
	

	if (fscanf(f, "%d", &number) == EOF)
	{
		Log::AddWarning("\n   +Error reading a line number\n");
		return false;
	}

	if (fscanf(f, "%s %d %d %d", str, &rotx, &roty, &rotz) == EOF || strcmp(str, "Rotations"))
	{
		std::string warning = "\n   +Error reading the constraint of the line number " + std::to_string(number);
		Log::AddWarning(warning);
		return false;
	}

	//All OK while reading
	return true;
}
