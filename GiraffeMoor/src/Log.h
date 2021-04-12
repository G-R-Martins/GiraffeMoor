#pragma once


class Log
{
private:
	bool existError;
	bool existWarning;

	unsigned int contErrors;
	unsigned int contWarnings;

	static std::string error;
	static std::string warning;
	static std::string final_message;

	static std::string_view last_keyword;

public:
	Log();
	~Log() = default;

	/*****************
	 * Add functions *
	 *****************/

	//Add error to the string (from a string view)
	static void AddError(const std::string_view& toAdd);
	//Add error to the string (from a string stream)
	static void AddError(const std::stringstream& toAdd);
	//Add error to the string (from a string)
	static void AddError(const std::string& toAdd);
	//Add error to the string (from a char array)
	static void AddError(const char* toAdd);

	//Add warning to the string 
	static void AddWarning(const std::string_view& toAdd);
	//Add warning to the string (from a string stream)
	static void AddWarning(const std::stringstream& toAdd);
	//Add warning to the string (from a string)
	static void AddWarning(const std::string& toAdd);
	//Add warning to the string (from a char array)
	static void AddWarning(const char* toAdd);
	
	//Add message to the string 
	static void AddFinalMessage(const std::string_view& toAdd);
	//Add message to the string (from a string stream)
	static void AddFinalMessage(const std::stringstream& toAdd);
	//Add message to the string (from a string)
	static void AddFinalMessage(const std::string& toAdd);
	//Add message to the string (from a char array)
	static void AddFinalMessage(const char* toAdd);
	
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

	//Return Singleton
	static Log& Log::Get();

	//Get the string with error message(s)
	static std::string& GetError();

	//Get the string with warning message(s)
	static std::string& GetWarning();

	//Get the string with final message
	static std::string& GetFinalMessage();
	

	/***********************
	 * Last keyword readed *
	 ***********************/

	static void SetLastKeyword(const std::string_view& key);
	static void SetLastKeyword(const char* key);
	static std::string_view& GetLastKeyword();


};

