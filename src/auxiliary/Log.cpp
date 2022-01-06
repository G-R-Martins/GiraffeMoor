#include "PCH.h"
#include "Log.h"
#include "AuxFunctions.h"


Log::Log()
	: m_warning_ID(0), m_tot_warnings(0), m_error_ID(0), m_tot_errors(0),
	m_error(""), m_warning(""), m_final_message(""), 
	m_last_keyword(""), m_last_valid_keyword("")
{}


/* =========================================================================================
    				Implementations of corresponding static functions
   ========================================================================================= */


/// 
/// SETTERS
/// 

void Log::SetWarning_Impl(Log::Warning type, std::string_view block, int line, std::string_view name, int number)
{
	switch (type)
	{
	case Warning::INVALID_ID:
		m_warning << "\n  " << ++m_warning_ID << ") " << block << ": Invalid ID number for \'" << name << "\' at line " << line;
		break;

	case Warning::INVALID_KEYWORD:
		m_warning << "\n  " << ++m_warning_ID << ") " << block << ": \'" << name << "\' is not a valid option. Please, check the manual for current supported options.";
		break;

	case Warning::INVALID_OPTION:
		m_warning << "\n  " << ++m_warning_ID << ") " << block << ": \'" << name << "\' (at line " << line <<
			") is not a valid keyword or it has been already defined.";
		break;
	
	case Warning::REMOVED_OBJECTS:
		m_warning << "\n  " << ++m_warning_ID << ") " << block << ": " << number << " repeated \'" << name << "\' removed";
		break;
	
	case Warning::UNDEFINED_PARAMETERS:
		m_warning << "\n  " << ++m_warning_ID << ") " << block << ": There is(are)" << number << " undefined parameter(s) for " << name;
		break;
	
	case Warning::UNDEFINED_MANDATORY_BLOCK:
		m_warning << "\n  " << ++m_warning_ID << ") " << block << ": " << number << " undefined mandatory block(s): ";
		//for (auto keyword : AuxFunctions::Reading::s_mandatory_keywords)
			//m_warning << "\n    - " << keyword;
		break;

	case Warning::SOLVING_CATENARY:
		m_warning << "\n  " << ++m_warning_ID << ") " << block << ": GiraffeMoor has failed to solve the catenary equations for line number " << line;
	}

	++m_tot_warnings;
}
void Log::SetWarning_Impl(std::string_view msg)
{
	m_warning << msg;
	++m_tot_warnings;
}

void Log::SetError_Impl(Log::Error error)
{
	switch (error)
	{
	case Error::OPENING_FILE:
		m_error << "Error trying to open the input file.";
		m_final_message << "\n\n" << R"(GiraffeMoor has failed to open the input file. 
Please, check the directory and the input file content.)";
		break;

	case Error::READING:
		m_error << "\n Error reading GiraffeMoor input file. \n Last valid block: \"" << m_last_valid_keyword << "\"";
		m_final_message << "\n\n" << R"(GiraffeMoor execution has failed during reading process.
Please, check your input file with the hint(s) from warning message(s).)";
		break;

	case Error::FEM_GENERATION:
		m_error << "\n Error generating Giraffe model.";
		m_final_message << "\n\n" << R"(GiraffeMoor execution has failed during FE model construction.
Please, check your input data.)";
		break;

	case Error::CHECKING_MODEL:
		m_error << "\n Error checking input data.";
		m_final_message << "\n\n" << R"(GiraffeMoor execution has failed during input model checking.
Please, check your input data.)";
		break;
	}
	
	++m_tot_errors;
}

void Log::SetFinalMessage_Impl(std::string_view msg)
{

}

void Log::SetLastKeyword_Impl(std::string_view key)
{
	m_last_keyword = key;
}
void Log::SetLastValidKeyword_Impl(std::string_view key)
{
	m_last_valid_keyword = key;
}


///
/// GETTERS
///


std::string_view Log::GetLastKeyword_Impl() 
{
	return m_last_keyword;
}
std::string_view Log::GetLastValidKeyword_Impl()
{
	return m_last_valid_keyword;
}



///
/// Print functions
///

void Log::ShowErrors_Impl()
{
	std::cout << "\n\n #========# \n";
	std::cout << " # ERRORS # \n";
	std::cout << " #========# \n";
	std::cout << m_error.str() << "\n";
}
void Log::ShowWarnings_Impl()
{
	std::cout << "\n\n #==========# \n";
	std::cout << " # WARNINGS # \n";
	std::cout << " #==========# \n";
	std::cout << m_warning.str() << "\n";
}
void Log::ShowFinalMessage_Impl()
{
	std::cout << m_final_message.str() << "\n";
}


//Functions to check if exist error/warning
void Log::CheckLogs_Impl()
{
	//Same final message with or without errors
	m_final_message << "\nPress enter key to close GiraffeMoor.";

	if (ExistErrors_Impl())		ShowErrors_Impl();
	if (ExistWarnings_Impl())	ShowWarnings_Impl();

	//Print final message
	ShowFinalMessage_Impl();
}
bool Log::ExistErrors_Impl()
{
	return m_tot_errors > 0;
}
bool Log::ExistWarnings_Impl()
{
	return m_tot_warnings > 0;
}
