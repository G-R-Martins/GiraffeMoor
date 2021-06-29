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


	/// 
	/// Get functions
	/// 
	const std::vector<AnchorConstraint>& GetAnchorConstraints() const;
	std::vector<AnchorConstraint>& GetAnchorConstraints();
	const std::vector<VesselConstraint>& GetVesselConstraints() const;
	std::vector<VesselConstraint>& GetVesselConstraints();
	const std::vector<LineConstraint>& GetLineConstraints() const;
	std::vector<LineConstraint>& GetLineConstraints();
	
	//Check if exist at least one constraint of the type
	bool ExistAnchorConstraint(), ExistVesselConstraint(), ExistLineConstraint();
};

