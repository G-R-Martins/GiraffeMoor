#pragma once


class Log
{
private:
	Log(); 
	/// <summary>
	///	
	/// This Singleton manages the log of the model,
	/// including the output to console.
	/// 
	/// </summary>	
	
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
	enum class Error
	{
		Reading = -1,
		FEM_Generation = -2,
		InputModel = -3
	};


	/********************
	 * Static functions *
	 ********************/

	//Add error to the string
	static void AddError(const std::string_view& toAdd) { return getInstance().AddError_Impl(toAdd); }
	static void AddError(const std::stringstream& toAdd) { return getInstance().AddError_Impl(toAdd); }
	static void AddError(const std::string& toAdd) { return getInstance().AddError_Impl(toAdd); }
	static void AddError(const char* toAdd) { return getInstance().AddError_Impl(toAdd); }
	//Add warning to the string 
	static void AddWarning(const std::string_view& toAdd) { return getInstance().AddWarning_Impl(toAdd); }
	static void AddWarning(const std::stringstream& toAdd) { return getInstance().AddWarning_Impl(toAdd); }
	static void AddWarning(const std::string& toAdd) { return getInstance().AddWarning_Impl(toAdd); }
	static void AddWarning(const char* toAdd) { return getInstance().AddWarning_Impl(toAdd); }
	//Add message to the string 
	static void AddFinalMessage(const std::string_view& toAdd) { return getInstance().AddFinalMessage_Impl(toAdd); }
	static void AddFinalMessage(const std::stringstream& toAdd) { return getInstance().AddFinalMessage_Impl(toAdd); }
	static void AddFinalMessage(const std::string& toAdd) { return getInstance().AddFinalMessage_Impl(toAdd); }
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
	static void SetLastKeyword(const std::string_view& key) { return getInstance().SetLastKeyword_Impl(key); }
	static void SetLastKeyword(const char* key) { return getInstance().SetLastKeyword_Impl(key); }
	static std::string_view& GetLastKeyword() { return getInstance().GetLastKeyword_Impl(); }
	///Valid keyword
	static void SetLastValidKeyword(const std::string_view& key) { return getInstance().SetLastValidKeyword_Impl(key); }
	static void SetLastValidKeyword(const char* key) { return getInstance().SetLastValidKeyword_Impl(key); }
	static std::string_view& GetLastValidKeyword() { return getInstance().GetLastValidKeyword_Impl(); }
	
	//Set error messages for each specific case
	static void SetError(Log::Error error) { getInstance().SetError_Impl(error); }

	//===========================================================================================================

private:

	/*************
	 * Variables *
	 *************/

	bool existError;
	bool existWarning;

	unsigned int contErrors;
	unsigned int contWarnings;

	std::string error;
	std::string warning;
	std::string final_message;

	std::string_view last_keyword;
	std::string_view last_valid_keyword;


	/*************
	 * Functions *
	 *************/

	///				  
	/// Implementations of corresponding static functions
	/// 			  

	//Add error to the string
	void AddError_Impl(const std::string_view& toAdd);
	void AddError_Impl(const std::stringstream& toAdd);
	void AddError_Impl(const std::string& toAdd);
	void AddError_Impl(const char* toAdd);
	//Add warning to the string 
	void AddWarning_Impl(const std::string_view& toAdd);
	void AddWarning_Impl(const std::stringstream& toAdd);
	void AddWarning_Impl(const std::string& toAdd);
	void AddWarning_Impl(const char* toAdd);
	//Add message to the string 
	void AddFinalMessage_Impl(const std::string_view& toAdd);
	void AddFinalMessage_Impl(const std::stringstream& toAdd);
	void AddFinalMessage_Impl(const std::string& toAdd);
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
	void SetLastKeyword_Impl(const std::string_view& key);
	void SetLastKeyword_Impl(const char* key);
	std::string_view& GetLastKeyword_Impl();
	///Valid keyword
	void SetLastValidKeyword_Impl(const std::string_view& key);
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

