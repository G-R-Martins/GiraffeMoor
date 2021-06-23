#pragma once

class SegmentProperty
{
public:
	SegmentProperty();
	~SegmentProperty() = default;

	//Reads input file
	bool Read(FILE *f);

	//Get functions
	const unsigned int GetNumber() const;

	//Writes Giraffe file data
	void WriteGiraffeModelFile(FILE *f);

	/*-------
	Variables
	--------*/

	unsigned int number;
	char type; //'b' - beam or 't' - truss
	double diameter;
	double diameter_inner;
	double rho;
	double EA;
	double EI;
	double GJ;
	double GA;
	double CDt;
	double CDn;
	double CAt;
	double CAn;
	double E;
	double nu;
	double SG;


	/*-------------------
	 Overloaded operators
	 -------------------*/

	friend bool operator< (const SegmentProperty& obj1, const SegmentProperty& obj2);
	friend bool operator> (const SegmentProperty& obj1, const SegmentProperty& obj2);
	friend bool operator== (const SegmentProperty& obj1, const SegmentProperty& obj2);
	friend bool operator!= (const SegmentProperty& obj1, const SegmentProperty& obj2);
};