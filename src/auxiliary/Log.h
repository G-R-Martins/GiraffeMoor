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

	enum class Warning
	{
		INVALID_ID = 0,
		INVALID_KEYWORD,
		INVALID_OPTION, 
		REMOVED_OBJECTS,
		UNDEFINED_PARAMETERS,
		UNDEFINED_MANDATORY_BLOCK,
		SOLVING_CATENARY
	};
	enum class Error
	{
		OPENING_FILE = -1,
		READING,
		FEM_GENERATION,
		CHECKING_MODEL
	};


	/* =========================================================================================
	                                    Static functions
	   ========================================================================================= */
	

	///
	/// SETTERS
	///
	
	static void SetWarning(Log::Warning type, std::string_view block, int line = 0,
		std::string_view name = "", int number = 0)			{ getInstance().SetWarning_Impl(type, block, line, name, number); };
	static void SetWarning(std::string_view msg)			{ getInstance().SetWarning_Impl(msg); }
	static void SetError(Log::Error error)					{ getInstance().SetError_Impl(error); }
	static void SetFinalMessage(std::string_view msg)		{ getInstance().SetFinalMessage_Impl(msg); }

	static void SetLastKeyword(std::string_view key)		{ return getInstance().SetLastKeyword_Impl(key); }
	static void SetLastValidKeyword(std::string_view key)	{ return getInstance().SetLastValidKeyword_Impl(key); }
	

	///
	/// GETTERS
	///
	
	static std::string_view GetLastKeyword()		{ return getInstance().GetLastKeyword_Impl(); }
	static std::string_view GetLastValidKeyword()	{ return getInstance().GetLastValidKeyword_Impl(); }
	
	
	///
	/// PRINTERS
	///
	

	//Functions to print to console
	static void ShowErrors()		{ return getInstance().ShowErrors_Impl(); }
	static void ShowWarnings()		{ return getInstance().ShowWarnings_Impl(); }
	static void ShowFinalMessage()	{ return getInstance().ShowFinalMessage_Impl(); }

	//Functions to check if exist error/warning 
	static void CheckLogs()			{ return getInstance().CheckLogs_Impl(); }
	static bool ExistErrors()		{ return getInstance().ExistErrors_Impl(); }
	static bool ExistWarnings()		{ return getInstance().ExistWarnings_Impl(); }

	//===========================================================================================================

private:

	int m_warning_ID;
	int m_tot_warnings;
	int m_error_ID;
	int m_tot_errors;

	std::stringstream m_error;
	std::stringstream m_warning;
	std::stringstream m_final_message;

	std::string m_last_keyword;
	std::string m_last_valid_keyword;


	/* =========================================================================================
					Implementations of corresponding static functions
	   ========================================================================================= */

	
	///
	/// SETTERS
	///
	
	void SetWarning_Impl(Log::Warning type, std::string_view block, /*mandatory arguments*/
		int line, std::string_view name, int number); /*optional arguments*/
	void SetWarning_Impl(std::string_view msg);
	void SetError_Impl(Log::Error error);
	void SetFinalMessage_Impl(std::string_view msg);

	// Keyword
	void SetLastKeyword_Impl(std::string_view key);
	void SetLastValidKeyword_Impl(std::string_view key);

	
	///
	/// GETTERS
	///
	
	std::string_view GetLastKeyword_Impl();
	std::string_view GetLastValidKeyword_Impl();


	///
	/// Print functions
	///
	
	void ShowErrors_Impl();
	void ShowWarnings_Impl();
	void ShowFinalMessage_Impl();


	/// 
	/// Other functions
	/// 
	
	void CheckLogs_Impl();
	bool ExistErrors_Impl();
	bool ExistWarnings_Impl();

};

