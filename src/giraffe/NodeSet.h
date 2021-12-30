#pragma once


class NodeSet
{
private:
	unsigned int m_id;
	unsigned int m_total_nodes;
	unsigned int m_node_init;  //Initial node (sequence)
	unsigned int m_increment;
	std::string m_comment;  //optional

	std::vector<unsigned int> m_nodes;

public:
	NodeSet();
	// Construct a list of nodesets
	NodeSet(unsigned int id, const std::vector<unsigned int>& nodes, const std::string& comment="\0");
	NodeSet(unsigned int id, const std::vector<unsigned int>& nodes, std::string& comment);
	//Construct a nodeset to be used with sequence of nodes
	NodeSet(unsigned int id, unsigned int total_nodes, unsigned int node_init, 
		unsigned int increment, const std::string& comment="\0");
	NodeSet(unsigned int id, unsigned int total_nodes, unsigned int node_init, 
		unsigned int increment, std::string& comment);
	
	//Destructor
	~NodeSet();
	

	///
	/// SETTERS
	/// 

	void SetIDNumber(unsigned int id);
	void SetNNodes(unsigned int total_nodes);
	void SetNodeInit(unsigned int node_init);
	void SetIncrement(unsigned int increment);
	void SetComment(const std::string& comment);
	void SetNodes(std::vector<unsigned int> nodes);

	///
	/// GETTERS
	/// 
	
	inline unsigned int GetNumber() const { return m_id; };
	inline unsigned int GetNNodes() const { return (unsigned int)m_nodes.size(); };
	inline unsigned int GetNodeInit() const { return m_node_init; };
	inline unsigned int GetIncrement() const { return m_increment; };
	inline const std::string& GetComment() const { return m_comment; };
	inline std::string& GetComment() { return m_comment; };
	inline const std::vector<unsigned int>& GetNodes() const { return m_nodes; };

	
	/// 
	/// Overloaded operators
	/// 

	friend bool operator<(const NodeSet& ns1, const NodeSet& ns2);
	friend bool operator>(const NodeSet& ns1, const NodeSet& ns2);
	friend bool operator!=(const NodeSet& ns1, const NodeSet& ns2);
	friend bool operator==(const NodeSet& ns1, const NodeSet& ns2);
	NodeSet& operator=(NodeSet&& other) noexcept = default;
	NodeSet& operator=(const NodeSet&) = default;


	NodeSet(NodeSet&& other) noexcept = default;
	NodeSet(const NodeSet& other) = default;

	friend std::ostream& operator<<(std::ostream& out, const NodeSet& obj);
};

