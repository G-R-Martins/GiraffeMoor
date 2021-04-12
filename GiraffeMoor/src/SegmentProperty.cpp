#include "PCH.h"
#include "SegmentProperty.h"
#include "Log.h"


SegmentProperty::SegmentProperty()
	: number(0), type('n'), diameter(0.0), diameter_inner(0.0), rho(0.0), 
	EA(0.0), EI(0.0), GJ(0.0), GA(0.0), 
	CDt(0.0), CDn(0.0), CAt(0.0), CAn(0.0), 
	E(0.0), nu(0.0), SG(1.0)
{}


//Overloaded operators
bool operator<(const SegmentProperty& obj1, const SegmentProperty& obj2)
{
	return obj1.number < obj2.number;
}

bool operator>(const SegmentProperty& obj1, const SegmentProperty& obj2)
{
	return !(obj1 < obj2);
}

bool operator==(const SegmentProperty& obj1, const SegmentProperty& obj2)
{
	return obj1.number == obj2.number;
}

bool operator!=(const SegmentProperty& obj1, const SegmentProperty& obj2)
{
	return !(obj1 == obj2);
}


//Reads input file
bool SegmentProperty::Read(FILE *f)
{
	//salva palavras-chave lidas e valores lidos
	char str[500];

	//Reading position
	fpos_t pos;

	//Reading boolean
	bool readOk = true;

	/*Tries to read a number indicated by the user this number is just for organization, 
	the real parameter 'number' will be setted with the static variable 'n_prop'*/
	fgetpos(f, &pos);
	//If a word is readed, back position to read segment type
	if (fscanf(f, "%d", &number) == EOF)//&& isalpha(str[0]))
	{
		Log::AddWarning("\n   +Error reading segment property ID.\n");
		return false;
	}
		//fsetpos(f, &pos);
	
	////Segment property ID
	//number = ++n_prop;

	if (fscanf(f, "%s", str) != EOF && (!strcmp(str, "truss") || !strcmp(str, "chain")))
	{
		type = 't';
	}
	else if (!strcmp(str, "beam") || !strcmp(str, "polymeric"))
	{
		type = 'b';
	}
	else
	{
		Log::AddWarning("\n   +Error reading segment property type.\n");
		return false;
	}

	//Truss
	if (type == 't')
	{
		//Tries to read specific gravity
		fgetpos(f, &pos);
		if (fscanf(f, "%s %lf", str, &SG) && readOk && strcmp(str, "SpecificGravity"))
			fsetpos(f, &pos);
		if (fscanf(f, "%s %lf", str, &rho) && readOk && strcmp(str, "SpecificMass"))
			readOk = false;
		if (fscanf(f, "%s %lf", str, &diameter) && readOk && strcmp(str, "Diameter"))
			readOk = false;
		if (fscanf(f, "%s %lf", str, &EA) && readOk && strcmp(str, "EA"))
			readOk = false;
		if (fscanf(f, "%s %lf", str, &CDt) && readOk && strcmp(str, "CDt"))
			readOk = false;
		if (fscanf(f, "%s %lf", str, &CDn) && readOk && strcmp(str, "CDn"))
			readOk = false;
		if (fscanf(f, "%s %lf", str, &CAt) && readOk && strcmp(str, "CAt"))
			readOk = false;
		if (fscanf(f, "%s %lf", str, &CAn) && readOk && strcmp(str, "CAn"))
			readOk = false;
	}
	//Beam
	else if (type == 'b')
	{

		//Tries read specific gravity
		fgetpos(f, &pos);
		if (fscanf(f, "%s %lf", str, &SG) && readOk && strcmp(str, "SpecificGravity"))
			fsetpos(f, &pos);
		if (fscanf(f, "%s %lf", str, &rho) && readOk && strcmp(str, "SpecificMass"))
			readOk = false;
		if (fscanf(f, "%s %lf", str, &diameter) && readOk && strcmp(str, "Diameter"))
			readOk = false;
		
		//EA, EI, GJ, GA
		if (fscanf(f, "%s", str) && readOk && !strcmp(str, "EA"))
		{
			if (fscanf(f, "%lf %s %lf", &EA, str, &EI) && readOk && strcmp(str, "EI"))
				readOk = false;
			if (fscanf(f, "%s %lf", str, &GJ) && readOk && strcmp(str, "GJ"))
				readOk = false;
			if (fscanf(f, "%s %lf", str, &GA) && readOk && strcmp(str, "GA"))
				readOk = false;
			if (fscanf(f, "%s %lf", str, &CDt) && readOk && strcmp(str, "CDt"))
				readOk = false;
			if (fscanf(f, "%s %lf", str, &CDn) && readOk && strcmp(str, "CDn"))
				readOk = false;
			if (fscanf(f, "%s %lf", str, &CAt) && readOk && strcmp(str, "CAt"))
				readOk = false;
			if (fscanf(f, "%s %lf", str, &CAn) && readOk && strcmp(str, "CAn"))
				readOk = false;
		}
		//Young modulus and Poisson ration
		else if(readOk && (!strcmp(str, "YoungModulus")|| !strcmp(str, "E")))
		{
			if (fscanf(f, "%lf %s %lf", &E, str, &nu) && readOk && (strcmp(str, "PoissonRatio")|| strcmp(str, "nu")))
				readOk = false;
			if (fscanf(f, "%s %lf", str, &CDt) && readOk && strcmp(str, "CDt"))
				readOk = false;
			if (fscanf(f, "%s %lf", str, &CDn) && readOk && strcmp(str, "CDn"))
				readOk = false;
			if (fscanf(f, "%s %lf", str, &CAt) && readOk && strcmp(str, "CAt"))
				readOk = false;
			if (fscanf(f, "%s %lf", str, &CAn) && readOk && strcmp(str, "CAn"))
				readOk = false;
		}
		//ERROR
		else 
		{
			Log::AddWarning("\n   +Error reading segment property data.\n");
			return false;
		}
	}
	//ERROR
	else
	{
		Log::AddWarning("\n   +Error defining segment property data.\n");
		return false;
	}

	//All OK while reading
	return true;
}

//Writes Giraffe file data
void SegmentProperty::WriteGiraffeModelFile(FILE *f)
{
	fprintf(f, "\tSec\t%d\tEA\t%.6e\tEI\t%.6e\tGJ\t%.6e\tGA\t%.6e\tRho\t%.6e\tCDt\t%.6e\tCDn\t%.6e\tCAt\t%.6e\tCAn\t%.6e\tDe\t%.6e\tDi\t%.6e\n", 
		number, EA, EI, GJ, GA, rho, CDt, CDn, CAt, CAn, diameter, 0.0);
}