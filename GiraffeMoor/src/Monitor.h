#pragma once


class Monitor
{
public:
	Monitor();
	~Monitor();

	//============================================================================

	/*-------
	Functions
	--------*/

	//Reads input file
	bool Read(FILE *f);
	//bool ReadMonitorData(FILE* f, fpos_t& pos, std::unordered_set<std::string_view>& sub_keywords, char* str);

	//Writes Giraffe file data
	void WriteGiraffeModelFile(FILE *f) const;

	//============================================================================

	/*-------
	Variables
	--------*/

	//Vectors with monitor numbers
	std::forward_list <unsigned int> nodes;
	std::forward_list <unsigned int> elements;
	std::forward_list <unsigned int> contacts;
	std::forward_list <unsigned int> node_sets;
	
	//Monitor sample
	int sample;

	//Booleans to indicate wath type of data will be monitored
	bool bool_nodes_fairleads;
	bool bool_nodes_anchors;
	bool bool_nodes_tdz;
	bool bool_nodes_vessel;
	bool bool_elements_fairleads;
	bool bool_elements_anchors;
	bool bool_elements_tdz;
	bool bool_elements_vessel;
	bool bool_contact_seabed_moor;

};