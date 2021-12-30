#include "PCH.h"
#include "MoorLoad.h"


MoorLoad::MoorLoad()
	: m_node_id(0), m_segment_id(1), m_line_id(0), m_step(0),
	m_table(nullptr), m_mathCode(nullptr),
	m_is_from_file(false), m_file_name("\0"), m_header_lines(0), m_n_times(0)
{}

MoorLoad::~MoorLoad()
{}

//Reads GiraffeMoor file
bool MoorLoad::Read(FILE* f)
{
	////Saves readed keywords and values
	//char str[50];

	////Warning message
	//std::string warning = " - \"NodalForce\" block:\n";

	////Stream with current position
	//fpos_t pos;

	////Checks if ID is a letter 
	//if (fscanf(f, "%s", str) != EOF && isalpha(str[0]))
	//	description = str;
	//else if (isdigit(str[0]))
	//	nodeID = atoi(str);

	//
	//if (description == "vessel")
	//	int to_ignore = fscanf(f, "%d", &nodeID);
	//else 
	//{
	//	//If is an anchor or fairlead node, there is no need to define the segment
	//	if (!fgetpos(f, &pos) && fscanf(f, "%s", str) && !strcmp(str, "SegmentID"))
	//		int ret_2_ignore = fscanf(f, "%d", &segmentID);
	//	else //Back position to read only the line
	//		fsetpos(f, &pos);

	//	if (fscanf(f, "%s %zd", str, &lineID) && strcmp(str, "LineID"))
	//	{
	//		warning += "\n   + Error reading segment or line data";
	//		Log::AddWarning(warning);
	//		return false;
	//	}

	//}

	////Read step
	//if (fscanf(f, "%s %d", str, &step) == EOF || strcmp(str, "Step"))
	//{
	//	warning += "\n   + Error reading step";
	//	Log::AddWarning(warning);
	//	return false;
	//}

	////Read data
	//bool flag_continue = true;
	//if (fscanf(f, "%s", str) && !strcmp(str, "MathCode"))
	//{
	//	mathCode = new MathCode();
	//	if (!mathCode->Read(f))
	//		flag_continue = false;
	//}
	////Read from external file (GiraffeMoor check if the file exists and only Giraffe will actually read it)
	//else if (!strcmp(str, "File"))
	//{
	//	AuxFunctions::Read::TryComment(f);

	//	//Read the name of the file with the table data 
	//	///file name must be enclosed by quotes
	//	char c;
	//	if (fscanf(f, "%[^\"]*", str) == EOF ||       /*read until double quotes (whitespaces)*/
	//		fscanf(f, "%c%[^\"]s", &c, str) == EOF || /*read file name, until the last double quotes*/
	//		c != '\"' || fscanf(f, "%c", &c) == EOF || c != '\"')  /*check first double quotes and read last one*/
	//		return false;
	//	else
	//		file_name = str;

	//	//Checks format (must be .csv or .txt)
	//	unsigned int dot_pos = file_name.find('.');				// position of the dot, before file format
	//	std::string_view format(file_name.c_str() + dot_pos + 1, 3);	// get a substring with the letters after the dot

	//	//Invalid format
	//	if (format != "csv" && format != "txt")
	//	{
	//		warning = "\n   + Invalid format for the file with nodal load of the " + description;
	//		warning = ( description == "vessel" ) ? std::to_string(nodeID) : /* if is a vessel */
	//			"node of the line " + std::to_string(lineID); /* if is first or last node of the line */
	//		Log::AddWarning(warning);
	//		return false;
	//	}

	//	//Tries to open the file before continue
	//	std::string full_file_name = IO::folder_name + "time series/" + std::string(file_name);
	//	std::ifstream inp(full_file_name);

	//	if (!inp.is_open())
	//	{
	//		warning = std::string("\n   + Error trying to open the file with nodal load of the ") + description + " ";
	//		warning += ( description == "vessel" ) ? std::to_string(nodeID) : /* if is a vessel */
	//			"node of the line " + std::to_string(lineID); /* if is first or last node of the line */
	//		Log::AddWarning(warning);
	//		return false;
	//	}

	//	//Check for error during the reading of the number of header and data lines
	//	if (fscanf(f, "%s %d", str, &header_lines) == EOF || strcmp(str, "HeaderLines") //set number of header lines
	//		|| fscanf(f, "%s %d", str, &n_times) == EOF || strcmp(str, "NTimes")) //set number of lines with data
	//		return false;

	//	fromFile = true;
	//}
	//else if (flag_continue && !strcmp(str, "TimeSeries"))
	//{
	//	table = new Table();
	//	if (!table->Read(f))
	//		flag_continue = false;
	//}
	//else
	//{
	//	warning += "\n   + Error reading force data of type. \"" + std::string(str) + "\" is not a valid type";
	//	Log::AddWarning(warning);
	//	return false;
	//}


	return true;
}


//Set functions
void MoorLoad::SetFileOption(bool opt)
{ this->m_is_from_file = opt; }

void MoorLoad::SetFileName(std::string_view name)
{ this->m_file_name = name; }

void MoorLoad::SetHeaderLines(unsigned int lines)
{ this->m_header_lines = lines; }

void MoorLoad::SetNTimes(unsigned int times)
{ this->m_n_times = times; }

void MoorLoad::SetNodeID(unsigned int node_id)
{ this->m_node_id = node_id; }

void MoorLoad::SetSegment(unsigned int segment_id)
{ this->m_segment_id = segment_id; }

void MoorLoad::SetLineID(unsigned int line_id)
{ this->m_line_id = line_id; }

void MoorLoad::SetDescription(std::string_view desc)
{ this->m_description = desc; }

void MoorLoad::SetStep(unsigned int initial_step)
{ this->m_step = initial_step; }

