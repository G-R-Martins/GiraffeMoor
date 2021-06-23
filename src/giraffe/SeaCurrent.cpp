#include "PCH.h"
#include "SeaCurrent.h"


SeaCurrent::SeaCurrent()
	: depth(0.0), speed(0.0), azimuth(0.0)
{}


SeaCurrent::~SeaCurrent()
{}

//Reads input file
bool SeaCurrent::Read(FILE *f)
{
	char str[500];			//salva palavras-chave lidas e valores lidos
	bool readOk = true;

	//Try to read a whole row
	if (fscanf(f, "%s %lf", str, &depth) == EOF || strcmp(str, "Depth"))			readOk = false;
	else if (fscanf(f, "%s %lf", str, &speed) == EOF || !readOk || strcmp(str, "Speed"))	readOk = false;
	else if (fscanf(f, "%s %lf", str, &azimuth) == EOF || !readOk || strcmp(str, "Angle"))	readOk = false;
	
	if (!readOk)
		return false;
	
	//All OK while reading
	return true;
}
