#include "PCH.h"
#include "GiraffeSolver.h"
#include "Log.h"
#include "AuxFunctions.h"


GiraffeSolver::GiraffeSolver()
	: nCores(2), isDirect(true), runGiraffe(false)
{}


bool GiraffeSolver::Read(FILE* f)
{
	char str[200];
	fpos_t pos;


	std::unordered_set<std::string_view> keywords({"Run", "Processors"});
	std::unordered_set<std::string_view>::iterator it;

	//Searches for comment block before solution parameters (it can be a stretch commented for a previously file, such as "DynamicRelaxation")
	AuxFunctions::Read::TryComment(f);

	//Loop to read solution parameters
	while (!fgetpos(f, &pos) && fscanf(f, "%s", str) != EOF)
	{
		it = keywords.find(std::string_view(str));
		if ( it != keywords.end() )
		{
			if ( *it == "Run" )
			{
				keywords.erase("Run");
				if ( fscanf(f, "%s", str) == EOF )
				{
					Log::AddWarning("\n   + Error reading solver option");
					return false;
				}
				else if ( !strcmp(str, "true") || !strcmp(str, "1") )
					runGiraffe = true;
				else if ( !strcmp(str, "false") || !strcmp(str, "0") )
					runGiraffe = false;
				else
				{
					Log::AddWarning("\n   + Error reading solver option after 'Run' keyword. It must be 'true/false' or '1/0'");
					return false;
				}
			}
			else if ( *it == "Processors" )
			{
				keywords.erase("Processors");
				if ( fscanf(f, "%s %d", str, &nCores) && !strcmp(str, "Cores") && //reads the number of cores and next keyword
					fscanf(f, "%s", str) && !strcmp(str, "LinSys") &&			  //checks for 'LinSys' keyword
					fscanf(f, "%s", str) )										  //reads the 'LinSys' option
				{
					if ( !strcmp(str, "direct") )			isDirect = true;
					else if ( !strcmp(str, "iterative") )	isDirect = false;
					else
					{
						Log::AddWarning("\n   + Error reading solver option after 'LynSys' keyword. It must be 'direct' or 'iterative'");
						return false;
					}
				}
			}
		} // end if 'keywords'
		else if (str[0] == '/' && AuxFunctions::Read::Comment(f, str))
			continue;	//Other word -> end loop and backs to IO class
		else
		{
			fsetpos(f, &pos);
			break;
		}
	}


	//All ok while reading
	return true;
}


void GiraffeSolver::WriteGiraffeModelFile(std::ostream& fout) const
{
	fout << "\tProcessors " << nCores <<
		"\tLinSys ";

	fout << (isDirect ? "Direct\n" : "Iterative\n");
}

///
/// Set/Get functions
///

void GiraffeSolver::SetSolverOptions(unsigned int cores, bool bool_direct)
{ 
	this->nCores = cores;	
	this->isDirect = bool_direct; 
}

bool GiraffeSolver::GetRunOption()
{ return runGiraffe; }