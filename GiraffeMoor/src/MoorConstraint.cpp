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
			if (!LoopReading::TryNestedKeyword_UnorderedMultiple(vessels, std::unordered_set<std::string_view>({ "VesselID" }), keywords, f, pos, str))
				return false;
			existVesselConstraint = true;
		}
		else if (!strcmp(str, "AnchorConstraints"))
		{
			if (!LoopReading::TryNestedKeyword_UnorderedMultiple(anchors, std::unordered_set<std::string_view>({ "LineID" }), keywords, f, pos, str))
				return false;
			existAnchorConstraint = true;
		}
		else if (!strcmp(str, "LineConstraints"))
		{
			if (!LoopReading::TryNestedKeyword_UnorderedMultiple(lines, std::unordered_set<std::string_view>({ "LineID" }), keywords, f, pos, str))
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


//Check input data readed
void MoorConstraint::CheckModel(bool& modelOk, std::map<std::string_view, std::size_t>& n_keywords)
{
	if (existAnchorConstraint)
	{
		std::for_each(anchors.cbegin(), anchors.cend(), [&](const AnchorConstraint& c) {
			if (c.GetLineNumber() > n_keywords["Lines"]) { 
				std::stringstream ss; 
				ss << "\n   + \"" << c.GetLineNumber() << "\" is not a valid line ID to change its anchor constraint" ; 
				Log::AddWarning(ss); modelOk = false; }
		});
	}
	if (existVesselConstraint)
	{
		std::for_each(vessels.cbegin(), vessels.cend(), [&](const VesselConstraint& c) {
			if (c.GetNumberID() > n_keywords["Vessels"]) { 
				std::stringstream ss; 
				ss << "\n   + \"" << c.GetNumberID() << "\" is not a valid vessel ID to change its constraints" ; 
				Log::AddWarning(ss); modelOk = false; }
		});
	}
	if (existLineConstraint)
	{
		std::for_each(lines.cbegin(), lines.cend(), [&](const LineConstraint& c) {
			if (c.GetNumberID() > n_keywords["Lines"]) { 
				std::stringstream ss; 
				ss << "\n   + \"" << c.GetNumberID() << "\" is not a valid line ID to change its constraints" ; 
				Log::AddWarning(ss); modelOk = false; }
		});
	}
}


bool MoorConstraint::ExistAnchorConstraint()
{ return this->existAnchorConstraint; }
bool MoorConstraint::ExistLineConstraint()
{ return this->existLineConstraint; }
bool MoorConstraint::ExistVesselConstraint()
{ return this->existVesselConstraint; }
