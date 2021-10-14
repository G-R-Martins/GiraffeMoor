#pragma once


class Element
{
protected:

	size_t m_number; 
	size_t m_material;
	size_t m_section;
	size_t m_cs;

	unsigned int m_tot_nodes;
	std::vector<unsigned int> m_nodes;  //Global nodes - conectivity

	bool m_mark_segment_begin;
	std::string m_label;


public:

	Element();
	Element(const std::string& name);
	Element(size_t number, size_t material, size_t section, size_t cs, unsigned int tot_nodes, 
		std::vector<unsigned int> nodes, bool segment_begin, const std::string& label = "");
	virtual ~Element();

	virtual inline std::ofstream& WriteGiraffeFile(std::ofstream& out) = 0;
	
	///
	/// SETTERS
	///

	void SetIDNumber(size_t number);
	void SetLabel(const std::string& label);
	void SetMaterial(size_t material);
	void SetSection(size_t section);
	void SetCS(size_t cs);
	void SetTotNodes(unsigned int tot_nodes);
	void SetNodes(const std::vector<unsigned int>& nodes);
	void SetFirstElementOpt(bool option);


	///
	/// GETTERS
	///

	inline size_t GetNumber() const				{ return m_number; }
	inline std::string const& GetLabel() const	{ return m_label; }
	inline std::string& GetLabel()				{ return m_label; }

	inline size_t GetMaterial() const	{ return m_material; }
	inline size_t GetSection() const	{ return m_section; }
	inline size_t GetCS() const			{ return m_cs; }
	inline size_t GetTotNodes() const	{ return m_tot_nodes; }
	
	inline std::vector<unsigned int> const& GetNodes() const { return m_nodes; }
	inline std::vector<unsigned int>& GetNodes()			 { return m_nodes; }
	
	inline bool IsFirstElement() const { return m_mark_segment_begin; }
};

