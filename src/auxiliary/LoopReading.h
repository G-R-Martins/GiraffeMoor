#pragma once
#include "AuxFunctions.h"

namespace AuxFunctions {
	namespace Reading
	{
		/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
		 *					                                             *
		 *                      Templates functions                      *
		 *                                                               *
		 *  To read input file in loops when many objects can be created *
		 *					                                             *
		 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

		 /// <summary>
		 ///	
		 /// There are some functions that might seems to be unecessary repeated.
		 /// This choice was made to clarify when use ordered or unordered containers
		 /// and to avoid some 'if' statements 
		 /// 
		 /// Some examples are given before every function definition.
		 /// 
		 /// </summary>

		


		/*-+-+-+-+-+-+-+-+
		 First keyword(s)
		 +-+-+-+-+-+-+-+-*/

		 //First level keyword (e.g.: 'Keypoints', 'Vessels' ...)
		  //All repeated objects will be removed (do not use std::deque and/or classes with no operators properly overloaded)
		template<typename container>
		bool TryKeyword(container& c, const std::unordered_set<std::string_view>& keyword_set, FILE* f, fpos_t& pos, char* str)
		{
			//Tries to read second level keyword and checks for End Of File or comment
			if (!fgetpos(f, &pos) && fscanf(f, "%s", str) != EOF && keyword_set.find(std::string_view(str)) == keyword_set.end())
			{
				//Backs position and tries to read a comment
				if (!fsetpos(f, &pos) && str[0] == '/' && AuxFunctions::Read::TryComment(f))
				{
					//Tries again to read second level keyword after a comment
					if (fscanf(f, "%s", str) && keyword_set.find(std::string_view(str)) == keyword_set.end())
						return false;
				}
			}

			if (!ReadLoopKeyword(c, keyword_set, f, pos, str))
				return false;
			else
			{
				//Size before repeated elements excluded
				size_t before = c.size();

				//Sorting and excluding repeated objects
				std::sort(c.begin(), c.end());
				c.erase(std::unique(c.begin(), c.end()), c.end());

				//Removed objects
				size_t removed = before - c.size();
				if (removed > 0)
				{
					std::string warning = "\n   + " + std::to_string(removed) + " repeated \"" + std::string(*keyword_set.begin()) + "(s)\" removed.";
					Log::AddWarning(warning);
				}
				c.shrink_to_fit();
			}

			return true;
		}

		//First level keyword (e.g.: 'NodalForces', 'VesselDisplacements' ...)
		 //Do not check if there is repeated objects (can be std::deque and/or classes without operators overloaded)
		template<typename container>
		bool TryKeyword_UnorderedMultiple(container& c, const std::unordered_set<std::string_view>& keyword_set, FILE* f, fpos_t& pos, char* str)
		{
			//Tries to read second level keyword and checks for End Of File or comment
			if (!fgetpos(f, &pos) && fscanf(f, "%s", str) != EOF && keyword_set.find(std::string_view(str)) == keyword_set.end())
			{
				//Backs position and tries to read a comment
				if (!fsetpos(f, &pos) && str[0] == '/' && AuxFunctions::Read::TryComment(f))
				{
					//Tries again to read second level keyword after a comment
					if (fscanf(f, "%s", str) && keyword_set.find(std::string_view(str)) == keyword_set.end())
						return false;
				}
			}

			if (!ReadLoopKeyword(c, keyword_set, f, pos, str))
				return false;

			return true;
		}

		/*-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
		 Second(or higher) level keyword(s)
		 +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-*/

		 //Second (or higher) level keyword (e.g.: 'Line', 'Connectivity' ...)
		  //All repeated objects will be removed (do not use std::deque and/or classes with no operators properly overloaded)
		template<typename container>
		bool TryNestedKeyword(container& c, const std::unordered_set<std::string_view>& keyword_set,
			const std::unordered_set<std::string_view>& upper_keyword_set, FILE* f, fpos_t& pos, char* str)
		{
			//Tries to read second level keyword and checks for End Of File or comment
			if (!fgetpos(f, &pos) && fscanf(f, "%s", str) != EOF && keyword_set.find(std::string_view(str)) == keyword_set.end())
			{
				//Backs position and tries to read a comment
				if (!fsetpos(f, &pos) && str[0] == '/' && AuxFunctions::Read::TryComment(f))
				{
					//Tries again to read second level keyword after a comment
					if (fscanf(f, "%s", str) && keyword_set.find(std::string_view(str)) == keyword_set.end())
						return false;
				}
			}

			if (!ReadLoopKeyword(c, keyword_set, upper_keyword_set, f, pos, str))
				return false;
			else
			{
				//Size before repeated elements excluded
				size_t before = c.size();

				//Sorting and excluding repeated objects
				std::sort(c.begin(), c.end());
				c.erase(std::unique(c.begin(), c.end()), c.end());

				//Removed objects
				size_t removed = before - c.size();

				if (removed > 0)
				{
					std::string warning = "\n   + " + std::to_string(removed) + " repeated \"" + std::string(*keyword_set.begin()) + "(s)\" removed.";
					Log::AddWarning(warning);
				}

				c.shrink_to_fit();
			}

			return true;
		}

		//Second (or higher) level keyword (e.g.: 'Line', 'Keypoint', 'Connectivity' ...)
		 //Do not check if there is repeated objects (can be std::deque and/or classes without operators overloaded)
		template<typename container>
		bool TryNestedKeyword_UnorderedMultiple(container& c, const std::unordered_set<std::string_view>& keyword_set,
			const std::unordered_set<std::string_view>& upper_keyword_set, FILE* f, fpos_t& pos, char* str)
		{
			//Tries to read second level keyword and checks for End Of File or comment
			if (!fgetpos(f, &pos) && fscanf(f, "%s", str) != EOF && keyword_set.find(std::string_view(str)) == keyword_set.end())
			{
				//Backs position and tries to read a comment
				if (!fsetpos(f, &pos) && str[0] == '/' && AuxFunctions::Read::TryComment(f))
				{
					//Tries again to read second level keyword after a comment
					if (fscanf(f, "%s", str) && keyword_set.find(std::string_view(str)) == keyword_set.end())
						return false;
				}
			}

			if (!ReadLoopKeyword(c, keyword_set, upper_keyword_set, f, pos, str))
				return false;

			return true;
		}

		/*-+-+-+-+-+-+-+
		 Reading loops
		 +-+-+-+-+-+-+-*/

		 //When different words led to the SAME read function and there is keyword(s) of other diffent level(s) to check
		  //(eg: 'PilotID' and 'Label' at 'Platform')
		template<typename container>
		bool ReadLoopKeyword(container& c, const std::unordered_set<std::string_view>& keyword_set,
			const std::unordered_set<std::string_view>& upper_keyword_set, FILE* f, fpos_t& pos, char* str)
		{
			while (true)
			{
				//if (!c.emplace_back().Read(f))
					return false; //ERROR while reading

				//Other word or a possible comment
				if (!fgetpos(f, &pos) && fscanf(f, "%s", str) == EOF)
				{
					fsetpos(f, &pos);
					return true; // return LoopReadingStatus::Ok;
				}
				else if (keyword_set.find(std::string_view(str)) == keyword_set.end())
				{
					//Searches for comment and read next word
					if (str[0] == '/' && !fsetpos(f, &pos) && AuxFunctions::Read::TryComment(f) /*comment*/
						&& !fgetpos(f, &pos) && fscanf(f, "%s", str) == EOF) /*next word*/
					{
						fsetpos(f, &pos);
						return true;
					}
					//Checks for another keyword
					else if (keyword_set.find(std::string_view(str)) != keyword_set.end())
						continue /*Do nothing, continue the loop*/;
					//Checks for an upper level keyword
					else if (upper_keyword_set.find(std::string_view(str)) != upper_keyword_set.end())
					{
						fsetpos(f, &pos);
						return true;
					}
					//Checks for a first level keyword
					else if (AuxFunctions::Read::isKeyword(str))
					{
						fsetpos(f, &pos);
						return true;
					}
					//Other word -> ERROR
					else
						return false;
				}//If a keyword was readed
			}//End while

			//While reading ok
			return true;
		}


		//When different words led to the SAME read function (eg: 'Line' and 'MooringLine' ...)
		template<typename container>
		bool ReadLoopKeyword(container& c, const std::unordered_set<std::string_view>& keyword_set, FILE* f, fpos_t& pos, char* str)
		{
			while (true)
			{
				if (!c.emplace_back().Read(f))
					return false; //ERROR while reading

				//Other word or a possible comment
				if (!fgetpos(f, &pos) && fscanf(f, "%s", str) == EOF)
				{
					fsetpos(f, &pos);
					return true;
				}
				//Checks for keyword
				else if (keyword_set.find(std::string_view(str)) == keyword_set.end())
				{
					//Searches for comment and read next word
					if (str[0] == '/' && !fsetpos(f, &pos) && AuxFunctions::Read::TryComment(f) && !fgetpos(f, &pos)
						&& fscanf(f, "%s", str) == EOF)
					{
						fsetpos(f, &pos);
						return true; //end of file
					}
					//Checks for another keyword
					else if (keyword_set.find(std::string_view(str)) != keyword_set.end())
						continue /*Do nothing, continue the loop*/;
					//Checks for a first level keyword
					else if (AuxFunctions::Read::isKeyword(str))
					{
						fsetpos(f, &pos);
						return true;
					}
					//Other word -> ERROR
					else
						return false;
				}//If a keyword was readed
			}//End while
			return true;
		}
	}
}