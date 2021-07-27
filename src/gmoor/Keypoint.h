#pragma once

class Keypoint
{
	//Keypoint ID
	unsigned int number;

	//Coordinates
	double x, y, z;

	//============================================================================

public:
	Keypoint();
	Keypoint(double coord_x, double coord_y, double coord_z, unsigned int ID=0);
	~Keypoint();

	//Reads input file
	bool Read(FILE *f);

	//Set functions
	

	//Get functions
	const unsigned int GetNumber() const;
	const double GetCoordinate(char coordinate) const;


	//============================================================================


	//Overloaded operators
	friend bool operator< (const Keypoint& obj1, const Keypoint& obj2);
	friend bool operator> (const Keypoint& obj1, const Keypoint& obj2);
	friend bool operator== (const Keypoint& obj1, const Keypoint& obj2);
	friend bool operator!= (const Keypoint& obj1, const Keypoint& obj2);

};

