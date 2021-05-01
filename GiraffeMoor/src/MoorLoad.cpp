#include "PCH.h"
#include "MoorLoad.h"
#include "Log.h"
#include "AuxFunctions.h"


//Global variable
extern std::string folder_name;

MoorLoad::MoorLoad()
	: nodeID(0), segmentID(1), lineID(0), step(-1),
	table(nullptr), mathCode(nullptr),
	fromFile(false), file_name("\0"), header_lines(0), n_times(0)
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
	else if (isdigit(str[0]))
		nodeID = atoi(str);

	
	if (description == "vessel")
		int to_ignore = fscanf(f, "%d", &nodeID);
	else //if (nodeID != 0 || description != "vessel")
	{
		//If is an anchor or fairlead node, there is no need to define the segment
		if (!fgetpos(f, &pos) && fscanf(f, "%s", str) && !strcmp(str, "SegmentID"))
			int ret_2_ignore = fscanf(f, "%d", &segmentID);
		else //Back position to read only the line
			fsetpos(f, &pos);

		if (fscanf(f, "%s %zd", str, &lineID) && strcmp(str, "LineID"))
		{
			warning += "\n   + Error reading segment or line data";
			Log::AddWarning(warning);
			return false;
		}

	}

	//Read step
	if (fscanf(f, "%s %d", str, &step) == EOF || strcmp(str, "Step"))
	{
		warning += "\n   + Error reading step";
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
	//Read from external file (GiraffeMoor check if the file exists and only Giraffe will actually read it)
	else if (!strcmp(str, "File"))
	{
		AuxFunctions::TryComment(f);

		//Read the name of the file with the table data 
		///file name must be enclosed by quotes
		char c;
		if (fscanf(f, "%[^\"]*", str) == EOF ||       /*read until double quotes (whitespaces)*/
			fscanf(f, "%c%[^\"]s", &c, str) == EOF || /*read file name, until the last double quotes*/
			c != '\"' || fscanf(f, "%c", &c) == EOF || c != '\"')  /*check first double quotes and read last one*/
			return false;
		else
			file_name = str;

		//Checks format (must be .csv or .txt)
		size_t dot_pos = file_name.find('.');				// position of the dot, before file format
		std::string_view format(file_name.c_str() + dot_pos + 1, 3);	// get a substring with the letters after the dot

		//Invalid format
		if (format != "csv" && format != "txt")
		{
			warning = "\n   + Invalid format for the file with nodal load of the " + description;
			warning = ( description == "vessel" ) ? std::to_string(nodeID) : /* if is a vessel */
				"node of the line " + std::to_string(lineID); /* if is first or last node of the line */
			Log::AddWarning(warning);
			return false;
		}

		//Tries to open the file before continue
		std::string full_file_name = folder_name + "time series/" + std::string(file_name);
		std::ifstream inp(full_file_name);

		if (!inp.is_open())
		{
			warning = "\n   + Error trying to open the file with nodal load of the " + description;
			warning = ( description == "vessel" ) ? std::to_string(nodeID) : /* if is a vessel */
				"node of the line " + std::to_string(lineID); /* if is first or last node of the line */
			Log::AddWarning(warning);
			return false;
		}

		//Check for error during the reading of the number of header and data lines
		if (fscanf(f, "%s %d", str, &header_lines) == EOF || strcmp(str, "HeaderLines") //set number of header lines
			|| fscanf(f, "%s %d", str, &n_times) == EOF || strcmp(str, "NTimes")) //set number of lines with data
			return false;

		fromFile = true;
	}
	else if (flag_continue && !strcmp(str, "TimeSeries"))
	{
		table = new Table();
		if (!table->Read(f))
			flag_continue = false;
	}
	else
	{
		warning += "\n   + Error reading force data of type. \"" + std::string(str) + "\" is not a valid type";
		Log::AddWarning(warning);
		return false;
	}


	return true;
}
