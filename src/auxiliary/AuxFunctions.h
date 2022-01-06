#pragma once
#include "Log.h"


typedef std::unordered_set<std::string_view> USET_SV;
typedef std::unordered_set<std::string> USET_STR;
typedef std::unordered_set<std::string_view>::iterator IT_USET_SV;
typedef std::pair<bool, std::string_view> PAIR_BOOL_SV;
typedef std::unordered_map<std::string_view, std::function<bool(std::string& readed)>> MAP_FUNC;
typedef std::_Node_handle<std::allocator<std::_List_node<std::string_view, void*>>::value_type, std::allocator<std::string_view>, std::_Node_handle_set_base, std::string_view> NODE_HANDLE_USET_SV;

namespace AuxFunctions
{
/// <summary>
///		
///		This namespace has 2 namespaces: 
///			- Read: additional functions, mainly to read commend and keywords
///			- Time: useful to measure/compare time
///		
/// </summary>
	


	namespace Reading
	{
		/// <summary>
		///		
		///		In this namespace some auxiliary functions to the 'LoopReading' 
		///		are defined, its goal is to read comment and check for valid keyword.
		///		
		/// </summary>


		/*-- Return type for node handle extraction function --*/
		enum class NODE_EXTRACTION_STATUS { NONE = -1, FALSE, TRUE, BREAK };

		/*=========================*
		 *  Function declarations  *
		 *=========================*/

		// Check if the current word is part of a comment and read next word
		static void TryCommentAndContinue(std::ifstream& input, std::string& readed);

		static bool ReadBlockComment(std::ifstream& input, std::string& readed);
		static bool ReadLineComment(std::ifstream& input, std::string& readed);
		static bool CheckComment(std::ifstream& input, std::string& readed);

		static bool ReadBlock(std::ifstream& input, std::string& readed, MAP_FUNC& mandatory_keys, MAP_FUNC& optional_keys);
		
		static int GetCurrentLine(std::ifstream& input);  // Taken from https://stackoverflow.com/questions/4813129/how-to-get-the-line-number-from-a-file-in-c
		static void BackLastWord(std::ifstream& input, std::string_view last_word);
		static void BackLastWord(std::ifstream& input, std::string last_word);
		static NODE_EXTRACTION_STATUS ExtractNodeHandle(std::ifstream& input, NODE_HANDLE_USET_SV& nh, std::string_view readed, std::string_view block, std::string_view name, USET_SV& mandatory_names, USET_SV& optional_names = USET_SV{});

		static Table&& ReadTable(std::ifstream& input, size_t lines = 0);
		static std::string ReadDelimitedString(std::ifstream& input, const std::array<char, 2>& delimeters);

		/*====================*
		 *  Static functions  *
		 *====================*/


		/*--- Read all comments and the next (key)word ---*/
		static void TryCommentAndContinue(std::ifstream& input, std::string& readed)
		{
			while (CheckComment(input, readed))
				input >> readed;
		}
		
		static bool CheckComment(std::ifstream& input, std::string& readed)
		{
			return (readed[0] == '/' && 
				(ReadLineComment(input, readed) || ReadBlockComment(input, readed)));
		}

		static bool ReadLineComment(std::ifstream& input, std::string& readed)
		{
			if (readed[1] == '/')
			{
				//input.getline(c_ptr, 100'000, '\n');
				input.ignore(1'000'000, '\n');
				return true;
			}
			return false;
		}
		
		static bool ReadBlockComment(std::ifstream& input, std::string& readed)
		{
			if (readed[1] == '*')
			{
				input.ignore(1'000'000, '*');
				input >> readed;
				return readed[0] == '/';
			}
			return false;
		}


		/*--- File ---*/
		static int GetCurrentLine(std::ifstream& input)
		{
			int num_lines = 1;

			// Clear error bits
			input.clear();

			// Get current position and back to the file begin
			std::streampos original_pos = input.tellg();
			if (original_pos < 0)
				return -1;
			input.seekg(0);

			// Count lines
			char c;
			while ((input.tellg() < original_pos) && input.get(c))
				if (c == '\n') ++num_lines;

			return num_lines;
		}

		static void BackLastWord(std::ifstream& input, std::string_view last_word)
		{
			std::streampos after_word = input.tellg();
			input.seekg(after_word - (std::streampos)last_word.size());
		}
		
		static void BackLastWord(std::ifstream& input, std::string last_word)
		{
			std::streampos after_word = input.tellg();
			input.seekg(after_word - (std::streampos)last_word.size());
		}

		/*--- Reading ---*/

		static bool ReadBlock(std::ifstream& input, std::string& readed, MAP_FUNC& mandatory_keys, MAP_FUNC& optional_keys)
		{
			TryCommentAndContinue(input, readed);
			
			// Try to extract node (handle) from map with mandatory blocks reading funcitons...
			auto nh = mandatory_keys.extract(readed);
			// ... check if is not a valid keyword ...
			if (nh.empty())
			{	
				// ... try to extract from optional keywords ...
				nh = optional_keys.extract(readed);
				// ... if it fails, it is an invalid word
				if (nh.empty()) 
					return false;
			}
			
			// Invoke the reading function (at IO class)
			if (!nh.mapped()(readed))
				return false; // ERROR while reading the input file

			return true;
		}

		static NODE_EXTRACTION_STATUS ExtractNodeHandle(std::ifstream& input, NODE_HANDLE_USET_SV& nh, std::string_view readed, std::string_view block, std::string_view name, USET_SV& mandatory_names, USET_SV& optional_names)
		{
			nh = mandatory_names.extract(readed);
			// If extracted node is empty, it not a mandatory keyword ...
			if (nh.empty())
			{
				// ... then, try from optional keywords ...
				nh = optional_names.extract(readed);

				// ... finally, check for error and other words
				if (nh.empty())
				{
					// Check if exist at least one mandatory keyword to read
					if (!mandatory_names.empty())
					{
						Log::SetWarning(Log::Warning::UNDEFINED_PARAMETERS, block, GetCurrentLine(input), name);
						return NODE_EXTRACTION_STATUS::FALSE;
					}
					return NODE_EXTRACTION_STATUS::BREAK;
				}
			}

			return NODE_EXTRACTION_STATUS::NONE;
		}

		inline unsigned int Try2GetObjectID(std::ifstream& input, std::string& readed)
		{
			try
			{
				input >> readed;
				return std::stoul(readed);
			}
			catch (const std::exception&)
			{
				//TODO: melhorar exception handling
				std::cout << "Invalid ID number definition at line " << GetCurrentLine(input);
				return 0;
			}
		}

		/*======================*
		 *  Template functions  *
		 *======================*/

		template<typename T>
		inline T ReadVariable(std::ifstream& input)
		{
			T variable;
			input >> variable;
			return variable;
		}

		template<typename container>
		inline std::string_view ExtractNodeValue(container& c, std::string_view readed)
		{
			auto nh = c.extract(readed);
			return nh.empty() ? "\0" : nh.value();
		}

		template<typename container>
		void RemoveDuplicates(container& c, std::string const& name)
		{
			//Size before repeated elements excluded
			size_t before = c.size();

			//Sorting and excluding repeated objects
			std::sort(c.begin(), c.end());
			c.erase(std::unique(c.begin(), c.end()), c.end());

			//Removed objects
			size_t removed = before - c.size();
			if (removed > 0)
				Log::SetWarning(Log::Warning::REMOVED_OBJECTS, name);
			c.shrink_to_fit();
		}
				
		template<typename container, size_t size>
		container ReadFixedContainer(std::ifstream& input)
		{
			try
			{
				container c;
				for (size_t i = 0; i < size; ++i)
					input >> c[i];
				return c;
			}
			catch (const std::exception&)
			{
				//TODO: melhorar exception handling
				std::cout << "Invalid input at line " << GetCurrentLine(input);
				std::exit(EXIT_FAILURE);
			}
		}
		

		Table&& ReadTable(std::ifstream& input, size_t lines)
		{
			auto table = new Table();

			std::string time;
			size_t cur_line = 0;
			do
			{
				// Check the first number (TIME)
				if (!(input >> time) || !std::isdigit(time[0]))
				{
					AuxFunctions::Reading::BackLastWord(input, std::string_view(time));
					break;
				}

				// Pre-allocate next line with current time... 
				table->SetLine(std::stod(time), 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
				// ... and read values for all DoFs
				input >> table->table[cur_line][1] >> table->table[cur_line][2] >> table->table[cur_line][3]
					>> table->table[cur_line][4] >> table->table[cur_line][5] >> table->table[cur_line][6];

				++cur_line;

			} while (input.good());

			return std::move(*table);
		}

		std::string ReadDelimitedString(std::ifstream& input, const std::array<char, 2>& delimeters)
		{
			// Buffer that will hold the equation
			std::stringbuf buf;
			char delimiter;

			// Read until initial angular bracket, ...
			input.get(buf, delimeters[0]);
			input >> delimiter;
			if (delimiter != delimeters[0])
				std::exit(EXIT_FAILURE);
			// ... clear whitspaces before FIRST DELIMITER from the buffer ...
			buf.swap(std::stringbuf(""));
			// ... read until the next angular bracket, ...
			input.get(buf, delimeters[1]);
			input >> delimiter;
			// ... then, set the equation
			return std::move(buf.str());
		}

	} /* namespace Reading */


	namespace Time
	{
	/// <summary>
	///		
	/// 	This namespace has only the a struct 'Timer'
	///		to measure execution time of a specific escope
	/// 
	/// </summary>
		
		using namespace std::literals::chrono_literals;

		struct Timer
		{
			std::chrono::time_point<std::chrono::steady_clock> start;
			std::chrono::duration<float> duration;

			Timer()
			{
				start = std::chrono::high_resolution_clock::now();
			}
			~Timer()
			{
				duration = std::chrono::high_resolution_clock::now() - start;
				
				float ms = duration.count() * 1000.0f;
				std::cout << "Timer took: " << ms << "ms" << "\n";
			}
		};

	}// End of namespace "Time"

}
