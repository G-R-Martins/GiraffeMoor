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
			Log::AddWarning("\n   + Error reading vessel keypoint.\n");
			return false;
		}
		else
			keypoint = atoi(str);
	}
	else
	{
		Log::AddWarning("\n   + Error reading vessel keypoint.\n");
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


void Vessel::AddNode2RigidNodeset(unsigned int n)
{ nodes_rigid_nodeset.emplace(n); }


//Set functions
void Vessel::SetNumber(unsigned int num)
{ this->number = num; }

void Vessel::SetKeypoint(unsigned int kp)
{ this->keypoint = kp; }

void Vessel::SetNode(unsigned int n)
{ this->node = n; }

void Vessel::SetNodeset(unsigned int ns)
{ this->nodeset = ns; }

void Vessel::SetRigidNodeset(unsigned int rigid_ns)
{ this->rigid_nodeset = rigid_ns; }

void Vessel::SetElement(unsigned int elem)
{ this->element = elem; }

void Vessel::SetMass(float m)
{ this->mass = m; }

void Vessel::SetInertiaTensor(const std::array<double, 6>&tensor)
{ this->inertiaTensor = tensor; }

void Vessel::SetNodesRigidNodeset(const std::unordered_set<unsigned int>&nodes)
{ this->nodes_rigid_nodeset = nodes; }


//Get functions
unsigned int Vessel::GetNumber() const
{ return this->number; }

unsigned int Vessel::GetKeypoint() const
{ return this->keypoint; }

unsigned int Vessel::GetNode() const
{ return this->node; }

unsigned int Vessel::GetNodeset() const
{ return this->nodeset; }

unsigned int Vessel::GetRigidNodeset() const
{ return this->rigid_nodeset; }

unsigned int Vessel::GetElement() const
{ return this->element; }

float Vessel::GetMass() const
{ return this->mass; }

std::array<double, 6> const& Vessel::GetInertiaTensor() const
{ return this->inertiaTensor; }

std::unordered_set<unsigned int> const& Vessel::GetNodesRigidNodeset() const
{ return this->nodes_rigid_nodeset; }
std::unordered_set<unsigned int>& Vessel::GetNodesRigidNodeset()
{ return this->nodes_rigid_nodeset; }

