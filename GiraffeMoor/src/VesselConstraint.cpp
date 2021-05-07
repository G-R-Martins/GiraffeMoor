#include "PCH.h"
#include "VesselConstraint.h"
#include "Log.h"


VesselConstraint::VesselConstraint()
	: number(0), constraints(6)
{}

VesselConstraint::~VesselConstraint()
{}

//Reads input file
bool VesselConstraint::Read(FILE *f)
{
	//Keeps readed words and numbers
	char str[10];

	//Stream to save position
	fpos_t pos;

	//Tries to read the first coordinate keyword
	if (fscanf(f, "%d %s", &number, str) == EOF)
	{
		Log::AddWarning("\n   + Error reading vessel ID at 'VesselConstraint' block.");
		return false;
	}

	while (true)
	{
		int i;
		if (!strcmp(str, "X")) i = 0;
		else if (!strcmp(str, "Y")) i = 1;
		else if (!strcmp(str, "Z")) i = 2;
		else if (!strcmp(str, "ROTX")) i = 3;
		else if (!strcmp(str, "ROTY")) i = 4;
		else if (!strcmp(str, "ROTZ")) i = 5;
		else
		{
			fsetpos(f, &pos);
			return true;
		}
		
		//Current constraint
		while (true)
		{
			//Saves position
			fgetpos(f, &pos);

			//Tries to read a number (1 or 0)
			if (fscanf(f, "%9s", str) && isdigit(str[0]))
			{
				bool add = ( str[0] == '1' ) ? true : false;
				constraints[i].push_back(add);
			}
			//No constraint defined for the current DOF
			else if (constraints[i].empty())
			{
				std::string warning = "\n   + There is at least one DOF of the vessel number " + std::to_string(number) + "with no constraint defined.";
				Log::AddWarning(warning);
				return false;
			}
			//It can be other keyword
			else
				break;
		}

	}

	return true;
}

/*-----------
Get functions
-----------*/

unsigned int VesselConstraint::GetSizeX()
{
	return ( unsigned int )this->constraints[0].size();
}

unsigned int VesselConstraint::GetSizeY()
{
	return ( unsigned int )constraints[1].size();
}

unsigned int VesselConstraint::GetSizeZ()
{
	return ( unsigned int )this->constraints[2].size();
}

unsigned int VesselConstraint::GetSizeRotX()
{
	return ( unsigned int )this->constraints[3].size();
}

unsigned int VesselConstraint::GetSizeRotY()
{
	return ( unsigned int )this->constraints[4].size();
}

unsigned int VesselConstraint::GetSizeRotZ()
{
	return ( unsigned int )this->constraints[5].size();
}

/*const bool VesselConstraint::GetX(const int& i)
{
	return x[i];
}

const bool VesselConstraint::GetY(const int& i)
{
	return y[i];
}

const bool VesselConstraint::GetZ(const int& i)
{
	return z[i];
}

const bool VesselConstraint::GetRotX(const int& i)
{
	return rotx[i];
}

const bool VesselConstraint::GetRotY(const int& i)
{
	return roty[i];
}

const bool VesselConstraint::GetRotZ(const int& i)
{
	return rotz[i];
}*/

//Overloaded operators
bool operator<(const VesselConstraint& vessel1, const VesselConstraint& vessel2)
{
	return vessel1.number < vessel2.number;
}

bool operator>(const VesselConstraint& vessel1, const VesselConstraint& vessel2)
{
	return vessel1.number > vessel2.number;
}

bool operator==(const VesselConstraint& vessel1, const VesselConstraint& vessel2)
{
	return vessel1.number == vessel2.number;
}

bool operator!=(const VesselConstraint& vessel1, const VesselConstraint& vessel2)
{
	return vessel1.number != vessel2.number;
}
