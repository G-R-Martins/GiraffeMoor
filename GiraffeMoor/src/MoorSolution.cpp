#include "PCH.h"
#include "MoorSolution.h"
#include "LoopReading.h"
#include "Log.h"


MoorSolution::MoorSolution()
	: bool_DynamicRelax(false), decrement(0.0), dyn_relax_periods(0), TimeRelax(0), alpha_relax(0.0),
	bool_ReleaseForces(false), release_timestep(0.0), 
	seacurrent_timestep(1.0), seacurrent_max_timestep(1.0), seacurrent_min_timestep(0.000001), 
	steps_to_set_model(0), ncores(1), lin_sys_isDirect(true)
{
	solution_steps.reserve(4);
}

MoorSolution::~MoorSolution()
{}

//Reads input file
bool MoorSolution::Read(FILE *f)
{

	typedef std::unordered_set<std::string_view> uset;

	//Warning messages
	std::string ss(" -\"Solution\" block:");

	char str[200];			//salva palavras-chave lidas e valores lidos
	fpos_t pos;
	
	uset keywords({ "DynamicRelaxation", "SeaCurrentTime", "Analysis" , "Solver"});
	uset::iterator it;
	
	//Searches for comment block before solution parameters (it can be a stretch commented for a previously file, such as "DynamicRelaxation")
	AuxFunctions::Read::TryComment(f);

	//Loop to read solution parameters
	while (!fgetpos(f, &pos) && fscanf(f, "%s", str) != EOF)
	{
		it = keywords.find(std::string_view(str));
		if ( it != keywords.end())
		{
			if (*it == "DynamicRelaxation")
			{
				keywords.erase("DynamicRelaxation");
				
				//Keywords for the new loop
				uset sub_keywords({ "LineConfiguration", "PlatformForces" });

				//Next word can be a comment, another keyword from the set 'keywords' or a first level keyword. 
					//Thus, after the loop ends it must back the position, that is why the position is saved (fgetpos()) before every iteration
				while (!fgetpos(f, &pos) && fscanf(f, "%s", str) != EOF)
				{
					//If is not a subkeyword, checks for commment
					if (sub_keywords.find(std::string(str)) == sub_keywords.end())
					{
						//Backs position and tries to read a comment
						if (str[0] == '/' && AuxFunctions::Read::Comment(f, str))
						{
							//Tries again to read second level keyword after a comment
							if (!fgetpos(f, &pos) && fscanf(f, "%s", str) && sub_keywords.find(std::string(str)) == sub_keywords.end())
							{
								fsetpos(f, &pos);
								break;
							}
						}
					}
					if (!strcmp(str, "LineConfiguration"))
					{
						sub_keywords.erase("LineConfiguration");
						bool_DynamicRelax = true;

						//Reads data
						if (fscanf(f, "%s %lf", str, &decrement) && !strcmp(str, "Decrement") /*Decrement (%)*/ &&
							fscanf(f, "%s %d", str, &dyn_relax_periods) && !strcmp(str, "Periods")) /*Periods of decrement*/
							continue;
						else
						{
							ss += "\n   + Error reading dynamic relaxation parameters after 'LineConfiguration'.";
							Log::AddWarning(ss);
							return false; //ERROR
						}
					}
					else if (!strcmp(str, "PlatformForces"))
					{
						sub_keywords.erase("PlatformForces");
						bool_ReleaseForces = true;

						// Reads data 
						if (!fscanf(f, "%s %lf", str, &release_timestep) || strcmp(str, "Time"))
						{
							ss += "\n   + Error reading dynamic relaxation parameters after 'PlatformForces'.";
							Log::AddWarning(ss);
							return false;
						}
					}
					else
						break;
				} fsetpos(f, &pos);
			}
			else if (*it == "SeaCurrentTime")
			{
				keywords.erase("SeaCurrentTime");
				if (fscanf(f, "%lf", &seacurrent_timestep) != EOF)
				{
					seacurrent_max_timestep = seacurrent_timestep;
					seacurrent_min_timestep = seacurrent_timestep / 1'000.0;
				}
				else
				{
					ss += "\n   + Error reading sea current time definition.";
					Log::AddWarning(ss);
					return false;
				}
			}
			else if (*it == "Analysis")
			{
				keywords.erase("Analysis");
				if (!LoopReading::TryNestedKeyword(solution_steps, uset({ "Step" }), keywords, f, pos, str))
				{
					return false;
				}
			}
			else if (*it == "Solver")
			{
				keywords.erase("Solver");
				if (fscanf(f, "%s %d", str, &ncores) && !strcmp(str, "Cores") && //reads the number of cores and next keyword
					fscanf(f, "%s", str) && !strcmp(str, "LinSys") &&				  //checks for 'LinSys' keyword
					fscanf(f, "%s", str))											  //reads the 'LinSys' option
				{
					if (!strcmp(str, "direct"))			lin_sys_isDirect = true;
					else if (!strcmp(str, "iterative"))	lin_sys_isDirect = false;
					else
					{
						Log::AddWarning("\n   + Error reading solver option. It must be 'direct' or 'iterative'");
						return false;
					}
				}
			}
		}
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

//Getters
const std::vector<SolutionStep>& MoorSolution::GetStepsVec() const
{
	return this->solution_steps;

}
const SolutionStep& MoorSolution::GetStep(const size_t& step) const
{
	return this->solution_steps[step];

}
