#include "PCH.h"
#include "Log.h"


Log::Log()
	: existError(false), existWarning(false), contErrors(0), contWarnings(0),
	error("\n\n# # # # # #\n#  ERROR  #\n# # # # # #\n"), 
	warning("\n\n* * * * * * *\n*  WARNING  *\n* * * * * * *\n"), 
	final_message(""), last_keyword(""), last_valid_keyword("")
{}


/*****************
 * Add functions *
 *****************/

//Errors
void Log::AddError_Impl(const std::string_view& toAdd)
{
	UpdateErrorCounter();
	error += toAdd;
}
void Log::AddError_Impl(const std::stringstream& toAdd)
{
	UpdateErrorCounter();
	error += toAdd.str();
}
void Log::AddError_Impl(const std::string& toAdd)
{
	UpdateErrorCounter();
	error += toAdd;
}
void Log::AddError_Impl(const char* toAdd)
{
	UpdateErrorCounter();
	error += toAdd;
}
//Warnings
void Log::AddWarning_Impl(const std::string_view& toAdd)
{
	UpdateWarningCounter();
	warning += toAdd;
}
void Log::AddWarning_Impl(const std::stringstream& toAdd)
{
	UpdateWarningCounter();
	warning += toAdd.str();
}
void Log::AddWarning_Impl(const std::string& toAdd)
{
	UpdateWarningCounter();
	warning += toAdd;
}
void Log::AddWarning_Impl(const char* toAdd)
{
	UpdateWarningCounter();
	warning += toAdd;
}
//Final messages
void Log::AddFinalMessage_Impl(const std::string_view& toAdd)
{
	final_message += toAdd;
}
void Log::AddFinalMessage_Impl(const std::stringstream& toAdd)
{
	final_message += toAdd.str();
}
void Log::AddFinalMessage_Impl(const std::string& toAdd)
{
	final_message += toAdd;
}
void Log::AddFinalMessage_Impl(const char* toAdd)
{
	final_message += toAdd;
}


//Update counters
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


//Functions to check if exist error/warning
void Log::CheckLogs_Impl()
{
	//Same final message with or without errors
	AddFinalMessage_Impl("\nPress enter key to close GiraffeMoor.");

	if (Check4Errors_Impl())	ShowErrors_Impl();
	if (Check4Warnings_Impl())	ShowWarnings_Impl();

	//Print final message
	ShowFinalMessage_Impl();
}
bool Log::Check4Errors_Impl()
{
	return existError;
}
bool Log::Check4Warnings_Impl()
{
	return existWarning;
}


/*********************************
 * Functions to print to console *
 *********************************/

void Log::ShowErrors_Impl()
{
	std::cout << GetError() << "\n";
}
void Log::ShowWarnings_Impl()
{
	std::cout << GetWarning() << "\n";
}
void Log::ShowFinalMessage_Impl()
{
	std::cout << GetFinalMessage() << "\n";
}


/*****************
 * Get functions *
 *****************/

std::string& Log::GetError()
{
	return error;
}
std::string& Log::GetWarning()
{
	return warning;
}
std::string& Log::GetFinalMessage()
{
	return final_message;
}


/***********************
 * Last keyword readed *
 ***********************/

//Any keyword readed
void Log::SetLastKeyword_Impl(const std::string_view& key)
{
	last_keyword = key;
}
void Log::SetLastKeyword_Impl(const char* key)
{
	last_keyword = key;
}
std::string_view& Log::GetLastKeyword_Impl()
{
	return last_keyword;
}
//Valid keyword
void Log::SetLastValidKeyword_Impl(const std::string_view& key)
{
	last_valid_keyword = key;
}
void Log::SetLastValidKeyword_Impl(const char* key)
{
	last_valid_keyword = key;
}
std::string_view& Log::GetLastValidKeyword_Impl()
{
	return last_valid_keyword;
}

void Log::SetError_Impl(Log::Error error)
{
	std::string reading_error;

	switch (error)
	{
	case Error::Reading:
		reading_error = "\n   + Error at \"" + std::string(last_keyword) + "\" block";
		AddError_Impl(reading_error);
		AddFinalMessage_Impl("\n\nGiraffeMoor execution has failed during reading process.\nCheck your input file with the hint(s) from warning message(s).");
		break;
	case Error::FEM_Generation:
		AddError_Impl("\n   + Error generating FE model");
		AddFinalMessage_Impl("\n\nGiraffeMoor execution has failed during FE model construction. Please, check your input data.");
		break;
	case Error::InputModel:
		AddError_Impl("\n   + Error checking input data");
		AddFinalMessage_Impl("\n\nGiraffeMoor execution has failed during input model checking. Please, check your input data.");
		break;
	}
}

