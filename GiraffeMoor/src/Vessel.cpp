#include "PCH.h"
#include "Vessel.h"
#include "Log.h"


//Constructors
Vessel::Vessel()
	: number(0), keypoint(0), node(0), nodeset(0), rigid_nodeset(0), 
	element(0), mass(0.0f), inertiaTensor({ 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 })
{}


//Destructor
Vessel::~Vessel()
{}

//Operators

bool operator< (Vessel& vessel1, Vessel& vessel2)
{
	return vessel1.number < vessel2.number;
}

bool operator> (Vessel& vessel1, Vessel& vessel2)
{
	return !(vessel1 < vessel2);
}

bool operator== (Vessel& vessel1, Vessel& vessel2)
{
	return vessel1.number == vessel2.number;
}

bool operator!= (Vessel& vessel1, Vessel& vessel2)
{
	return !(vessel1 == vessel2);
}


bool Vessel::Read(FILE *f)
{
	//Saves readed keywords and values 
	char str[500];

	//Stream to save current position
	fpos_t pos;
	
	//Tries to read vessel keypoint ID
	if (fscanf(f, "%d %s", &number, str) != EOF && !strcmp(str, "PilotNode"))
	{
		if (fscanf(f, "%s", str) && isalpha(str[0]))
		{
			Log::AddWarning("\n   +Error reading vessel keypoint.\n");
			return false;
		}
		else
			keypoint = atoi(str);
	}
	else
	{
		Log::AddWarning("\n   +Error reading vessel keypoint.\n");
		return false;
	}

	//Tries to read the inertia tensor
	fgetpos(f, &pos);
	if (fscanf(f, "%s", str) && !strcmp(str, "InertiaTensor"))
	{
		if (fscanf(f, "%lf %lf %lf %lf %lf %lf", &inertiaTensor[0], &inertiaTensor[1], &inertiaTensor[2], &inertiaTensor[3], &inertiaTensor[4], &inertiaTensor[5]) /*Rotation inertias*/
			&& !fgetpos(f, &pos) && fscanf(f, "%s %f", str, &mass) && strcmp(str, "Mass")) /*concetrated mass at vessel keypoint*/
			fsetpos(f, &pos); //Mass was not defined
	}
	else //No inertia rotation
		fsetpos(f, &pos);


	//All OK while reading
	return true;
}

