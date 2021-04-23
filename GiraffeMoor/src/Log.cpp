#include "PCH.h"
#include "Log.h"


Log::Log()
	: existError(false), existWarning(false), contErrors(0), contWarnings(0),
	error("\n\n# # # # # #\n#  ERROR  #\n# # # # # #\n"), 
	warning("\n\n* * * * * * *\n*  WARNING  *\n* * * * * * *\n"), final_message(""), last_keyword("")
{}


/*****************
 * Add functions *
 *****************/

//Errors
void Log::AddError(const std::string_view& toAdd)
{
	getInstance().UpdateErrorCounter();
	getInstance().error += toAdd;
}
void Log::AddError(const std::stringstream& toAdd)
{
	getInstance().UpdateErrorCounter();
	getInstance().error += toAdd.str();
}
void Log::AddError(const std::string& toAdd)
{
	getInstance().UpdateErrorCounter();
	getInstance().error += toAdd;
}
void Log::AddError(const char* toAdd)
{
	getInstance().UpdateErrorCounter();
	getInstance().error += toAdd;
}
//Warnings
void Log::AddWarning(const std::string_view& toAdd)
{
	getInstance().UpdateWarningCounter();
	getInstance().warning += toAdd;
}
void Log::AddWarning(const std::stringstream& toAdd)
{
	getInstance().UpdateWarningCounter();
	getInstance().warning += toAdd.str();
}
void Log::AddWarning(const std::string& toAdd)
{
	getInstance().UpdateWarningCounter();
	getInstance().warning += toAdd;
}
void Log::AddWarning(const char* toAdd)
{
	getInstance().UpdateWarningCounter();
	getInstance().warning += toAdd;
}
//Final messages
void Log::AddFinalMessage(const std::string_view& toAdd)
{
	getInstance().final_message += toAdd;
}
void Log::AddFinalMessage(const std::stringstream& toAdd)
{
	getInstance().final_message += toAdd.str();
}
void Log::AddFinalMessage(const std::string& toAdd)
{
	getInstance().final_message += toAdd;
}
void Log::AddFinalMessage(const char* toAdd)
{
	getInstance().final_message += toAdd;
}

/* Update counters */
void Log::UpdateErrorCounter()
{
	if (!getInstance().existError) getInstance().existError = true;
	++getInstance().contErrors;
}
void Log::UpdateWarningCounter()
{
	if (!getInstance().existWarning) getInstance().existWarning = true;
	++getInstance().contWarnings;
}

/*********************************************
 * Functions to check if exist error/warning *
 *********************************************/

bool Log::Check4Errors()
{
	return getInstance().existError;
}

bool Log::Check4Warnings()
{
	return getInstance().existWarning;
}


/*********************************
 * Functions to print to console *
 *********************************/

void Log::ShowErrors()
{
	std::cout << getInstance().GetError() << "\n";
}

void Log::ShowWarnings()
{
	std::cout << getInstance().GetWarning() << "\n";
}

void Log::ShowFinalMessage()
{
	std::cout << getInstance().GetFinalMessage() << "\n";
}


/*****************
 * get functions *
 *****************/

std::string& Log::GetError()
{
	return getInstance().error;
}

std::string& Log::GetWarning()
{
	return getInstance().warning;
}

std::string& Log::GetFinalMessage()
{
	return getInstance().final_message;
}


/***********************
 * Last keyword readed *
 ***********************/

void Log::SetLastKeyword(const std::string_view& key)
{
	getInstance().last_keyword = key;
}

void Log::SetLastKeyword(const char* key)
{
	getInstance().last_keyword = key;
}

std::string_view& Log::GetLastKeyword()
{
	return getInstance().last_keyword;
}

