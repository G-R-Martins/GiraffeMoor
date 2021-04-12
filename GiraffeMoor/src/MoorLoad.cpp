#include "PCH.h"
#include "MoorLoad.h"
#include "Log.h"


MoorLoad::MoorLoad()
	: nodeID(0), segmentID(1), lineID(0), step(-1),
	table(nullptr), mathCode(nullptr)
{}

MoorLoad::~MoorLoad()
{}

//Reads GiraffeMoor file
bool MoorLoad::Read(FILE* f)
{
	//Saves readed keywords and values
	char str[50];

	//Warning message
	std::string warning = " - \"NodalForce\" block:\n";

	//Stream with current position
	fpos_t pos;

	//Checks if ID is a letter 
	if (fscanf(f, "%s", str) != EOF && isalpha(str[0]))
		description = str;
	else
		nodeID = atoi(str);

	
	if (description == "vessel")
		auto to_ignore = fscanf(f, "%d", &nodeID);
	else //if (nodeID != 0 || description != "vessel")
	{
		//If is an anchor or fairlead node, there is no need to define the segment
		if (!fgetpos(f, &pos) && fscanf(f, "%s", str) && !strcmp(str, "SegmentID"))
			auto ret = fscanf(f, "%d", &segmentID);
		else //Returns position to read only the line
			fsetpos(f, &pos);

		if (fscanf(f, "%s %zd", str, &lineID) && strcmp(str, "LineID"))
		{
			warning += "\n   +Error reading segment or line data";
			Log::AddWarning(warning);
			return false;
		}

	}

	//Read step
	if (fscanf(f, "%s %d", str, &step) == EOF || strcmp(str, "Step"))
	{
		warning += "\n   +Error reading step";
		Log::AddWarning(warning);
		return false;
	}

	//Read data
	bool flag_continue = true;
	if (fscanf(f, "%s", str) && !strcmp(str, "MathCode"))
	{
		mathCode = new MathCode();
		if (!mathCode->Read(f))
			flag_continue = false;
	}
	else if (flag_continue && !strcmp(str, "TimeSeries"))
	{
		table = new Table();
		if (!table->Read(f))
			flag_continue = false;
	}
	else
	{
		warning += "\n   +Error reading force data of type \"" + std::string(str) + "\"";
		Log::AddWarning(warning);
		return false;
	}


	return true;
}
