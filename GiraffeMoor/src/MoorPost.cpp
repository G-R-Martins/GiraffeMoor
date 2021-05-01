#include "PCH.h"
#include "MoorPost.h"
#include "GiraffeModel.h"
#include "AuxFunctions.h"

//Global object
extern GiraffeModel gm;

//Static member
//std::vector<std::string> MoorPost::platform_names;
std::map<size_t, std::string> MoorPost::platform_names;

MoorPost::MoorPost()
{}

MoorPost::~MoorPost()
{}


//Reads input file
bool MoorPost::Read(FILE *f)
{

	//Keywords
	typedef std::unordered_set<std::string_view> uset;

	//Saves readed keywords and values
	char str[200];
	
	//Stream with current position
	fpos_t pos;
	
	//Saves current position after trying to read direction
	fgetpos(f, &pos);


	/*-----------------
	 Parameters reading
	 -----------------*/

	//Searches for comment block before keywords
	AuxFunctions::TryComment(f);

	uset keywords({ "CADs", "PostFiles"});
	uset::iterator it;

	//Loop to read data
	while (!fgetpos(f, &pos) && fscanf(f, "%s", str) != EOF)
	{
		bool try_comment = true;

		it = keywords.find(std::string_view(str));
		if (it != keywords.end())
		{
			if (*it == "CADs")
			{
				keywords.erase(*it);

				while (!fgetpos(f, &pos) && fscanf(f, "%s", str) != EOF)
				{
					if (!strcmp(str, "PlatformID"))
					{
						if (fscanf(f, "%s", str) != EOF)
							platform_names[2] = str;
					}
				}
			}
			else if (*it == "PostFiles")
			{
				keywords.erase(*it);
				while (!fgetpos(f, &pos) && fscanf(f, "%s", str) != EOF)
				{
					//Check flag
					if (!strcmp(str, "Forces"))						gm.post.WriteForces_flag = true;
					else if (!strcmp(str, "ContactForces"))			gm.post.WriteContactForces_flag = true;
					else if (!strcmp(str, "SpecialConstraints"))	gm.post.WriteSpecialConstraints_flag = true;
					else if (!strcmp(str, "ContactSurface"))			gm.post.WriteRigidContactSurfaces_flag = true;
					else
					{
						fsetpos(f, &pos);
						try_comment = false;
						break;
					}
				}
			}
		}
		//Not a keyword
		else if (try_comment && str[0] == '/' && AuxFunctions::ReadComment(f, str))
			continue;	//Try to read other keyword after comment
		//Other word -> backs position go to IO class
		else
		{
			fsetpos(f, &pos);
			return true;
		}
	}//end while

	return true;
}

std::tuple<bool, std::string> MoorPost::GetName(size_t plat_num)
{
	//Searches for key -> returns an iterator
	auto it = platform_names.find(plat_num);

	//Key founded
	if (it != platform_names.end())
	{
		return std::make_tuple(true, platform_names[plat_num]);
	}
	//Key not founded (invalid value)
	else
		return std::make_tuple(false, std::string(""));
}

