#include "PCH.h"
#include "GiraffeModel.h"
#include "MooringModel.h"
#include "IO.h"
#include "Summary.h"
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
		std::string reading_error = "\n   +Error at \"" + std::string(Log::GetLastKeyword()) + "\" block.";
		Log::AddError(reading_error);
		Log::AddWarning("\n\n\nGiraffeMoor execution has failed during reading process.\nCheck your input file with the hint(s) from warning message(s).");
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
				Log::AddFinalMessage(std::string_view("\n\n\nGiraffeMoor execution has finished successfully!"));

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
			Log::AddError("\n   +Error generating FE model.");
			Log::AddFinalMessage("\n\n\nGiraffeMoor execution has failed during FE model construction.\nPlease, check your input data.");
		}
	}
	Log::AddFinalMessage("\n\nPress enter key to close it."); //Same with(out) errors
	
	
	//Check for error and/or warning messages
	if (Log::Get().Check4Errors())		Log::Get().ShowErrors();
	if (Log::Get().Check4Warnings())	Log::Get().ShowWarnings();

	//Print final message
	Log::Get().ShowFinalMessage();
	
	//PlaySound(TEXT("C:\\Windows\\Media\\Windows Notify System Generic.wav"), NULL, SND_SYNC);

	std::cin.get();
	return 0;
}