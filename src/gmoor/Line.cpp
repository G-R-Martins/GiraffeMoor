#include "PCH.h"
#include "Line.h"
#include "LoopReading.h"
#include "Log.h"


Line::Line()
	: number(0), keypoint_A(0), keypoint_B(0), cs(0), vessel(0), node_A(0), node_B(0), 
	tot_nodes(0), nodeset_A(0), nodeset_B(0), total_length(0.0), configuration("\0"),
	hasAnchor(true), isShared(false), segment_set(0), usingSegmentSet(false),
	tdz(nullptr), percent(0.0), anc_tdp(0.0), tdp_fair(0.0)
{
	segments.reserve(4);
	gamma_s.reserve(4);
}

Line::~Line()
{
	//if (tdz) delete tdz;
}

Line::Line(Line&& other) noexcept
	: number(std::move(other.number)), keypoint_A(std::move(other.keypoint_A)), keypoint_B(std::move(other.keypoint_B)),
	cs(std::move(other.cs)), vessel(std::move(other.vessel)), node_A(std::move(other.node_A)), node_B(std::move(other.node_B)),
	tot_nodes(std::move(other.tot_nodes)), nodeset_A(std::move(other.nodeset_A)), nodeset_B(std::move(other.nodeset_B)),
	total_length(std::move(other.total_length)), hasAnchor(std::move(other.hasAnchor)), isShared(std::move(other.isShared)),
	segment_set(std::move(other.segment_set)), usingSegmentSet(std::move(other.usingSegmentSet)), segments(std::move(other.segments)), 
	gamma_s(std::move(other.gamma_s)), transition_nodes(std::move(other.transition_nodes)), configuration("\0"), vesselIDs(std::move(other.vesselIDs)),
	//laying_direction(std::move(other.laying_direction)), tdz(std::move(other.tdz)),
	percent(std::move(other.percent)), anc_tdp(std::move(other.anc_tdp)), tdp_fair(std::move(other.tdp_fair))
{
	other.tdz = nullptr;
}

Line& Line::operator=(Line&& other) noexcept
{
	//if (tdz) delete tdz;
	number = std::move(other.number);
	keypoint_A = std::move(other.keypoint_A);
	keypoint_B = std::move(other.keypoint_B);
	cs = std::move(other.cs);
	vessel = std::move(other.vessel);
	node_A = std::move(other.node_A);
	node_B = std::move(other.node_B);
	tot_nodes = std::move(other.tot_nodes);
	nodeset_A = std::move(other.nodeset_A);
	nodeset_B = std::move(other.nodeset_B);
	total_length = std::move(other.total_length);
	hasAnchor = std::move(other.hasAnchor);
	isShared = std::move(other.isShared);
	segment_set = std::move(other.segment_set);
	usingSegmentSet = std::move(other.usingSegmentSet);

	segments = std::move(other.segments);
	gamma_s = std::move(other.gamma_s);
	transition_nodes = std::move(other.transition_nodes);
	configuration[0] = '\0';
	vesselIDs = std::move(other.vesselIDs);
	//tdz = std::move(other.tdz);
	percent = std::move(other.percent);
	anc_tdp = std::move(other.anc_tdp);
	tdp_fair = std::move(other.tdp_fair);


	//TDZ pointer
	other.tdz = nullptr;

	return *this;
}


/* Overloaded operators */
bool operator< (const Line& line1, const Line& line2)
{
	//Both lines with vessels identified and different between them
	// -> uses the line numbers to compare
	if (line1.vessel != 0 && line2.vessel != 0 && line1.vessel == line2.vessel)
	{
		return line1.number < line2.number;
	}
	//Otherwise -> uses the vessel number to compare
	else
		return line1.vessel < line2.vessel;
}
bool operator> (const Line& line1, const Line& line2)
{
	return !(line1 < line2);
}

bool operator== (const Line& line1, const Line& line2)
{
		/*			same ID number		  ||		same extremeties keypoints*/
	return ( line1.number == line2.number || ( line1.keypoint_A == line2.keypoint_A && line1.keypoint_B == line2.keypoint_B ) );
}
bool operator!= (const Line& line1, const Line& line2)
{
	return !( line1 == line2 );
}

//Comparing line with an ID number
bool operator== (const Line& line1, const unsigned int& line2)
{
	return line1.vessel == line2;
}
bool operator!= (const Line& line1, const unsigned int& line2)
{
	return !( line1 == line2 );
}


//Reads input file
bool Line::Read(FILE *f)
{

	char str[500];			//salva palavras-chave lidas e valores lidos
	fpos_t pos;				//variável que salva ponto do stream de leitura
	bool readOk = true;

	//Line number
	if (fscanf(f, "%s", str) && isdigit(str[0]))
		number = atoi(str);
	else
	{
		Log::AddWarning("\n   + Error reading the ID number of a line");
		return false;
	}

	//Boundary nodes
	if (readOk && fscanf(f, "%s", str) != EOF && !strcmp(str, "Anchor"))
	{
		if (fscanf(f, "%d %s %d", &keypoint_A, str, &keypoint_B) == EOF || strcmp(str, "Fairlead"))
			readOk = false;
	}
	//If "Fairlead" was read first, it is a line without an anchor
	else if (readOk && !strcmp(str, "Fairlead"))
	{
		hasAnchor = false;

		if (fscanf(f, "%d %s %d", &keypoint_A, str, &keypoint_B) == EOF || strcmp(str, "Fairlead"))
			readOk = false;
	}
	else
		readOk = false;

	//Checks vessel number and previously error
	if (readOk && !fgetpos(f, &pos) && fscanf(f, "%s", str) == EOF)
		readOk = false;
	//No specific vessel defined
	else if (strcmp(str, "VesselID"))
	{
		if (hasAnchor)
		{
			std::string warning = "\n   + The line number " + std::to_string(number) + " supposed to be addressed to a vessel.";
			Log::AddWarning(warning);
			return false;
		}
		fsetpos(f, &pos);
	}
	//With a vessel
	else if (!strcmp(str, "VesselID") && fscanf(f, "%s", str) != EOF && isdigit(str[0]))
	{
		//Check first vessel number
		if (hasAnchor)
			vessel = atoi(str);
		else
		{
			isShared = true;
			vesselIDs.emplace_back(atoi(str));
			//Reading loop
			while (!fgetpos(f, &pos) && fscanf(f, "%s", str) != EOF)
			{
				//If is a number (vessel ID)
				if (isdigit(str[0]))
					vesselIDs.emplace_back(atoi(str));
				//Separator between vessels
				else if (!strcmp(str, ";"))
					continue;
				//Otherwise
				else
				{
					fsetpos(f, &pos);
					break;
				}
			}
		}
	}
	//Other word -> ERROR
	else
		readOk = false;


	if (!readOk)
	{
		std::string warning = "\n   + Error reading parameters of line " + std::to_string(number);
		Log::AddWarning(warning);
		return false;
	}
	
		
	//Check if there is a touchdown zone
	if (!fgetpos(f, &pos) && fscanf(f, "%s", str) && !strcmp(str, "TouchdownZone"))
	{
		if (fscanf(f, "%lf %lf %lf", &percent, &anc_tdp, &tdp_fair) == EOF || percent == 0.0 || anc_tdp == 0.0 || tdp_fair == 0.0 ||
			( !fgetpos(f, &pos) && fscanf(f, "%s", str) == EOF )) //Segment after TDZ
		{
			std::string warning = "\n   + Error reading touchdown zone of line number " + std::to_string(number);
			Log::AddWarning(warning);
			return false;
		}
	}

	//Read segment(s)
	if (!strcmp(str, "SegmentSet"))
	{
		fscanf(f, "%zd", &segment_set);
		usingSegmentSet = true;
	}
	else
	{
		//Backs position because it can be a comment, then, try to read 'Length'
		fsetpos(f, &pos);
		if (!LoopReading::TryNestedKeyword_UnorderedMultiple(segments,
															 std::unordered_set<std::string_view>({ "Length" }),
															 std::unordered_set<std::string_view>({ "Line", "MooringLine", "Cable" }),
															 f, pos, str))
		{
			std::string warning = "\n   + Error reading a segment of the line number " + std::to_string(number);
			Log::AddWarning(warning);
			return false;
		}
	}


	//All OK while reading
	return true;
}

const unsigned int Line::GetNumber() const
{
	return this->number;
}
