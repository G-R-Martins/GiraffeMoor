#include "PCH.h"
#include "Platform.h"
#include "LoopReading.h"
#include "GiraffeModel.h"

extern GiraffeModel gm;



Platform::Platform()
	: number(0), node0(0), tot_nodes(0), vessel_connections(0), vessel_ID(0)
{}

Platform::~Platform()
{}

/*-------------------
 Overloaded operators
 -------------------*/

bool operator< (Platform& plat1, Platform& plat2)
{
	return plat1.number < plat2.number;
}

bool operator> (Platform& plat1, Platform& plat2)
{
	return !(plat1 < plat2);
}

bool operator== (Platform& plat1, Platform& plat2)
{
	return plat1.number == plat2.number;
}

bool operator!= (Platform& plat1, Platform& plat2)
{
	return !(plat1 == plat2);
}


//Reads input file
bool Platform::Read(FILE *f)
{

	typedef std::unordered_set<std::string_view> uset;

	//Saves keywords and values readed
	char str[500];
	
	//Saves current position
	fpos_t pos;

	//Container with lower level keywords (ConcentratedMass is not mandatory)
	uset sub_keyword({ "Connectivity", "ConcentratedMass" , "Platform"});

	//Platform and vessel numbers
	if (fscanf(f, "%d %s %d", &number, str, &vessel_ID) == EOF || strcmp(str, "VesselID"))
	{
		std::cout << "[WARNING] Error reading platform data.\n";
		return false;
	}
	//Read cylinders
	else if (!LoopReading::TryNestedKeyword(cylinders_container, uset({ "ID" }), sub_keyword, f, pos, str))
		return false;


	//Searches for comment block before "Connectivity" and "ConcentratedMass"
	AuxFunctions::Read::TryComment(f);

	uset::iterator it;
	//Loop to read solution parameters
	while (!fgetpos(f, &pos) && fscanf(f, "%s", str) != EOF)
	{
		it = sub_keyword.find(std::string(str));
		if (it != sub_keyword.end())
		{
			if (*it == "Connectivity")
			{
				sub_keyword.erase("Connectivity");
				if (!LoopReading::TryNestedKeyword_UnorderedMultiple(connectivity_container, uset({ "PilotID", "Label" }), sub_keyword, f, pos, str))
					return false;
			}
			else if (*it == "ConcentratedMass")
			{
				sub_keyword.erase("ConcentratedMass");
				if (!LoopReading::TryNestedKeyword_UnorderedMultiple(concentrated_mass_container, uset({ "Body", "Label" }), sub_keyword, f, pos, str))
					return false;
			}
			else if (*it == "Platform")
			{
				fsetpos(f, &pos);
				return true;
			}
		}
		else if (str[0] == '/' && AuxFunctions::Read::Comment(f, str));
		//Other word -> end loop and backs to IO class
		else
		{
			fsetpos(f, &pos);
			break;
		}
	}

	//Checks if the connectivity rules were defined
	if (sub_keyword.find("Connectivity") != sub_keyword.end())
	{
		std::cout << "[WARNING] The connectivity for the platform number " << number << "was not defined.\n";
		return false;
	}


	//All ok while reading
	return true;
}

//Generates rigid body elements from concentrated mass(es)
bool Platform::GenerateRigidBodyElements(unsigned int& element, unsigned int& nodeset, unsigned int &rb_data, unsigned int &special_constraint, unsigned int &nodal_constraint) const
{
	///TODO: 'GenerateRigidBodyData' para plataformas em EF
	//Generates rigid bodies data and elements
	//unsigned int rb_data = 0;
	for (const Cylinder& cyl : cylinders_container)
	{
		//Checks if there is a concentrated mass at the first node
		if (cyl.BoolFirstNodeMass())
		{
			//Generates Giraffe RB data
			//gm.GenerateRigidBodyData(++rb_data, cyl.GetFirstNodeMass(), { 0.,0.,0.,0.,0.,0. }, { 0.,0.,0. }, "", cyl.GetName());

			//Generates Giraffe element
			gm.GenerateRigidBodyElement(element++, rb_data, 1, cyl.GetFirstNode(), cyl.GetName());
		}
		//Checks if there is a concentrated mass at the last node
		if (cyl.BoolLastNodeMass())
		{
			//Generates Giraffe RB data
			//gm.GenerateRigidBodyData(++rb_data, cyl.GetLastNodeMass(), { 0.,0.,0.,0.,0.,0. }, { 0.,0.,0. }, "", cyl.GetName());

			//Generates Giraffe element
			gm.GenerateRigidBodyElement(element++, rb_data, 1, cyl.GetLastNode(), cyl.GetName());
		}
	}

	//Generates RB and elements of ballast(s)
	for (const ConcentratedMass& conc_mass : concentrated_mass_container)
	{
		//Generates Giraffe RB data
		//gm.GenerateRigidBodyData(++rb_data, conc_mass.GetMass(), { 0.,0.,0.,0.,0.,0. }, { 0.,0.,0. }, "", conc_mass.GetLabel());
		
		//Generates Giraffe element
		gm.GenerateRigidBodyElement(element++, rb_data, 1,
									cylinders_container[conc_mass.GetCylinderID() - 1].GetFirstNode() + ( conc_mass.GetLocalNodeID() - 1 ),
									conc_mass.GetLabel());
	}

	return true;
}

//Generates node sets, rigid node sets 
bool Platform::GenerateNodeSetsSpecialConstraints(unsigned int &nodeset, unsigned int &nodal_constraint, unsigned int &special_constraint)
{
	//Generates platform node sets, special constraints
	for (Connectivity& plat_connect : connectivity_container)
	{
		//Checks if is neither a fairlead connection nor a vessel connection
		if (plat_connect.GetNodeSpecification(0) != "fairlead" && plat_connect.GetPilotSpecification() != "vessel")
		{
			//Vector with node(s) of the node set
			std::vector<unsigned int> nodes_list;
			
			//Mount vector with node(s) of the node set
			plat_connect.PushNodeBack(nodes_list, this->number);
			
			//Node set booltable
			BoolTable BT(false, 3);

			//Generates node set
			gm.GenerateNodeSet(nodeset, nodes_list, plat_connect.GetLabel().c_str());

			//Local specification of the pilot node (first, middle or last node of the cylinder)
			if (plat_connect.GetPilotSpecification() == "first")
				gm.GenerateRigidNodeSet(special_constraint++, cylinders_container[plat_connect.GetPilotID() - 1].GetFirstNode(), nodeset++, BT, plat_connect.GetLabel());
			else if (plat_connect.GetPilotSpecification() == "last")
				gm.GenerateRigidNodeSet(special_constraint++, cylinders_container[plat_connect.GetPilotID() - 1].GetLastNode(), nodeset++, BT, plat_connect.GetLabel());
			else //middle
				gm.GenerateRigidNodeSet(special_constraint++,
				( cylinders_container[plat_connect.GetPilotID() - 1].GetLastNode() + cylinders_container[plat_connect.GetPilotID() - 1].GetFirstNode() ) / 2,
										nodeset++, BT, plat_connect.GetLabel());
		}
	}

	//Generates a node set with all nodes of the platform and its nodal constraint
	///Giraffe node set
	gm.GenerateNodeSet(nodeset, tot_nodes, node0, 1, "All nodes of the platform");
	///Node set booltable
	BoolTable BT(true, 3);
	///Giraffe constraint
	gm.GenerateNodalConstraint(++nodal_constraint, nodeset++, BT, BT, BT, BT, BT, BT);

	return true;
}

//Generates fairleads nodal constraints and rigid node sets
bool Platform::FairleadsNodalConstraintsNodeSets(unsigned int &nodeset, unsigned int &nodal_constraint, const int& max_fairleads) const
{
	//Fairleads counter
	int cont_fairleads = 0;

	//Iterates in search of fairleads
	for (const Connectivity& plat_connect : connectivity_container)
	{
		if (plat_connect.GetNodeSpecification(0) == "fairlead")
		{
			//Generates nodal constraint
			///Booltables
			BoolTable U, ROT;
			U.Set(4, true, true, true, false);
			ROT.Set(4, false, true, true, false);
			///Generates Giraffe constraint
			gm.GenerateNodalConstraint(++nodal_constraint, ++nodeset, U, U, U, ROT, ROT, ROT);
		}
		//Check if all fairleads constraints have already been created
		if (++cont_fairleads == max_fairleads) break;
	}

	return true;
}

//Adds a vessel connection (it is actualized during "Connectivity" reading)
void Platform::AddVesselConnection()
{
	++this->vessel_connections;
}

//Generates fairleads nodal constraints
bool Platform::VesselNodalConstraint(unsigned int &nodeset, unsigned int &nodal_constraint)
{
	//All booltables are the same for the vessel
	BoolTable BT(true, 3);
	
	//Generates Giraffe constraint
	gm.GenerateNodalConstraint(nodal_constraint, nodeset, BT, BT, BT, BT, BT, BT);

	return true;
}

//Generates vessel rigid node set
bool Platform::VesselRigidNodeset(unsigned int& nodeset, unsigned int& special_constraint, const std::vector<Vessel>& vessel_vector)
{
	//Vessel connections counter
	int cont_connections = 0;

	//Iterates in search of vessel connection(s)
	for (Connectivity& plat_connect : connectivity_container)
	{
		if (plat_connect.GetPilotSpecification() == "vessel")
		{

			//Vector with node(s) of the node set
			std::vector<unsigned int> nodes_list;

			//Mount vector with node(s) of the node set
			plat_connect.PushNodeBack(nodes_list, this->number);

			//Node set booltable
			BoolTable BT(false, 3);

			//Generates node set
			gm.GenerateNodeSet(nodeset, nodes_list, plat_connect.GetLabel().c_str());

			//Generates rigid node set special constraint
			gm.GenerateRigidNodeSet(special_constraint++, vessel_vector[this->vessel_ID - 1].node, nodeset++, BT, plat_connect.GetLabel());
		
			//Check if all fairleads constraints have already been created
			if (++cont_connections == this->vessel_connections) break;
		}
	}

	return true;
}

//Generates fairleads connections (same displacement)
bool Platform::FairleadsConnections(unsigned int& special_constraint, const std::vector<Line>& line_vector) const
{
	//Count fairleads generated
	unsigned int cont_fairleads = 0;
	
	for (const Connectivity& plat_connect : this->connectivity_container)
	{
		//Checks if is neither a fairlead connection nor a vessel connection
		if (plat_connect.GetNodeSpecification(0) == "fairlead")
		{
			//Node set booltable
			BoolTable BT(false, 2);

			//Local specification of the node (first, middle or last node of the cylinder)
			NodeSpecification cur_pilot_specification;
			if (plat_connect.GetPilotSpecification() == "first")
				cur_pilot_specification = First;
			else if (plat_connect.GetPilotSpecification() == "last")
				cur_pilot_specification = Last;
			else 
				cur_pilot_specification = Middle;

			//Generates rigid node set special constraint
			gm.GenerateSameDisplacement(special_constraint++, 
										GetSpecificNode(plat_connect.GetPilotID(), cur_pilot_specification), 
										line_vector[plat_connect.GetNodeID(0) - 1].node_B, BT);

			//Checks if all fairleads has been generated
			if (++cont_fairleads == line_vector.size()) break;
		}
	}

	return true;
}

//Generates coordinate systems, nodes and elements (except rigid bodies for concentrated mass)
bool Platform::GenerateCSNodesElements(unsigned int& node, unsigned int& element, unsigned int& CoordSystem, const std::vector<SegmentProperty>& segment_property_vector)
{
	//Platform first node
	SetPlatformFirstNode(node + 1);

	//Generates platform coordinate systems
	for (Cylinder& cyl : cylinders_container)
	{
		//Set projection, total length and element(s) length(s)
		cyl.SetGeneralCylinderData();

		//Cylinder length
		double length = cyl.GetLength();

		//Components of the versor E3
		double e31 = cyl.GetProjX() / length;
		double e32 = cyl.GetProjY() / length;
		double e33 = cyl.GetProjZ() / length;
		//double mod3 = sqrt(pow(e1, 2.0) + pow(e2, 2.0) + pow(e3, 2.0));
		//double e31 = e1 / mod3;
		//double e32 = e2 / mod3;
		//double e33 = e3 / mod3;

		//Checks if current CS does not coincides with the global CS
		if (e31 != 0.0 || e32 != 0.0 || e33 != 1.0)
		{
			//Modulus of versor E1
			//double mod1 = sqrt(pow(e33, 2.0) + pow(e32, 2.0));
			//Components of the versor E1
			double e11 = 0.0, e12 = -e33, e13 = e32;

			//Versores
			Matrix E1(3); 
			Matrix E3(3);
			E1(0, 0) = e11; 
			E1(1, 0) = e12; 
			E1(2, 0) = e13;
			E3(0, 0) = e31; 
			E3(1, 0) = e32; 
			E3(2, 0) = e33;

			//Generates Giraffe CS
			gm.GenerateCoordinateSystem(CoordSystem, E1, E3);

			//Assigns cylinder CS ID
			cyl.SetCoordinateSystem(CoordSystem);
			++CoordSystem;
		}
	}

	//Generates platform nodes and elements
	tot_nodes = 0;
	for (auto cyl = cylinders_container.begin(); cyl != cylinders_container.end(); cyl++)
	{
		//Element property
		unsigned int prop_ID = cyl->GetID();
		char elem_type = segment_property_vector[( size_t )prop_ID - 1].type;
		cyl->SetCylinderType(elem_type);

		//Updates the number of nodes
		int n = elem_type == 'b' ? 2 : 1;
		tot_nodes += n * cyl->GetDiscretization() + 1;
		
		/*------------------------------
		Elements of the current cylinder
		------------------------------*/
		
		//Beam elements
		if (elem_type == 'b')
		{
			for (unsigned int cyl_element = 1; cyl_element <= cyl->GetDiscretization(); cyl_element++)
			{
				bool bool_first_element = false;
				//First node
				if (cyl_element == 1)
				{
					bool_first_element = true;
					cyl->SetFirstNode(++node);
					gm.GenerateNode(node, cyl->GetFirstNodeCoordinates().X, cyl->GetFirstNodeCoordinates().Y, cyl->GetFirstNodeCoordinates().Z, cyl->GetName().c_str());
				}

				//Generates nodes
				gm.GenerateNode(++node, cyl->GetFirstNodeCoordinates().X + ( cyl_element - 0.5 ) * cyl->GetDX(),
								cyl->GetFirstNodeCoordinates().Y + ( cyl_element - 0.5 ) * cyl->GetDY(),
								cyl->GetFirstNodeCoordinates().Z + ( cyl_element - 0.5 ) * cyl->GetDZ());
				gm.GenerateNode(++node, cyl->GetFirstNodeCoordinates().X + ( cyl_element )*cyl->GetDX(),
								cyl->GetFirstNodeCoordinates().Y + ( cyl_element )*cyl->GetDY(),
								cyl->GetFirstNodeCoordinates().Z + ( cyl_element )*cyl->GetDZ());

				//Checks if is the last element and set the last node
				if (cyl_element == cyl->GetDiscretization())
					//unsigned int temp_node = node;
					cyl->SetLastNode(node);

				//Generates element
				gm.GeneratePipeElement(element++, bool_first_element, prop_ID, cyl->GetCS(), node - 2, node - 1, node - 0);
			}
		}
		//Truss elements
		else
		{
			for (unsigned int cyl_element = 1; cyl_element <= cyl->GetDiscretization(); cyl_element++)
			{
				bool bool_first_element = false;
				//First node
				if (cyl_element == 1)
				{
					bool_first_element = true;
					cyl->SetFirstNode(++node);
					gm.GenerateNode(node, cyl->GetFirstNodeCoordinates().X, cyl->GetFirstNodeCoordinates().Y, cyl->GetFirstNodeCoordinates().Z, cyl->GetName().c_str());
				}

				//Generates node
				gm.GenerateNode(++node, cyl->GetFirstNodeCoordinates().X + ( cyl_element )*cyl->GetDX(),
								cyl->GetFirstNodeCoordinates().Y + ( cyl_element )*cyl->GetDY(),
								cyl->GetFirstNodeCoordinates().Z + ( cyl_element )*cyl->GetDZ());

				//Checks if is the last element and set the last node
				if (cyl_element == cyl->GetDiscretization())
					//unsigned int temp_node = node;
					cyl->SetLastNode(node);

				//Generates element
				gm.GenerateTrussElement(element++, bool_first_element, prop_ID, node - 1, node, cyl->GetName());

			}
		}
	}

	//All ok
	return true;
}

void Platform::SetPlatformFirstNode(const unsigned int& node) const
{
	node0 = node;
}

//Get number of a specific node of a specific cylinder
unsigned int Platform::GetSpecificNode(const unsigned int& cylinderID, const NodeSpecification& specification) const
{
	switch (specification)
	{
	case First:
		return cylinders_container[cylinderID - 1].GetFirstNode();
	case Middle:
		return ( cylinders_container[cylinderID - 1].GetLastNode() + cylinders_container[cylinderID - 1].GetFirstNode() ) / 2;
	case Last:
		return cylinders_container[cylinderID - 1].GetLastNode();

	default:
		return 0;
	}
}

//Get the number of the vessel
unsigned int Platform::GetVesselNumber()
{
	return this->vessel_ID;
}
