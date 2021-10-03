#pragma once

//Typedefs
typedef std::string_view	SV;
typedef std::stringstream	SSTREAM;
typedef std::string			STR;
typedef std::vector<SV>		VEC_SV;
typedef std::vector<STR>	VEC_STR;

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
		Invalid_ID = -1,
		Removed_Obj,
		InputModel
	};
	//Enumeration class for errors
	enum class Error
	{
		Reading = -1,
		FEM_Generation,
		InputModel
	};


	///
	/// Static functions 
	///
	
	//Add error to the string
	static void AddError(const SV& toAdd) { return getInstance().AddError_Impl(toAdd); }
	static void AddError(const SSTREAM& toAdd) { return getInstance().AddError_Impl(toAdd); }
	static void AddError(const STR& toAdd) { return getInstance().AddError_Impl(toAdd); }
	static void AddError(const char* toAdd) { return getInstance().AddError_Impl(toAdd); }
	//Add warning to the string 
	static void AddWarning(const SV& toAdd) { return getInstance().AddWarning_Impl(toAdd); }
	static void AddWarning(const SSTREAM& toAdd) { return getInstance().AddWarning_Impl(toAdd); }
	static void AddWarning(const STR& toAdd) { return getInstance().AddWarning_Impl(toAdd); }
	static void AddWarning(const char* toAdd) { return getInstance().AddWarning_Impl(toAdd); }
	static void AddWarning(Log::Warning type, VEC_STR toAdd) { return getInstance().AddWarning_Impl(type, toAdd); }
	//Add message to the string 
	static void AddFinalMessage(const SV& toAdd) { return getInstance().AddFinalMessage_Impl(toAdd); }
	static void AddFinalMessage(const SSTREAM& toAdd) { return getInstance().AddFinalMessage_Impl(toAdd); }
	static void AddFinalMessage(const STR& toAdd) { return getInstance().AddFinalMessage_Impl(toAdd); }
	static void AddFinalMessage(const char* toAdd) { return getInstance().AddFinalMessage_Impl(toAdd); }
	
	//Functions to check if exist error/warning 
	static void CheckLogs() { return getInstance().CheckLogs_Impl(); }
	static bool Check4Errors() { return getInstance().Check4Errors_Impl(); }
	static bool Check4Warnings() { return getInstance().Check4Warnings_Impl(); }

	//Functions to print to console
	static void ShowErrors() { return getInstance().ShowErrors_Impl(); }
	static void ShowWarnings() { return getInstance().ShowWarnings_Impl(); }
	static void ShowFinalMessage() { return getInstance().ShowFinalMessage_Impl(); }


	//Last keyword readed
	///Any word
	static void SetLastKeyword(const SV& key) { return getInstance().SetLastKeyword_Impl(key); }
	static void SetLastKeyword(const char* key) { return getInstance().SetLastKeyword_Impl(key); }
	static SV& GetLastKeyword() { return getInstance().GetLastKeyword_Impl(); }
	///Valid keyword
	static void SetLastValidKeyword(const SV& key) { return getInstance().SetLastValidKeyword_Impl(key); }
	static void SetLastValidKeyword(const char* key) { return getInstance().SetLastValidKeyword_Impl(key); }
	static SV& GetLastValidKeyword() { return getInstance().GetLastValidKeyword_Impl(); }
	
	//Set error messages for each specific case
	static void SetError(Log::Error error) { getInstance().SetError_Impl(error); }
	static void SetError(Log::Error error, const STR& msg) { getInstance().SetError_Impl(error, msg); }

	//===========================================================================================================

private:

					/*+-+-+-+-+-+-+-+
					|               |
					|   Variables   |
					|               |
					+-+-+-+-+-+-+-+-*/

	bool existError, existWarning;
	unsigned int contErrors,  contWarnings;

	STR error, warning, final_message;
	SV last_keyword, last_valid_keyword;


					/*+-+-+-+-+-+-+-+
					|               |
					|   Variables   |
					|               |
					+-+-+-+-+-+-+-+-*/

	///				  
	/// Implementations of corresponding static functions
	/// 			  

	//Add error to the string
	void AddError_Impl(const SV& toAdd);
	void AddError_Impl(const SSTREAM& toAdd);
	void AddError_Impl(const STR& toAdd);
	void AddError_Impl(const char* toAdd);
	//Add warning to the string 
	void AddWarning_Impl(const SV& toAdd);
	void AddWarning_Impl(const SSTREAM& toAdd);
	void AddWarning_Impl(const STR& toAdd);
	void AddWarning_Impl(const char* toAdd);
	void AddWarning_Impl(Log::Warning type, VEC_STR toAdd);
	//Add message to the string 
	void AddFinalMessage_Impl(const SV& toAdd);
	void AddFinalMessage_Impl(const SSTREAM& toAdd);
	void AddFinalMessage_Impl(const STR& toAdd);
	void AddFinalMessage_Impl(const char* toAdd);

	//Functions to check if exist error/warning 
	void CheckLogs_Impl();
	bool Check4Errors_Impl();
	bool Check4Warnings_Impl();

	//Functions to print to console
	void ShowErrors_Impl();
	void ShowWarnings_Impl();
	void ShowFinalMessage_Impl();

	//Last keyword readed
	///Any word
	void SetLastKeyword_Impl(const SV& key);
	void SetLastKeyword_Impl(const char* key);
	SV& GetLastKeyword_Impl();
	///Valid keyword
	void SetLastValidKeyword_Impl(const SV& key);
	void SetLastValidKeyword_Impl(const char* key);
	SV& GetLastValidKeyword_Impl();

	//Set error messages for each specific case
	void SetError_Impl(Log::Error error);
	void SetError_Impl(Log::Error error, const STR& msg);


	/// 
	/// Other functions
	/// 

	//Get functions
	STR& GetError();
	STR& GetWarning();
	STR& GetFinalMessage();

	//Update counters
	void UpdateErrorCounter();
	void UpdateWarningCounter();

};

