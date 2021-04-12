#include "PCH.h"
#include "Log.h"

std::string Log::error = "\n\n!!! ERROR !!!";
std::string Log::warning = "\n\n*** WARNINGS ***";
std::string Log::final_message = "";
std::string_view Log::last_keyword = "";

Log::Log()
	: existError(false), existWarning(false), contErrors(0), contWarnings(0)
	//error("\n\n***** ERROR *****\n"), warning("\n\n*** WARNINGS ***\n"), final_message("")
{}


/*****************
 * Add functions *
 *****************/

//Errors
void Log::AddError(const std::string_view& toAdd)
{
	Get().UpdateErrorCounter();
	Log::error += toAdd;
}
void Log::AddError(const std::stringstream& toAdd)
{
	Get().UpdateErrorCounter();
	Log::error += toAdd.str();
}
void Log::AddError(const std::string& toAdd)
{
	Get().UpdateErrorCounter();
	Log::error += toAdd;
}
void Log::AddError(const char* toAdd)
{
	Get().UpdateErrorCounter();
	Log::error += toAdd;
}
//Warnings
void Log::AddWarning(const std::string_view& toAdd)
{
	Get().UpdateWarningCounter();
	Log::warning += toAdd;
}
void Log::AddWarning(const std::stringstream& toAdd)
{
	Get().UpdateWarningCounter();
	Log::warning += toAdd.str();
}
void Log::AddWarning(const std::string& toAdd)
{
	Get().UpdateWarningCounter();
	Log::warning += toAdd;
}
void Log::AddWarning(const char* toAdd)
{
	Get().UpdateWarningCounter();
	Log::warning += toAdd;
}
//Final messages
void Log::AddFinalMessage(const std::string_view& toAdd)
{
	Log::final_message += toAdd;
}
void Log::AddFinalMessage(const std::stringstream& toAdd)
{
	Log::final_message += toAdd.str();
}
void Log::AddFinalMessage(const std::string& toAdd)
{
	Log::final_message += toAdd;
}
void Log::AddFinalMessage(const char* toAdd)
{
	Log::final_message += toAdd;
}

/* Update counters */
void Log::UpdateErrorCounter()
{
	if (!existError) existError = true;
	++contErrors;
}
void Log::UpdateWarningCounter()
{
	if (!existWarning) existWarning = true;
	++contWarnings;
}

/*********************************************
 * Functions to check if exist error/warning *
 *********************************************/

bool Log::Check4Errors()
{
	return existError;
}

bool Log::Check4Warnings()
{
	return existWarning;
}


/*********************************
 * Functions to print to console *
 *********************************/

void Log::ShowErrors()
{
	std::cout << Log::GetError() << "\n";
}

void Log::ShowWarnings()
{
	std::cout << Log::GetWarning() << "\n";
}

void Log::ShowFinalMessage()
{
	std::cout << Log::GetFinalMessage() << "\n";
}


/*****************
 * Get functions *
 *****************/

Log& Log::Get()
{
	static Log log_messages;
	return log_messages;
}

std::string& Log::GetError()
{
	return Log::error;
}

std::string& Log::GetWarning()
{
	return Log::warning;
}

std::string& Log::GetFinalMessage()
{
	return Log::final_message;
}


/***********************
 * Last keyword readed *
 ***********************/

void Log::SetLastKeyword(const std::string_view& key)
{
	last_keyword = key;
}

void Log::SetLastKeyword(const char* key)
{
	last_keyword = key;
}

std::string_view& Log::GetLastKeyword()
{
	return last_keyword;
}

