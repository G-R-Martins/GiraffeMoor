#pragma once
#include "ExternalTimeHistory.h"


class MoorLoad : public ExternalTimeHistory
{
protected:
	//Node
	unsigned int m_node_id;
	unsigned int m_segment_id;
	unsigned int m_line_id;

	//Name -> vessel (ID), first, middle or last (node of segment)
	std::string m_description;


public:
	MoorLoad();
	~MoorLoad();
	

	///
	///Set functions
	///
	
	void SetNodeID(unsigned int node_id);
	void SetSegment(unsigned int segment_id);
	void SetLineID(unsigned int line_id);
	void SetDescription(std::string_view desc);

	///
	///Get functions
	///
	
	inline unsigned int GetNodeID() const			{ return this->m_node_id; }
	inline unsigned int GetNodeID()					{ return this->m_node_id; }
	inline unsigned int GetSegmentID() const		{ return this->m_segment_id; }
	inline unsigned int GetSegmentID()				{ return this->m_segment_id; }
	inline unsigned int GetLineID() const			{ return this->m_line_id; }
	inline unsigned int GetLineID()					{ return this->m_line_id; }
	inline std::string_view GetDescription() const	{ return this->m_description; }

};
