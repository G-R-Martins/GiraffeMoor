#include "PCH.h"
#include "Log.h"
#include "CADData.h"


bool CADData::Read(FILE* f)
{
	//Reading auxiliary variables
	char str[200], c, temp_name[200];


	if (fscanf(f, "%zd %s", &number, str) && !strcmp(str, "Name"))
	{
		if (fscanf(f, "%[^\"]*", str) == EOF || fscanf(f, "%c%[^\"]s", &c, temp_name) == EOF || c != '\"'
			|| fscanf(f, "%s", str) == EOF) //read the last quote
		{

			std::stringstream ss{ "\n   + Error reading CAD name of the platform number " }; ss << number;
			Log::AddWarning(ss);
			return false;
		}
		else
			name = temp_name;

	}
	else
	{
		Log::AddWarning("\n   + Error reading CAD data");
		return false;
	}


	//All ok while reading
	return true;
}

void CADData::WriteGiraffeModelFile(FILE* f)
{
	fprintf(f, "\tSTLSurface %zd %s\n", number, name.c_str());
}



size_t CADData::GetNumber() const
{
	return this->number;
}
const std::string& CADData::GetName() const
{
	return this->name;
}
