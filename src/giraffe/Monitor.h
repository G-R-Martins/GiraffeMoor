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

	//Writes Giraffe file data
	void WriteGiraffeModelFile(FILE *f) const;

	//============================================================================

	/*------------------------------------------
	  Structs with guidelines to create monitors
	 ------------------------------------------*/
	struct SequenceNodes { unsigned int nodes, begin, increment; };
	struct SequenceElements { unsigned int elements, begin, increment; };

	/*-------
	Variables
	--------*/

	//Vectors with monitor numbers
	std::forward_list<unsigned int> nodes;
	std::forward_list<unsigned int> elements;
	std::forward_list<unsigned int> contacts;
	std::forward_list<unsigned int> node_sets;
	
	//Containers with structs to create monitors
	std::forward_list<SequenceNodes> seq_nodes;
	std::forward_list<SequenceElements> seq_elements;

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