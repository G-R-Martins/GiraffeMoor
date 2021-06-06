#pragma once

class Keypoint
{
public:
	Keypoint();
	~Keypoint();

	//Reads input file
	bool Read(FILE *f);

	//Get functions
	const unsigned int GetNumber() const;
	const double GetKeypoint(char coordinate) const;

	//============================================================================

	/*-------
	Variables
	--------*/

	//Keypoint ID
	unsigned int number;

	//Coordinates

	double x;
	double y;
	double z;

	friend bool operator< (const Keypoint& obj1, const Keypoint& obj2);
	friend bool operator> (const Keypoint& obj1, const Keypoint& obj2);
	friend bool operator== (const Keypoint& obj1, const Keypoint& obj2);
	friend bool operator!= (const Keypoint& obj1, const Keypoint& obj2);

};

