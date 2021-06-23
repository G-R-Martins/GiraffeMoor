#include "PCH.h"
#include "MoorPost.h"
#include "LoopReading.h"


MoorPost::MoorPost()
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
	AuxFunctions::Read::TryComment(f);

	uset keywords({ "CADs", "PostFiles"});
	uset::iterator it;

	//Loop to read data
	while (!fgetpos(f, &pos) && fscanf(f, "%s", str) != EOF)
	{
		it = keywords.find(std::string_view(str));
		if (it != keywords.end())
		{
			if (*it == "CADs")
			{
				keywords.erase(*it);
				if (!LoopReading::TryNestedKeyword_UnorderedMultiple(platform_cads,
												   std::unordered_set<std::string_view>{ "PlatformID" },
												   std::unordered_set<std::string_view>({ "PostFiles"}),
												   f, pos, str))
				{
					return false;
				}
			}
			else if (*it == "PostFiles")
			{
				keywords.erase(*it);
				while (!fgetpos(f, &pos) && fscanf(f, "%s", str) != EOF)
				{
					//Check flag					
					if (!strcmp(str, "Mesh"))							write.mesh_flag = true;
					else if (!strcmp(str, "RenderMesh"))				write.renderMesh_flag = true;
					else if (!strcmp(str, "RigidContactSurfaces"))		write.rigidContactSurfaces_flag = true;
					else if (!strcmp(str, "FlexibleContactSurfaces"))	write.flexibleContactSurfaces_flag = true;
					else if (!strcmp(str, "Constraints"))				write.constraints_flag = true;
					else if (!strcmp(str, "Forces"))					write.forces_flag = true;
					else if (!strcmp(str, "SpecialConstraints"))		write.specialConstraints_flag = true;
					else if (!strcmp(str, "ContactForces"))			write.contactForces_flag = true;
					else if (!strcmp(str, "RenderParticles"))			write.renderParticles_flag = true;
					else if (!strcmp(str, "RenderRigidBodies"))		write.renderRigidBodies_flag = true;					
					else
					{
						fsetpos(f, &pos);
						break;
					}
				}
			}
		}
		//Not a keyword
		else if (str[0] == '/' && AuxFunctions::Read::Comment(f, str))
			continue;	//Try to read other keyword after comment
		//Other word -> backs position go to IO class
		else
		{
			fsetpos(f, &pos);
			return true;
		}
	}//end while


	//All ok while reading
	return true;
}
