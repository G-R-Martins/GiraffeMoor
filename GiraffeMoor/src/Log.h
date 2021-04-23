#pragma once


class Log
{
private:
	bool existError;
	bool existWarning;

	unsigned int contErrors;
	unsigned int contWarnings;

	std::string error;
	std::string warning;
	std::string final_message;

	std::string_view last_keyword;


	//Private constructor to prevent copies
	Log();

public:
	// Deleting copy and assignment 
	Log(const Log&) = delete;
	Log& operator=(const Log&) = delete;

	//Static factory
	static Log& getInstance()
	{
		static Log log_instance;
		return log_instance;
	}

	~Log() = default;

	/*****************
	 * Add functions *
	 *****************/

	//Add error to the string (from a string view)
	void AddError(const std::string_view& toAdd);
	//Add error to the string (from a string stream)
	void AddError(const std::stringstream& toAdd);
	//Add error to the string (from a string)
	void AddError(const std::string& toAdd);
	//Add error to the string (from a char array)
	void AddError(const char* toAdd);

	//Add warning to the string 
	void AddWarning(const std::string_view& toAdd);
	//Add warning to the string (from a string stream)
	void AddWarning(const std::stringstream& toAdd);
	//Add warning to the string (from a string)
	void AddWarning(const std::string& toAdd);
	//Add warning to the string (from a char array)
	void AddWarning(const char* toAdd);
	
	//Add message to the string 
	void AddFinalMessage(const std::string_view& toAdd);
	//Add message to the string (from a string stream)
	void AddFinalMessage(const std::stringstream& toAdd);
	//Add message to the string (from a string)
	void AddFinalMessage(const std::string& toAdd);
	//Add message to the string (from a char array)
	void AddFinalMessage(const char* toAdd);
	
	/* Update counters */

	void UpdateErrorCounter();

	void UpdateWarningCounter();
	

	/*********************************************
	 * Functions to check if exist error/warning *
	 *********************************************/

	bool Check4Errors();

	bool Check4Warnings();

	/*********************************
	 * Functions to print to console *
	 *********************************/

	//Print warning message(s)
	void ShowErrors();

	//Print warning message(s)
	void ShowWarnings();
	
	//Print final message
	void ShowFinalMessage();


	/*****************
	 * Get functions *
	 *****************/

	//Get the string with error message(s)
	std::string& GetError();

	//Get the string with warning message(s)
	std::string& GetWarning();

	//Get the string with final message
	std::string& GetFinalMessage();
	

	/***********************
	 * Last keyword readed *
	 ***********************/

	void SetLastKeyword(const std::string_view& key);
	void SetLastKeyword(const char* key);
	std::string_view& GetLastKeyword();


};

