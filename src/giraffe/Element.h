#pragma once


class Element
{
protected:
			/*--------------+
			|               |
			|   Variables   |
			|               |
			+--------------*/

	//Label (comment)
	std::string label;
	
	//Material ID
	unsigned int material;

	//Section ID
	unsigned int section;

	//Element ID
	unsigned int number;

	//Number of nodes
	unsigned int n_nodes;

	//Coordinate system ID of the element
	unsigned int cs;

	//Global nodes - conectivity
	std::vector <unsigned int> nodes;

	//Marker (to comment)
	bool mark_segment_begin;

	//============================================================================

public:
	Element();
	Element(const std::string& name);
	virtual ~Element();

	//Interface
	virtual void WriteGiraffeModelFile(FILE *f) = 0;

	///
	/// Get functions
	///
	
	std::string const& GetLabel() const;
	std::string& GetLabel();
	unsigned int GetMaterial() const;
	unsigned int GetSection() const;
	unsigned int GetNumber() const;
	unsigned int GetNNodes() const;
	unsigned int GetCS() const;
	std::vector<unsigned int> const& GetNodes() const;
	std::vector<unsigned int>& GetNodes();

	bool CheckIfIsFirstElement() const;
	

	///
	/// Set functions
	///

	void SetLabel(const std::string& name);
	void SetMaterial(unsigned int mat);
	void SetSection(unsigned int sec);
	void SetNumber(unsigned int num);
	void SetNNodes(unsigned int nnodes);
	void SetCS(unsigned int coord_sys);
	void SetNodes(const std::vector<unsigned int>& n_vec);
	void SetFirstElementBool(bool bool_option);
};

