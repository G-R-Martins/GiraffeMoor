#pragma once


class Element
{
protected:

	unsigned int m_id; 
	unsigned int m_material_id;
	unsigned int m_section_id;
	unsigned int m_cs_id;

	unsigned int m_tot_nodes;
	std::vector<unsigned int> m_nodes;  //Global nodes - conectivity

	bool m_mark_segment_begin;
	std::string m_label;


public:

	Element();
	Element(const std::string& name);
	Element(unsigned int id, unsigned int material_id, unsigned int section_id, unsigned int cs_id, unsigned int tot_nodes,
		std::vector<unsigned int> nodes, bool segment_begin, const std::string& label = "");
	virtual ~Element();

	virtual inline std::ofstream& WriteGiraffeFile(std::ofstream& out) = 0;
	
	///
	/// SETTERS
	///

	void SetIDNumber(unsigned int id);
	void SetLabel(const std::string& label);
	void SetMaterial(unsigned int material_id);
	void SetSection(unsigned int section_id);
	void SetCS(unsigned int cs_id);
	void SetTotNodes(unsigned int tot_nodes);
	void SetNodes(const std::vector<unsigned int>& nodes);
	void SetFirstElementOpt(bool is_first);


	///
	/// GETTERS
	///

	inline unsigned int GetNumber() const				{ return m_id; }
	inline std::string const& GetLabel() const	{ return m_label; }
	inline std::string& GetLabel()				{ return m_label; }

	inline unsigned int GetMaterial() const	{ return m_material_id; }
	inline unsigned int GetSection() const	{ return m_section_id; }
	inline unsigned int GetCS() const			{ return m_cs_id; }
	inline unsigned int GetTotNodes() const	{ return m_tot_nodes; }
	
	inline std::vector<unsigned int> const& GetNodes() const { return m_nodes; }
	inline std::vector<unsigned int>& GetNodes()			 { return m_nodes; }
	
	inline bool IsFirstElement() const { return m_mark_segment_begin; }
};

