#include "PCH.h"
#include "Keypoint.h"
#include "Log.h"


Keypoint::Keypoint()
	: number(0), x(0.0), y(0.0), z(0.0)
{}


Keypoint::~Keypoint()
{}

//Reads input file
bool Keypoint::Read(FILE *f)
{
	char str[200];			//salva palavras-chave lidas e valores lidos
	bool readOk = true;

	if (fscanf(f, "%s", str) && isdigit(str[0]))
		number = atoi(str);
	else
	{
		Log::AddWarning("\n   + Error reading a keypoit number\n");
		return false;
	}


	if (fscanf(f, "%s %lf", str, &x) && readOk && strcmp(str, "X"))			readOk = false;
	else if (fscanf(f, "%s %lf", str, &y) && readOk && strcmp(str, "Y"))	readOk = false;
	else if (fscanf(f, "%s %lf", str, &z) && readOk && strcmp(str, "Z"))	readOk = false;

	if (!readOk)
	{
		std::string w = "\n   + Error reading data of the keypoit number " + std::to_string(number);
		Log::AddWarning(w);
		return false;
	}
	
	//All OK while reading
	return true;
}


//Overloaded operators
bool operator<(const Keypoint& obj1, const Keypoint& obj2)
{
	return obj1.number < obj2.number;
}
bool operator>(const Keypoint& obj1, const Keypoint& obj2)
{
	return !(obj1 < obj2);
}

bool operator==(const Keypoint& obj1, const Keypoint& obj2)
{
	return obj1.number == obj2.number;
}
bool operator!=(const Keypoint& obj1, const Keypoint& obj2)
{
	return !(obj1 == obj2);
}
