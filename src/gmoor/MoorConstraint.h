#pragma once
//Objects inside containers
#include "AnchorConstraint.h"
#include "VesselConstraint.h"
#include "LineConstraint.h"


class MoorConstraint
{
	//Booleans to indicate which container has constraint data
	bool existAnchorConstraint, existVesselConstraint, existLineConstraint;

	//Containers with constraint objects
	std::vector<AnchorConstraint> anchors;
	std::vector<VesselConstraint> vessels;
	std::vector<LineConstraint> lines;

	//==========================================================================================================================

public:

	MoorConstraint();
	~MoorConstraint() = default;
	
		/*--------
		|Functions|
		---------*/

	//Reads input file
	bool Read(FILE* f);

	//Check input data readed
	void CheckModel(bool& modelOk, std::map<std::string_view , std::size_t>& n_keywords);

	//Check if exist at least one constraint of the type
	bool ExistAnchorConstraint(), ExistVesselConstraint(), ExistLineConstraint();

	std::vector<AnchorConstraint>& GetAnchorConstraints() { return  anchors; }
	std::vector<VesselConstraint>& GetVesselConstraints() { return  vessels; }
	std::vector<LineConstraint>& GetLineConstraints() { return  lines; }
};

