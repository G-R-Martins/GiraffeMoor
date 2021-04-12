#pragma once


class NodeSet
{
public:
	//Construct a empty nodeset -> list of nodes
	NodeSet();

	//Construct a nodeset to be used with sequence of nodes
	NodeSet(const unsigned int& num_nodes, const unsigned int& node0, const unsigned int& inc);		
	
	//Destructor
	~NodeSet();
	
	//Writes Giraffe file
	void WriteGiraffeModelFile(FILE *f);
	
	//============================================================================

	/*-------
	Variables
	--------*/

	//Node set ID (list)
	unsigned int number;

	//Number or nodes
	unsigned int total_nodes;
	
	//Initial node (sequence)
	unsigned int init;

	//Increment (sequence)
	unsigned int increment;

	//Comment
	char comment[100];

	//Vector with nodes
	std::vector <unsigned int> nodes;

	//============================================================================

	/*------------------
	Overloaded operators
	-------------------*/

	friend bool operator<(const NodeSet& ns1, const NodeSet& ns2);
	friend bool operator>(const NodeSet& ns1, const NodeSet& ns2);
	friend bool operator!=(const NodeSet& ns1, const NodeSet& ns2);
	friend bool operator==(const NodeSet& ns1, const NodeSet& ns2);
	NodeSet& operator=(NodeSet&& other) noexcept = default;
	NodeSet& operator=(const NodeSet& other) = default;


	NodeSet(NodeSet&& other) noexcept = default;
	NodeSet(const NodeSet& other) = default;

};

