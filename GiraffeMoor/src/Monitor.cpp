#include "PCH.h"
#include "Monitor.h"
#include "AuxFunctions.h"
#include "Log.h"


Monitor::Monitor()
	: sample(1), bool_nodes_fairleads(true), bool_nodes_anchors(false), bool_nodes_tdz(false),
	bool_nodes_vessel(true), bool_elements_fairleads(false), bool_elements_anchors(false),
	bool_elements_tdz(false), bool_elements_vessel(false), bool_contact_seabed_moor(false)
{}

Monitor::~Monitor()
{}

//Reads input file
bool Monitor::Read(FILE *f)
{
	//REading variables
	char str[200];
	fpos_t pos;
	typedef std::unordered_set<std::string_view> uset;
	
	//Reads sample
 	fgetpos(f, &pos);
	if (fscanf(f, "%s %d", str, &sample) != EOF && strcmp(str, "Sample"))
	{
		Log::AddWarning("\n   + Monitors sample was not defined in the input file. The default value (one) is considered");
		fsetpos(f, &pos);
	}

	/*-----------------
	 Parameters reading
	 -----------------*/
	
	//Searches for comment block before solution parameters (it can be a stretch commented for a previously file, such as "DynamicRelaxation")
	AuxFunctions::Read::TryComment(f);

	uset keywords({ "Nodes", "Elements", "Contacts" });
	uset::iterator it;

	//Loop to read data
	while (!fgetpos(f, &pos) && fscanf(f, "%s", str) != EOF)
	{
		bool try_comment = true;

		it = keywords.find(std::string_view(str));
		if (it != keywords.end())
		{
			if (*it == "Nodes")
			{
				keywords.erase(*it);

				//Reset 'true' booleans
				bool_nodes_fairleads = false; bool_nodes_vessel = false;

				while (!fgetpos(f, &pos) && fscanf(f, "%s", str) != EOF)
				{
					if (!strcmp(str, "none"))				break;
					else if (!strcmp(str, "fairleads"))		bool_nodes_fairleads = true;
					else if (!strcmp(str, "anchors"))		bool_nodes_anchors = true;
					else if (!strcmp(str, "vessels"))		bool_nodes_vessel = true;
					else if (!strcmp(str, "Sequence"))
					{
						if (fscanf(f, "%s", str) == EOF || strcmp(str, "NNodes"))
						{
							Log::AddWarning("\n   + Error reading sequence of nodes to monitor\n");
							return false;
						}
						else
						{
							seq_nodes.emplace_front();
							if (fscanf(f, "%d %s %d", &seq_nodes.front().nodes, str, &seq_nodes.front().begin) == EOF || strcmp(str, "Begin")
								|| fscanf(f, "%s %d", str, &seq_nodes.front().increment) == EOF || strcmp(str, "Increment"))
							{
								Log::AddWarning("\n   + Error reading sequence of nodes to monitor\n");
								return false;
							}
						}
					}
					else if (!strcmp(str, "List"))
					{
						while (!fgetpos(f, &pos) && fscanf(f, "%s", str) && isdigit(str[0]))
							nodes.emplace_front(atoi(str));
						fsetpos(f, &pos);
					}
					else
					{
						fsetpos(f, &pos);
						try_comment = false;
						break;
					}
				}
			}
			else if (*it == "Elements")
			{
				keywords.erase(*it);
				while (!fgetpos(f, &pos) && fscanf(f, "%s", str) != EOF)
				{
					if (!strcmp(str, "none"))				break;
					else if (!strcmp(str, "fairleads"))		bool_elements_fairleads = true;
					else if (!strcmp(str, "anchors"))		bool_elements_anchors = true;
					else if (!strcmp(str, "vessels"))		bool_elements_vessel = true;
					else if (!strcmp(str, "Sequence"))
					{
						if (fscanf(f, "%s", str) == EOF || strcmp(str, "NElements"))
						{
							Log::AddWarning("\n   + Error reading sequence of elements to monitor\n");
							return false;
						}
						else
						{
							seq_elements.emplace_front();
							if (fscanf(f, "%d %s %d", &seq_elements.front().elements, str, &seq_elements.front().begin) == EOF || strcmp(str, "Begin")
								|| fscanf(f, "%s %d", str, &seq_elements.front().increment) == EOF || strcmp(str, "Increment"))
							{
								Log::AddWarning("\n   + Error reading sequence of elements to monitor\n");
								return false;
							}
						}
					}
					else if (!strcmp(str, "List"))
					{
						while (!fgetpos(f, &pos) && fscanf(f, "%s", str) && isdigit(str[0]))
							elements.emplace_front(atoi(str));
						fsetpos(f, &pos);
					}
					else
					{
						fsetpos(f, &pos);
						try_comment = false;
						break;
					}
				}
			}
			else if (*it == "Contacts")
			{
				keywords.erase(*it);
				if (fscanf(f, "%s", str) != EOF && !strcmp(str, "seabed&lines"))
					bool_contact_seabed_moor = true;
				else
				{
					Log::AddWarning("\n   + Error reading contact monitor\n");
					return false;
				}
			}
		}
		else if (try_comment && str[0] == '/' && AuxFunctions::Read::Comment(f, str))
			continue;	//Try to read other keyword after comment
		//Other word -> backs position go to IO class
		else
		{
			fsetpos(f, &pos);
			return true;
		}
	}

	return true;
}






void Monitor::WriteGiraffeModelFile(FILE *f) const
{
	fprintf(f, "\tSample\t%d\n",sample);
	if (!nodes.empty())
	{
		fprintf(f, "\tMonitorNodes\t");
		for (const int& node : nodes)
			fprintf(f, "%d ", node);
		fprintf(f, "\n");
	}
	if (!elements.empty())
	{
		fprintf(f, "\tMonitorElements\t");
		for (const int& elem : elements)
			fprintf(f, "%d ", elem);
		fprintf(f, "\n");
	}
	if (!contacts.empty())
	{
		fprintf(f, "\tMonitorContacts\t");
		for (const int& cont : contacts)
			fprintf(f, "%d ", cont);
		fprintf(f, "\n");
	}
	if (!node_sets.empty())
	{
		fprintf(f, "\tMonitorNodeSets\t");
		for (const int& NS : node_sets)
			fprintf(f, "%d ", NS);
		fprintf(f, "\n");
	}
	
}
