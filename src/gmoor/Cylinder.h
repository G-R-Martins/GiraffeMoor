#pragma once

//Structure with first/last nodes data	
struct CylinderNodeData
{
	//Coordinates
	double X = 0.0, Y = 0.0, Z = 0.0;

	//Concentrated mass
	float mass = 0.0;

	//Node number
	unsigned int node = 0;
};

class Cylinder
{
	//First node data
	CylinderNodeData begin;

	//Last node data
	CylinderNodeData end;

	//Cylinder ID
	unsigned int ID;
	
	//Cylinder name
	std::string name;
	
	//Cylinder segment property
	unsigned int propertyID;
	
	//Number of elements by cylinder
	unsigned int discretization;
	
	//Cylinder coordinate system ID
	unsigned int CS;
	
	//Total length
	double length;

	//Projections
	double ProjX;
	double ProjY;
	double ProjZ;

	//Element(s) length
	double DX;
	double DY;
	double DZ;

	//Cylinder element type
		// 'b' -> beam
		// 't' -> truss
	char type;

	//==========================================================================================================================
public:

	Cylinder();
	~Cylinder();

					/*--------
					|Functions|
					---------*/

	//Reads input file
	bool Read(FILE* f);

	///
	/// Set functions
	///

	//Set coordinate system
	void SetCoordinateSystem(unsigned int CS);

	//Set data
	void SetGeneralCylinderData();

	//Cylinder total length
	void SetLength();

	//Cylinder first node
	void SetFirstNode(unsigned int& node);
	//Cylinder last node
	void SetLastNode(unsigned int& node);

	//X-axis projection 
	void SetProjX();
	//Y-axis projection 
	void SetProjY();
	//Z-axis projection 
	void SetProjZ();

	//A single element length at the X direction
	void SetDX();
	//A single element length at the Y direction
	void SetDY();
	//A single element length at the Z direction
	void SetDZ();

	//Current cylinder element type
	void SetCylinderType(char &temp);

	///
	/// Get functions
	///

	//Number of elements
	unsigned int GetDiscretization() const;

	//Cylinder first node
	unsigned int GetFirstNode() const;
	//Cylinder last node
	unsigned int GetLastNode() const;

	//Cylinder name
	const std::string& GetName() const;

	//Cylinder property ID
	unsigned int GetID() const;

	//Cylinder coordinate system
	unsigned int GetCS() const;

	//Cylinder total length
	double GetLength() const;
	//X-axis projection 
	double GetProjX() const;
	//Y-axis projection 
	double GetProjY() const;
	//Z-axis projection 
	double GetProjZ() const;

	//Cylinder total length
	double GetLength();
	//X-axis projection 
	double GetProjX();
	//Y-axis projection 
	double GetProjY();
	//Z-axis projection 
	double GetProjZ();

	//A single element length at the X direction
	double GetDX() const;
	//A single element length at the Y direction
	double GetDY() const;
	//A single element length at the Z direction
	double GetDZ() const;

	//First node concentrated mass
	double GetFirstNodeMass() const;
	//Last node concentrated mass
	double GetLastNodeMass() const;

	//Get current cylinder element type
	char GetCylinderType() const;

	//Checks if there is a concentrated mass at the first node
	bool BoolFirstNodeMass() const;
	//Checks if there is a concentrated mass at the last node
	bool BoolLastNodeMass() const;

	//Get first node coordinates
	const CylinderNodeData& GetFirstNodeCoordinates() const;

	//============================================================================

	/*-------------------
	 Overloaded operators
	--------------------*/

	friend bool operator< (const Cylinder& obj1, const Cylinder& obj2);
	friend bool operator> (const Cylinder& obj1, const Cylinder& obj2);
	friend bool operator== (const Cylinder& obj1, const Cylinder& obj2);
	friend bool operator!= (const Cylinder& obj1, const Cylinder& obj2);
};

