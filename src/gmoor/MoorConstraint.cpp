#include "PCH.h"
#include "MoorConstraint.h"
#include "AuxFunctions.h"


MoorConstraint::MoorConstraint()
	: m_number(0), m_nodeset(0), m_constraints(6)
{}

MoorConstraint::~MoorConstraint()
{}


/// 
/// SETTERS
/// 

void MoorConstraint::SetIDNumber(size_t number)
{
	m_number = number;
}
void MoorConstraint::SetNodeset(size_t nodeset)
{
	m_nodeset = nodeset;
}

void MoorConstraint::SetDof(size_t dof, const std::list<bool>& constraints)
{
	m_constraints[dof] = constraints;
}
void MoorConstraint::PushToDof(size_t dof, bool constraint)
{
	m_constraints[dof].push_back(constraint);
}
void MoorConstraint::PushX(bool constraint)
{
	m_constraints[0].push_back(constraint);
}
void MoorConstraint::PushY(bool constraint)
{
	m_constraints[1].push_back(constraint);
}
void MoorConstraint::PushZ(bool constraint)
{
	m_constraints[2].push_back(constraint);
}
void MoorConstraint::PushRotX(bool constraint)
{
	m_constraints[3].push_back(constraint);
}
void MoorConstraint::PushRotY(bool constraint)
{
	m_constraints[4].push_back(constraint);
}
void MoorConstraint::PushRotZ(bool constraint)
{
	m_constraints[5].push_back(constraint);
}


/// 
/// Overloaded Operators
/// 

bool operator<(const MoorConstraint& obj1, const MoorConstraint& obj2)
{
	return obj1.m_number < obj2.m_number;
}
bool operator>(const MoorConstraint& obj1, const MoorConstraint& obj2)
{
	return !(obj1 < obj2);
}
bool operator==(const MoorConstraint& obj1, const MoorConstraint& obj2)
{
	return obj1.m_number == obj2.m_number;
}
bool operator!=(const MoorConstraint& obj1, const MoorConstraint& obj2)
{
	return !(obj1 == obj2);
}

std::ifstream& operator>>(std::ifstream& input, MoorConstraint* constraint)
{
	std::unordered_set<std::string_view> DoFs{ "X", "Y", "Z", "ROTX", "ROTY", "ROTZ" };

	std::string readed;
	size_t dof = 0;


	// Object ID
	input >> readed;
	size_t num_ID = AuxFunctions::Reading::Try2GetObjectID<size_t>(input, readed);
	constraint->m_number = num_ID;

	input >> readed;
	do
	{
		// Check DoF
		if (DoFs.count(readed) == 0)
		{
			AuxFunctions::Reading::BackLastWord(input, readed);
			// TODO: avisar GLs sem definição
			break;
		}
		else
			DoFs.erase(readed);

		if (readed == "X")			dof = 0;
		else if (readed == "Y")		dof = 1;
		else if (readed == "Z")		dof = 2;
		else if (readed == "ROTX")	dof = 3;
		else if (readed == "ROTY")	dof = 4;
		else if (readed == "ROTZ")	dof = 5;

		// read options (MUST be '1' or '0')
		while (input >> readed && std::isdigit(readed[0]))
		{
			constraint->m_constraints[dof].push_back(
				(readed[0] == '1' ? true : false)
			);
		}
		
	} while (true);

	return input;
}

