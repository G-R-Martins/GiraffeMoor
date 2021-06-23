#include "PCH.h"
#include "Cylinder.h"


Cylinder::Cylinder()
	: ID(0), propertyID(0), discretization(0), CS(1), length(0.0), 
	ProjX(0.0), ProjY(0.0), ProjZ(0.0), DX(0.0), DY(0.0), DZ(0.0)
{}

Cylinder::~Cylinder()
{}

//Overloaded operators
bool operator<(const Cylinder& obj1, const Cylinder& obj2)
{
	return obj1.ID < obj2.ID;
}

bool operator>(const Cylinder& obj1, const Cylinder& obj2)
{
	return obj1.ID > obj2.ID;;
}

bool operator==(const Cylinder& obj1, const Cylinder& obj2)
{
	return obj1.ID == obj2.ID;;
}

bool operator!=(const Cylinder& obj1, const Cylinder& obj2)
{
	return obj1.ID != obj2.ID;
}


bool Cylinder::Read(FILE *f)
{
	//Saves keywords and values readed
	char str[500];
	
	//Stream with current position
	fpos_t pos;

	//Checks if Cylinder ID is a letter has been readed
	if (fscanf(f, "%s", str) && isalpha(str[0])) //ERROR
	{
		std::cout << "[WARNING] Error reading cylinder ID number.\n";
		return false;
	}
	else
		ID = atoi(str);
	
	
	//Reads cylinder data
	while (true)
	{
		//Checks for end of file and "Property"
		if (fscanf(f, "%s", str) == EOF || !strcmp(str, "Property")) break;
		
		//If no word has been assigned to the cylinder name
		if (name.size() == 0) name += str;

		//If, at least, one word has been assigned to the cylinder name
		else name = name + " " + str;
	}

	//Reading property
	if (!strcmp(str, "Property"))
		fscanf(f, "%d", &propertyID);
	else //ERROR
	{
		std::cout << "[WARNING] Error reading property of cylinder number "<< ID << " .\n";
		return false;
	}

	//Reads discretization
	if (fscanf(f, "%s", str) && !strcmp(str, "Discretization"))
		fscanf(f, "%d", &discretization);
	else //ERROR
	{
		std::cout << "[WARNING] Error reading discretization of cylinder number " << ID << " .\n";
		return false;
	}

	//Reads cylinder start
	if (fscanf(f, "%s", str) && !strcmp(str, "Begin"))
	{
		//Coordinates
		fscanf(f, "%lf %lf %lf", &begin.X, &begin.Y, &begin.Z);

		//Checks for concentrated mass
		fgetpos(f, &pos);
		if (fscanf(f, "%s", str) && !strcmp(str, "Mass"))
			fscanf(f, "%f", &begin.mass);
		else //No concentrated mass
			fsetpos(f, &pos);
	}
	else //ERROR
	{
		std::cout << "[WARNING] Error reading beginning of cylinder number " << ID << " .\n";
		return false;
	}

	//Reads cylinder end
	if (fscanf(f, "%s", str) && !strcmp(str, "End"))
	{
		//Coordinates
		if (fscanf(f, "%lf %lf %lf", &end.X, &end.Y, &end.Z))
		{
		//Checks for concentrated mass
			fgetpos(f, &pos);
			if (fscanf(f, "%s", str) && !strcmp(str, "Mass"))
				fscanf(f, "%f", &end.mass);
			else //No concentrated mass
				fsetpos(f, &pos);
		}
	}
	else
	{
		std::cout << "[WARNING] Error reading beginning of cylinder number " << ID << " .\n";
		return false;
	}

	//All ok while reading
	return true;
}

		/*-----------
		SET functions
		------------*/

//Set coordinate system
void Cylinder::SetCoordinateSystem(unsigned int CS) 
{
	this->CS = CS;
}

//Set data
void Cylinder::SetGeneralCylinderData()
{
	//Projections
	SetProjX();
	SetProjY();
	SetProjZ();

	//Total length
	SetLength();

	//Element(s) length
	SetDX();
	SetDY();
	SetDZ();
}

//Cylinder total length
void Cylinder::SetLength()
{
	length = sqrt(pow(GetProjX(), 2) + pow(GetProjY(), 2) + pow(GetProjZ(), 2));
}

//Cylinder first node
void Cylinder::SetFirstNode(unsigned int& node)
{
	this->begin.node = node;
}

//Cylinder last node
void Cylinder::SetLastNode(unsigned int& node)
{
	this->end.node = node;
}

//X-axis projection 
void Cylinder::SetProjX()
{
	ProjX = end.X - begin.X;
}

//Y-axis projection 
void Cylinder::SetProjY()
{
	ProjY = end.Y - begin.Y;
}

//Z-axis projection 
void Cylinder::SetProjZ()
{
	ProjZ = end.Z - begin.Z;
}

//A single element length at the X direction
void Cylinder::SetDX()
{
	DX = GetProjX() / discretization;
}

//A single element length at the Y direction
void Cylinder::SetDY()
{
	DY = GetProjY() / discretization;
}

//A single element length at the Z direction
void Cylinder::SetDZ()
{
	DZ = GetProjZ() / discretization;
}

void Cylinder::SetCylinderType(char &temp)
{
	type = temp;
}

		/*-----------
		GET functions
		------------*/

//Cylinder total length
double Cylinder::GetLength() const
{
	return this->length;
}
double Cylinder::GetLength()
{
	return this->length;
}

//Number of elements
unsigned int Cylinder::GetDiscretization() const
{
	return this->discretization;
}

//Cylinder first node
unsigned int Cylinder::GetFirstNode() const
{
	return this->begin.node;
}

//Cylinder last node
unsigned int Cylinder::GetLastNode() const
{
	return this->end.node;
}

//Cylinder name
const std::string& Cylinder::GetName() const
{
	return this->name;
}

//Cylinder property ID
unsigned int Cylinder::GetID() const
{
	return this->propertyID;
}

//Cylinder coordinate system
unsigned int Cylinder::GetCS() const
{
	return this->CS;
}

//X-axis projection 
double Cylinder::GetProjX() const
{
	return this->ProjX;
}
double Cylinder::GetProjX()
{
	return this->ProjX;
}

//Y-axis projection 
double Cylinder::GetProjY() const
{
	return this->ProjY;
}
double Cylinder::GetProjY()
{
	return this->ProjY;
}

//Z-axis projection 
double Cylinder::GetProjZ() const
{
	return this->ProjZ;
}
double Cylinder::GetProjZ()
{
	return this->ProjZ;
}

//A single element length at the X direction
double Cylinder::GetDX() const
{
	return this->DX;
}

//A single element length at the Y direction
double Cylinder::GetDY() const
{
	return this->DY;
}

//A single element length at the Z direction
double Cylinder::GetDZ() const
{
	return this->DZ;
}

//Checks if there is a concentrated mass at the first node
bool Cylinder::BoolFirstNodeMass() const
{
	return this->begin.mass != 0.0;
}

//Checks if there is a concentrated mass at the last node
bool Cylinder::BoolLastNodeMass() const
{
	return this->end.mass != 0.0;
}

//First node concentrated mass
double Cylinder::GetFirstNodeMass() const
{
	return ( double )this->begin.mass;
}

//Last node concentrated mass
double Cylinder::GetLastNodeMass() const
{
	return ( double )this->end.mass;
}

//Gets first node coordinates
const CylinderNodeData& Cylinder::GetFirstNodeCoordinates() const
{
	return this->begin;
}

char Cylinder::GetCylinderType() const
{
	return this->type;
}
