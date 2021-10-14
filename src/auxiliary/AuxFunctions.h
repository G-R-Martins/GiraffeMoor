#pragma once
#include "Log.h"


typedef std::unordered_set<std::string_view> USET_SV;
typedef std::unordered_set<std::string> USET_STR;
typedef std::unordered_set<std::string_view>::iterator IT_USET_SV;
typedef std::pair<bool, std::string_view> PAIR_BOOL_SV;
typedef std::unordered_map<std::string_view, std::function<bool(std::string& readed)>> MAP_FUNC;


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



		static USET_SV s_mandatory_keywords = { "Environment",
			"Keypoints", "Lines", "Vessels", "SegmentProperties", "Solution" };

		static USET_SV s_optional_keywords = { "SegmentSets",
			"VesselDisplacements", "Platforms", "GiraffeConvergenceCriteria",
			"Monitors", "PostProcessing", "StiffnessMatrix", "GiraffeSolver",
			"Constraints", "NodalForces", "DisplacementFields" };


		/*=========================*
		 *  Function declarations  *
		 *=========================*/

		// Check if the current word is part of a comment and read next word
		static void TryCommentAndContinue(std::ifstream& input, std::string& readed);
		// Searches for at least one line/block of comment only read next word if found
		static bool TryComment(std::ifstream& input, std::string& readed);

		static bool ReadBlockComment(std::ifstream& input, std::string& readed);
		static bool ReadLineComment(std::ifstream& input, std::string& readed);
		static bool CheckComment(std::ifstream& input, std::string& readed);

		static bool UniqueSubKeywords(std::ifstream& input, std::string& readed, MAP_FUNC& reading_func);
		
		int GetCurrentLine(std::ifstream& input);  // https://stackoverflow.com/questions/4813129/how-to-get-the-line-number-from-a-file-in-c
		static void BackLastWord(std::ifstream& input, std::string_view last_word);
		static void BackLastWord(std::ifstream& input, std::string last_word);


		/*=============*
		 *  Functions  *
		 *=============*/

		static void TryCommentAndContinue(std::ifstream& input, std::string& readed)
		{
			CheckComment(input, readed);

			do { input >> readed;
			} while (CheckComment(input, readed));
		}
		
		static bool TryComment(std::ifstream& input, std::string& readed)
		{
			if (!CheckComment(input, readed))
				return false;

			do { input >> readed; 
			} while (CheckComment(input, readed) && !input.eof());

			return true;
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

		inline bool CheckTopKeyword(std::string_view readed)
		{
			// Try a mandatory ...
			if (s_mandatory_keywords.find(readed) == s_mandatory_keywords.end() 
				&& // ... and an optional keyword ...
				(s_optional_keywords.find(readed) == s_optional_keywords.end()))
				// ... finally, we can infer it is not a valid key
				return false; 
			
			return true;
		}

		inline bool CheckUpperKeyword(const USET_SV& upper_keywords, const std::string& readed)
		{
			return upper_keywords.find(readed) != upper_keywords.end();
		}

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


		/*======================*
		 *  Template functions  *
		 *======================*/

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
			{
				Log::SetWarning(Log::Warning::REMOVED_OBJECTS, name);
			}
			c.shrink_to_fit();
		}

		template<typename container>
		bool Loop(std::ifstream& input, container& c, std::string& readed, MAP_FUNC& reading_func)
		{
			TryCommentAndContinue(input, readed);
			do {
				// Checks if is a valid keyword ...
				if (reading_func.count(readed) == 0)
					return false;
				// ... then, creates an object ...
				c.emplace_back();
				// ... and invokes the reading function (at IO class)
				if (!reading_func[readed](readed))
					return false; // ERROR while reading the object parameters

				// Searches for comment, if founded read next word ...
				TryComment(input, readed);
				// ... then if it is a first level keyword ...
				if (CheckTopKeyword(readed))
					return true; // ... MUST jump out of the function

			} while (true);
			
			return true;
		}

		// Althougth it is quite similar to "Loop" function, we MUST differ 
		// 'keywords' and 'upper_keywords' to check in the first if statement
		template<typename container>
		bool NestedLoop(std::ifstream& input, container& c, USET_SV& upper_keywords,
			std::string& readed, MAP_FUNC& reading_func)
		{
			TryCommentAndContinue(input, readed);
			do {
				// Checks if is a valid keyword ...
				if (reading_func.count(readed) == 0)
					return false;
				// ... then, creates an object ...
				c.emplace_back();
				// ... and invokes the reading function (at IO class)
				if (!reading_func[readed](readed))
					return false; // ERROR while reading the object parameters

				// Searches for comment, if founded read next word ...
				TryComment(input, readed);
				// ... then if it is a top OR upper level keyword ...
				if (CheckTopKeyword(readed) || CheckUpperKeyword(upper_keywords, readed))
					return true; // ... MUST jump out of the function

			} while (true);
			
			return true;
		}


		static bool UniqueSubKeywords(std::ifstream& input, std::string& readed, MAP_FUNC& reading_func)
		{
			TryCommentAndContinue(input, readed);
			do {
				// Extract node (handle) from set with names of the object parameters ...
				auto nh = reading_func.extract(readed);
				// ... check if is a valid keyword ...
				if (nh.empty())
					// ... if is not, check if all keywords were readed
					return reading_func.empty();
				
				// ... if is, invoke the reading function (at IO class)
				if (!nh.mapped()(readed))
					return false; // ERROR while reading the object parameters

				// Searches for comment, if founded read next word ...
				TryComment(input, readed);
				// ... then if it is a first level keyword ...
				if (CheckTopKeyword(readed))
					return true; // ... MUST jump out of the function

			} while (true);

			return true;
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

		template<typename T>
		inline T Try2GetObjectID(std::ifstream& input, std::string& readed)
		{
			try
			{
				input >> readed;
				return std::stoull(readed);
			}
			catch (const std::exception&)
			{
				//TODO: melhorar exception handling
				std::cout << "Invalid number for keypoint at line " << GetCurrentLine(input);
				return 0;
			}
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
