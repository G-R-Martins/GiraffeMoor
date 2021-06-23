#include "PCH.h"
#include "LineConstraint.h"
#include "Log.h"


LineConstraint::LineConstraint()
	: number(0), constraints(6)
{}

LineConstraint::~LineConstraint()
{}

//Reads input file
bool LineConstraint::Read(FILE* f)
{
	//Keeps readed words and numbers
	char str[200];

	//Stream to save position
	fpos_t pos;

	//Tries to read the first coordinate keyword
	if (fscanf(f, "%d %s", &number, str) == EOF)
	{
		Log::AddWarning("\n   + Error reading vessel ID at 'LineConstraint' block.");
		return false;
	}

	std::unordered_set<std::string_view> to_constraint = {"X",  "Y",  "Z", "ROTX",  "ROTY",  "ROTZ"};
	std::unordered_set<std::string_view>::iterator it_dof;

	while (true)
	{
		int dof;

		it_dof = to_constraint.find(std::string_view(str));

		//Check if is another word
		if ( it_dof == to_constraint.end() )
		{ fsetpos(f, &pos); break; }
		//Otherwise, read DoF constraint definition
		else
		{
			if ( *it_dof == "X")		{ dof = 0; to_constraint.erase(std::string_view(str)); }
			else if (*it_dof == "Y")	{ dof = 1; to_constraint.erase(std::string_view(str)); }
			else if (*it_dof == "Z")	{ dof = 2; to_constraint.erase(std::string_view(str)); }
			else if (*it_dof == "ROTX")	{ dof = 3; to_constraint.erase(std::string_view(str)); }
			else if (*it_dof == "ROTY")	{ dof = 4; to_constraint.erase(std::string_view(str)); }
			else if (*it_dof == "ROTZ")	{ dof = 5; to_constraint.erase(std::string_view(str)); }

			//Current constraint
			while ( true )
			{
				//Saves position
				fgetpos(f, &pos);

				//Tries to read a number (1 or 0)
				if ( fscanf(f, "%s", str) && isdigit(str[0]) )
				{
					bool add = (str[0] == '1') ? true : false;
					constraints[dof].push_back(add);
				}
				//No constraint defined for the current DOF
				else if ( constraints[dof].empty() )
				{
					std::string warning = std::string("\n   + Any constraint was defined for the DoF '") + 
						std::string(*it_dof) +  "' of the line number " + std::to_string(number) + 
						"\n       Please, check your Giraffe input file.";
					Log::AddWarning(warning);
				}
				//It can be other keyword
				else
					break;
			}
		}
	}


	if ( !to_constraint.empty() )
	{
		std::string warning = "\n   + There is(are) " + std::to_string(to_constraint.size()) + 
			" DoF(s) with any constraint defined for the line number " + std::to_string(number) + 
			".\n       Make sure you are getting the desirable constraints.";
		Log::AddWarning(warning);
	}

	return true;
}


/*-----------
Get functions
-----------*/

unsigned int LineConstraint::GetNumberID() const
{ return this->number; }

//Number constraints at the DoF
unsigned int LineConstraint::GetSizeX()
{ return (unsigned int)this->constraints[0].size(); }
unsigned int LineConstraint::GetSizeY()
{ return (unsigned int)constraints[1].size(); }
unsigned int LineConstraint::GetSizeZ()
{ return (unsigned int)this->constraints[2].size(); }
unsigned int LineConstraint::GetSizeRotX()
{ return (unsigned int)this->constraints[3].size(); }
unsigned int LineConstraint::GetSizeRotY()
{ return (unsigned int)this->constraints[4].size(); }
unsigned int LineConstraint::GetSizeRotZ()
{ return (unsigned int)this->constraints[5].size(); }

//Get the container with constraints for a specific DoF
std::list <bool> const& LineConstraint::GetDoFConstraints(const size_t& dof)
{ return this->constraints[dof]; }


/*------------------
Overloaded operators
-------------------*/
bool operator<(const LineConstraint& line1, const LineConstraint& line2)
{ return line1.number < line2.number; }
bool operator>(const LineConstraint& line1, const LineConstraint& line2)
{ return !(line1 < line2); }

bool operator==(const LineConstraint& line1, const LineConstraint& line2)
{ return line1.number == line2.number; }
bool operator!=(const LineConstraint& line1, const LineConstraint& line2)
{ return !(line1 == line2); }
