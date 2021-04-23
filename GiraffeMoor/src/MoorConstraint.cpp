#include "PCH.h"
#include "MoorConstraint.h"
#include "MooringModel.h"
#include "TemplateReading.h"


extern MooringModel mm;


MoorConstraint::MoorConstraint()
{}

MoorConstraint::~MoorConstraint()
{}

//Reads inout file
bool MoorConstraint::Read(FILE * f)
{
	//Saves keywords and values readed
	char str[500];

	//Saves current position
	fpos_t pos;

	//Keywords
	std::unordered_set<std::string_view> keywords({ "AnchorConstraints", "VesselConstraints" });

	//Loop to read solution parameters
	while (!fgetpos(f, &pos) && fscanf(f, "%s", str) != EOF)
	{
		if (!strcmp(str, "VesselConstraints"))
		{
			if (!LoopReading::TryNestedKeyword_UnorderedMultiple(mm.vessel_constraint, std::unordered_set<std::string_view>({ "VesselID" }), keywords, f, pos, str))
				return false;
		}
		else if (!strcmp(str, "AnchorConstraints"))
		{
			if (!LoopReading::TryNestedKeyword_UnorderedMultiple(mm.anc_constraint, std::unordered_set<std::string_view>({ "LineID" }), keywords, f, pos, str))
				return false;
		}
		else if (str[0] == '/' && AuxFunctions::ReadComment(f, str))
			continue;
		//Other word -> end loop and backs to IO class
		else
		{
			fsetpos(f, &pos);
			break;
		}
	}


	//All ok while reading
	return true;
}
