#pragma once


class Log
{
/// <summary>
/// 
///		This Singleton manages the log of the model.
///		
///		Nowadays, there is only outputs to the console, 
///		but a log file is planned. 
///		
///		There are 3 different logs:
///			1. Warnings: 
///				- may be accompanied by errors or not
///			2. Errors
///				- throw an error message and finish the 
///				execution at the first error founded
///				- thus, in the next execution one can 
///				get another error
///			3. Final message
///				- some message is always printed
///				- if the Giraffe is called in the console
///				this message is shown after its execution is finished
///		 
/// </summary>
	
	//Singleton private constructor
	Log(); 

public:
	
	
	//Create/return Singleton instance
	static Log& getInstance()
	{
		static Log log_instance;
		return log_instance;
	}
	//Deleting copy and assignment 
	Log(const Log&) = delete;
	Log(Log&&) = delete;
	Log& operator=(const Log&) = delete;

	~Log() = default;


	//Enumeration class for errors
	enum class Warning
	{
		INVALID_ID = 0,
		INVALID_KEYWORD,
		REMOVED_OBJECTS,
		UNDEFINED_PARAMETERS,
		UNDEFINED_MANDATORY_BLOCK
	};
	//Enumeration class for errors
	enum class Error
	{
		READING = 0,
		FEM_GENERATION,
		CHECKING_MODEL
	};


	///
	/// Static functions 
	///
	
	static void AddWarning(Log::Warning type, std::vector<std::string> toAdd) { return getInstance().AddWarning_Impl(type, toAdd); }
	//Add message to the string 
	static void AddFinalMessage(std::string_view toAdd) { return getInstance().AddFinalMessage_Impl(toAdd); }
	static void AddFinalMessage(const std::string& toAdd) { return getInstance().AddFinalMessage_Impl(toAdd); }
	static void AddFinalMessage(const char* toAdd) { return getInstance().AddFinalMessage_Impl(toAdd); }
	
	//Functions to check if exist error/warning 
	static void CheckLogs() { return getInstance().CheckLogs_Impl(); }
	static bool CheckErrors() { return getInstance().CheckErrors_Impl(); }
	static bool CheckWarnings() { return getInstance().CheckWarnings_Impl(); }

	//Functions to print to console
	static void ShowErrors() { return getInstance().ShowErrors_Impl(); }
	static void ShowWarnings() { return getInstance().ShowWarnings_Impl(); }
	static void ShowFinalMessage() { return getInstance().ShowFinalMessage_Impl(); }


	//Last keyword readed
	///Any word
	static void SetLastKeyword(std::string_view key) { return getInstance().SetLastKeyword_Impl(key); }
	static void SetLastKeyword(const char* key) { return getInstance().SetLastKeyword_Impl(key); }
	static std::string_view GetLastKeyword() { return getInstance().GetLastKeyword_Impl(); }
	///Valid keyword
	static void SetLastValidKeyword(std::string_view key) { return getInstance().SetLastValidKeyword_Impl(key); }
	static void SetLastValidKeyword(const char* key) { return getInstance().SetLastValidKeyword_Impl(key); }
	static std::string_view GetLastValidKeyword() { return getInstance().GetLastValidKeyword_Impl(); }
	
	//Set error messages for each specific case
	static void SetError(Log::Error error) { getInstance().SetError_Impl(error); }
	static void SetError(Log::Error error, const std::string& msg) { getInstance().SetError_Impl(error, msg); }

	//===========================================================================================================

private:

					/*+-+-+-+-+-+-+-+
					|               |
					|   Variables   |
					|               |
					+-+-+-+-+-+-+-+-*/

	bool m_exist_error;
	bool m_exist_warning;
	int m_warning_ID;
	int m_tot_warnings;
	int m_tot_errors;

	std::stringstream m_error;
	std::stringstream m_warning;
	std::stringstream m_final_message;

	std::string m_last_keyword;
	std::string m_last_valid_keyword;

	///				  
	/// Implementations of corresponding static functions
	/// 			  

	void SetWarning_Impl(Log::Warning type, std::string_view block, int line, std::string_view name="", int number=0);
	void SetError_Impl(Log::Error error, const std::string& msg);

	//Add error to the string
	void AddError_Impl(std::string_view toAdd);
	void AddError_Impl(const std::stringstream& toAdd);
	void AddError_Impl(const std::string& toAdd);
	void AddError_Impl(const char* toAdd);
	//Add warning to the string 
	void AddWarning_Impl(std::string_view toAdd);
	void AddWarning_Impl(const std::stringstream& toAdd);
	void AddWarning_Impl(const std::string& toAdd);
	void AddWarning_Impl(const char* toAdd);
	void AddWarning_Impl(Log::Warning type, std::vector<std::string> toAdd);
	//Add message to the string 
	void AddFinalMessage_Impl(std::string_view toAdd);
	void AddFinalMessage_Impl(const std::stringstream& toAdd);
	void AddFinalMessage_Impl(const std::string& toAdd);
	void AddFinalMessage_Impl(const char* toAdd);

	//Functions to check if exist error/warning 
	void CheckLogs_Impl();
	bool CheckErrors_Impl();
	bool CheckWarnings_Impl();

	//Functions to print to console
	void ShowErrors_Impl();
	void ShowWarnings_Impl();
	void ShowFinalMessage_Impl();

	//Last keyword readed
	///Any word
	void SetLastKeyword_Impl(std::string_view key);
	void SetLastKeyword_Impl(const char* key);
	std::string_view& GetLastKeyword_Impl();
	///Valid keyword
	void SetLastValidKeyword_Impl(std::string_view key);
	void SetLastValidKeyword_Impl(const char* key);
	std::string_view& GetLastValidKeyword_Impl();

	//Set error messages for each specific case
	void SetError_Impl(Log::Error error);


	/// 
	/// Other functions
	/// 

	//Get functions
	std::string& GetError();
	std::string& GetWarning();
	std::string& GetFinalMessage();

	//Update counters
	void UpdateErrorCounter();
	void UpdateWarningCounter();

};

