#include "PCH.h"
#include "Connectivity.h"
#include "Cylinder.h"
#include "MooringModel.h"
#include "GiraffeModel.h"

//Mooring model object -> vessel keypoint
extern MooringModel mm;

//Giraffe model object -> generate node, elements, CS, node sets etc...
extern GiraffeModel gm;

//Knot separator
#define SEPARATOR ";"


Connectivity::Connectivity()
{}

Connectivity::~Connectivity()
{
	connectivity_nodes.clear();
}

//Reads input file
bool Connectivity::Read(FILE *f)
{
	//Saves keywords and values readed
	char str[100];

	//Stream with current position
	fpos_t pos;

	/*--------
	Pilot node
	---------*/


	//Checks if a number (pilot node ID) or a word (label) was readed
	if (fscanf(f, "%s", str) != EOF && isalpha(str[0]))
	{
		//Checks for end of file or "ID" keyword
		while (strcmp(str, "PilotID"))
		{
			//If no word has been assigned to the cylinder name
			if (label.size() == 0) label += str;

			//If, at least, one word has been assigned to the cylinder name
			else label = label + " " + str;

			if (fscanf(f, "%s", str) == EOF) return false;
		}
	}

	//Tries to read a cylinder ID 
	if (fscanf(f, "%d", &pilot.ID) != EOF)
	{
		//Specification
		if (fscanf(f, "%s", str))	pilot.specification = str;
		else //ERROR
		{
			std::cout << "[WARNING] Error reading connectivity pilot node.\n";
			return false;
		}
	}
	//If is the vessel keypoint
	else if (!strcmp(str, "vessel") && fscanf(f, "%d", &pilot.ID) != EOF)
	{
		mm.platform_vector.back().AddVesselConnection();
		pilot.specification = str;
	}
	//ERROR
	else
	{
		std::cout << "[WARNING] Error reading connectivity pilot node ID.\n";
		return false;
	}


	/*-----------
	Other node(s)
	------------*/
	
	//ERROR
	if (fscanf(f, "%s", str) && strcmp(str, "NodesID"))
	{
		std::cout << "[WARNING] Error reading nodes connectivity.\n";
		return false;
	}

	//Creates a connectivity structure (with an ID and a specification)
	connectivity_nodes.emplace_back(CylinderConnectivity());
	
	//Checks if is a fairlead connection
	if (fscanf(f, "%s", str) && !strcmp(str, "fairlead")) 
	{
		connectivity_nodes.back().specification = "fairlead";
		fscanf(f, "%d", &connectivity_nodes.back().ID);
	}
	//Checks if an ID number was readed
	else if (isdigit(str[0]))
	{
		//Reads connectivity data from the first node
		connectivity_nodes.back().ID = atoi(str);
		if (fscanf(f, "%s", str)) connectivity_nodes.back().specification = str;

		//Checks for other nodes
		if (!fgetpos(f, &pos) && fscanf(f, "%s", str) && strcmp(str, SEPARATOR))
			fsetpos(f, &pos);
		else
		{
			//Loop to search for other nodes
			while (!strcmp(str, SEPARATOR))
			{
				//Creates a connectivity structure (with an ID and a specification)
				connectivity_nodes.emplace_back(CylinderConnectivity());

				//Reads node connectivity data
				if (fscanf(f, "%d %s", &connectivity_nodes.back().ID, str))	connectivity_nodes.back().specification = str;

				//Checks for end of file and the separator character
				if (!fgetpos(f, &pos) && fscanf(f, "%s", str) == EOF || strcmp(str, SEPARATOR))
				{
					fsetpos(f, &pos);
					break;
				}
			}
		}
	}

	//Neither a fairlead connection nor a number ID
	else return false;
		
	//All of while reading
	return true;
}

//For loop using a lambda function
void Connectivity::ForEachLambda(std::vector<CylinderConnectivity>& NodesVec, 
								 const std::function<void(CylinderConnectivity)>& func)
{
	for (CylinderConnectivity& value : NodesVec)
		func(value);
}

//Push node back in the vector of the nodeset
void Connectivity::PushNodeBack(std::vector<unsigned int>& nodes_list, const unsigned int& plat_num)
{
	for (CylinderConnectivity& cyl_connect : connectivity_nodes)
	{
		if (cyl_connect.specification == "first")
			nodes_list.emplace_back(mm.platform_vector[plat_num].GetSpecificNode(cyl_connect.ID, mm.platform_vector[plat_num].First));
		else if (cyl_connect.specification == "last")
			nodes_list.emplace_back(mm.platform_vector[plat_num].GetSpecificNode(cyl_connect.ID, mm.platform_vector[plat_num].Last));
		else if (cyl_connect.specification == "middle")
			nodes_list.emplace_back(mm.platform_vector[plat_num].GetSpecificNode(cyl_connect.ID, mm.platform_vector[plat_num].Middle));
	}
}

		/*-----------
		GET functions
		------------*/

//Returns the pilot node specification
const std::string& Connectivity::GetPilotSpecification() const
{
	return this->pilot.specification;
}

//Returns the connectivity label
const std::string& Connectivity::GetLabel() const
{
	return this->label;
}

//Returns the pilot node ID
unsigned int Connectivity::GetPilotID() const
{
	return this->pilot.ID;
}

//Returns the node specification
const std::string& Connectivity::GetNodeSpecification(const unsigned int& node) const
{
	return this->connectivity_nodes[node].specification;
}

//Returns the node ID
unsigned int Connectivity::GetNodeID(const unsigned int& node) const
{
	return this->connectivity_nodes[node].ID;
}
