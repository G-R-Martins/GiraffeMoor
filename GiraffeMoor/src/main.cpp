#include "PCH.h"
//Databases
#include "GiraffeModel.h"
#include "MooringModel.h"
//Input/Output
#include "IO.h"
#include "Summary.h"
//Static 'Log' member
#include "Log.h"


//Global objects
MooringModel mm;
GiraffeModel gm;
IO io;


//Global variables
std::string name_input;
std::string folder_name;
std::string name;	//with directory and extension
std::string version("0.1.30");


int main(int argc, char* argv[])
{
	//Reading input data
	if (!io.ReadFile())
	{
		std::string reading_error = "\n   + Error at \"" + std::string(Log::getInstance().GetLastKeyword()) + "\" block.";
		Log::getInstance().AddError(reading_error);
		Log::getInstance().AddFinalMessage("\n\nGiraffeMoor execution has failed during reading process.\nCheck your input file with the hint(s) from warning message(s).");
	}
	else
	{
		//Creates SummaryFile (with header)
		Summary::Get().CreateSumFile(folder_name + name_input, version);

		//Creates FEM model
		if (mm.GenerateGiraffeModel())
		{
			//Add description to summary file 
			Summary::Get().Append2File();

			//GIRAFFE input file
			io.WriteGiraffeModelFile();

			//End message
			if (!gm.run_giraffe)
				Log::getInstance().AddFinalMessage(std::string_view("\n\nGiraffeMoor execution has finished successfully!"));

			//Run Giraffe if is in release mode
#if _DEBUG == 0
			if (gm.run_giraffe)
			{
				system("CLS");
				std::string GiraffeFile = "Giraffe.exe " + name_input;
				system(GiraffeFile.c_str());
			}
#endif
		}
		else
		{
			Log::getInstance().AddError("\n   + Error generating FE model.");
			Log::getInstance().AddFinalMessage("\n\nGiraffeMoor execution has failed during FE model construction. Please, check your input data.");
		}
	}
	Log::getInstance().AddFinalMessage("\nPress enter key to close GiraffeMoor."); //Same with(out) errors
	
	
	//Check for error and/or warning messages
	if (Log::getInstance().Check4Errors())		Log::getInstance().ShowErrors();
	if (Log::getInstance().Check4Warnings())	Log::getInstance().ShowWarnings();

	//Print final message
	Log::getInstance().ShowFinalMessage();
	
	//PlaySound(TEXT("C:\\Windows\\Media\\Windows Notify System Generic.wav"), NULL, SND_SYNC);

	std::cin.get();
	return 0;
}