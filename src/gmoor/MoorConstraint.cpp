#include "PCH.h"
#include "MoorConstraint.h"
//Auxiliary function to read input file
#include "LoopReading.h"


MoorConstraint::MoorConstraint()
	: existAnchorConstraint(false), existVesselConstraint(false), existLineConstraint(false)
{
	anchors.reserve(32);
	vessels.reserve(16);
	lines.reserve(32);
}


//Read input file
bool MoorConstraint::Read(FILE * f)
{
	//Saves keywords and values readed
	char str[500];

	//Saves current position
	fpos_t pos;

	//Keywords
	std::unordered_set<std::string_view> keywords({"AnchorConstraints", "VesselConstraints" , "LineConstraints" });

	//Loop to read solution parameters
	while (!fgetpos(f, &pos) && fscanf(f, "%s", str) != EOF)
	{
		if (!strcmp(str, "VesselConstraints"))
		{
			if (!AuxFunctions::Reading::TryNestedKeyword_UnorderedMultiple(vessels, std::unordered_set<std::string_view>({ "VesselID" }), keywords, f, pos, str))
				return false;
			existVesselConstraint = true;
		}
		else if (!strcmp(str, "AnchorConstraints"))
		{
			if (!AuxFunctions::Reading::TryNestedKeyword_UnorderedMultiple(anchors, std::unordered_set<std::string_view>({ "LineID" }), keywords, f, pos, str))
				return false;
			existAnchorConstraint = true;
		}
		else if (!strcmp(str, "LineConstraints"))
		{
			if (!AuxFunctions::Reading::TryNestedKeyword_UnorderedMultiple(lines, std::unordered_set<std::string_view>({ "LineID" }), keywords, f, pos, str))
				return false;
			existLineConstraint = true;
		}
		else if (str[0] == '/' && AuxFunctions::Read::Comment(f, str))
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


/// 
/// Get functions
/// 

const std::vector<AnchorConstraint>& MoorConstraint::GetAnchorConstraints() const
{ return this->anchors; }
std::vector<AnchorConstraint>& MoorConstraint::GetAnchorConstraints()
{ return this->anchors; }
const std::vector<VesselConstraint>& MoorConstraint::GetVesselConstraints() const
{ return this->vessels; }
std::vector<VesselConstraint>& MoorConstraint::GetVesselConstraints()
{ return this->vessels; }
const std::vector<LineConstraint>& MoorConstraint::GetLineConstraints() const
{ return this->lines; }
std::vector<LineConstraint>& MoorConstraint::GetLineConstraints()
{ return this->lines; }



bool MoorConstraint::ExistAnchorConstraint()
{ return this->existAnchorConstraint; }
bool MoorConstraint::ExistLineConstraint()
{ return this->existLineConstraint; }
bool MoorConstraint::ExistVesselConstraint()
{ return this->existVesselConstraint; }