#include "PCH.h"
#include "ConcentratedMass.h"


ConcentratedMass::ConcentratedMass()
	:ID_cylinder(0), local_node(0), global_node(0), concentrated_mass(0.0)
{}

ConcentratedMass::~ConcentratedMass()
{}

bool ConcentratedMass::Read(FILE *f)
{
	//Saves keywords and values readed
	char str[250];

	//Checks if there is a label (used as a comment to rigid body data and element)
	if (fscanf(f, "%s", str) != EOF && isalpha(str[0]))
	{
		//Checks for end of file or "ID" keyword
		while (strcmp(str, "Body"))
		{
			//If no word has been assigned to the cylinder name
			if (label.size() == 0) label += str;

			//If, at least, one word has been assigned to the cylinder name
			else label = label + " " + str;

			if (fscanf(f, "%s", str) == EOF) return false;
		}
	}

	//Checks if the body has been identified
	if (!strcmp(str, "Body"))
		auto ret = fscanf(f, "%d", &ID_cylinder);
	else
	{
		std::cout << "[WARNING] Please define the body identification for concentrated mass.\n";
		return false;
	}

	//Checks if the number of the local node has been identified
	if (fscanf(f, "%s", str) && !strcmp(str, "NodeID"))
		auto ret = fscanf(f, "%d", &local_node);
	else
	{
		std::cout << "[WARNING] Please define the local node identification for concentrated mass.\n";
		return false;
	}

	//Checks if the concentrated mass has been identified
	if (fscanf(f, "%s", str) && !strcmp(str, "Mass"))
		auto ret = fscanf(f, "%lf", &concentrated_mass);
	else
	{
		std::cout << "[WARNING] Please define the concentrated mass.\n";
		return false;
	}


	//All ok while reading
	return true;
}

	/*-------------------
	Setting private data
	--------------------*/

void ConcentratedMass::SetGlobalNode(const unsigned int& node)
{
	global_node = node;
}

	/*-------------------
	Accesing private data
	--------------------*/

unsigned int ConcentratedMass::GetCylinderID() const
{
	return this->ID_cylinder;
}

unsigned int ConcentratedMass::GetLocalNodeID() const
{
	return this->local_node;
}

unsigned int ConcentratedMass::GetGlobalNodeID() const
{
	return this->global_node;
}

double ConcentratedMass::GetMass() const
{
	return this->concentrated_mass;
}

const std::string& ConcentratedMass::GetLabel() const
{
	return this->label;
}