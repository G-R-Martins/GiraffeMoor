#pragma once

/// Structs with guidelines to create monitors
struct NodesSequence { unsigned int nodes, begin, increment; };
struct ElementsSequence { unsigned int elements, begin, increment; };


class Monitor
{
private:
	//Containers with monitor numbers
	std::forward_list<unsigned int> m_nodes_id;
	std::forward_list<unsigned int> m_elements_id;
	std::forward_list<unsigned int> m_contacts_id;
	std::forward_list<unsigned int> m_node_sets_id;

	//Containers with structs to create monitors
	std::forward_list<NodesSequence> m_nodes_sequence_hint;
	std::forward_list<ElementsSequence> m_elements_sequence_hint;

	//Monitor sample
	unsigned int m_sample;

	//Booleans to indicate which type of data will be monitored
	bool m_nodes_fairleads_opt;
	bool m_nodes_anchors_opt;
	bool m_nodes_tdz_opt;
	bool m_nodes_vessel_opt;
	bool m_elements_fairleads_opt;
	bool m_elements_anchors_opt;
	bool m_elements_tdz_opt;
	bool m_elements_vessel_opt;
	bool m_contact_seabed_lines_opt;

public:
	Monitor();
	~Monitor();


	///
	/// SETTERS
	/// 
	
	void PushNodeID(unsigned int node_id);
	void PushElementID(unsigned int element_id);
	void PushContactID(unsigned int contact_id);
	void PushNodeSetID(unsigned int node_set_id);

	NodesSequence* AddNodesSequence(unsigned int nodes, unsigned int begin, unsigned int increment);
	NodesSequence* AddNodesSequence();
	void PushNodesSequence(unsigned int nodes, unsigned int begin, unsigned int increment);
	void PushNodesSequence();
	
	ElementsSequence* AddElementsSequence(unsigned int elements, unsigned int begin, unsigned int increment);
	ElementsSequence* AddElementsSequence();
	void PushElementsSequence(unsigned int elements, unsigned int begin, unsigned int increment);
	void PushElementsSequence();
	
	void SetSample(unsigned int sample);

	//Booleans to indicate which type of data will be monitored
	void SetMonitorFairleadNodesOpt(bool nodes_fairleads_opt);
	void SetMonitorAnchorNodesOpt(bool nodes_anchors_opt);
	void SetMonitorTDZNodesOpt(bool nodes_tdz_opt);
	void SetMonitorVesselNodesOpt(bool nodes_vessel_opt);
	void SetMonitorFairleadElementsOpt(bool elements_fairleads_opt);
	void SetMonitorAnchorElementsOpt(bool elements_anchors_opt);
	void SetMonitorTDZElementsOpt(bool elements_tdz_opt);
	void SetMonitorVesselElementsOpt(bool elements_vessel_opt);
	void SetMonitorLinesSeabedContactOpt(bool contact_seabed_lines_opt);

	void SetAllNodesFlags(bool option);
	void SetAllElementsFlags(bool option);


	///
	/// GETTERS
	/// 
	
	inline std::forward_list<unsigned int> GetNodeIDs() const		{ return m_nodes_id; }
	inline std::forward_list<unsigned int> GetElementIDs() const	{ return m_elements_id; }
	inline std::forward_list<unsigned int> GetContactIDs() const	{ return m_contacts_id; }
	inline std::forward_list<unsigned int> GetNodeSetIDs() const	{ return m_node_sets_id; }
	inline unsigned int GetSample() const							{ return m_sample; }
	
	inline std::forward_list<NodesSequence> const* GetNodesSequence() const			{ return &m_nodes_sequence_hint; };
	inline std::forward_list<NodesSequence>* GetNodesSequence()						{ return &m_nodes_sequence_hint; };
	inline std::forward_list<ElementsSequence> const* GetElementsSequence() const	{ return &m_elements_sequence_hint; };
	inline std::forward_list<ElementsSequence>* GetElementsSequence()				{ return &m_elements_sequence_hint; };

	//Booleans to indicate which type of data will be monitored
	bool MonitorFairleadNodes() const		{ return m_nodes_fairleads_opt; }
	bool MonitorAnchorNodes() const			{ return m_nodes_anchors_opt; }
	bool MonitorTDZNodes() const			{ return m_nodes_tdz_opt; }
	bool MonitorVesselNodes() const			{ return m_nodes_vessel_opt; }
	bool MonitorFairledElements() const		{ return m_elements_fairleads_opt; }
	bool MonitorAnchorElements() const		{ return m_elements_anchors_opt; }
	bool MonitorTDZElements() const			{ return m_elements_tdz_opt; }
	bool MonitorVesselElements() const		{ return m_elements_vessel_opt; }
	bool MonitorLinesSeabedContact() const	{ return m_contact_seabed_lines_opt; }


	/// 
	/// Overloaded operators
	/// 

	friend std::ostream& operator<<(std::ostream& out, const Monitor& obj);
};