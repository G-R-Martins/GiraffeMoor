//Pre-compiled headers
#include "PCH.h"
//Databases
#include "GiraffeModel.h"
#include "MooringModel.h"
//Pure static class to manage input/output
#include "IO.h"
//Singletons
#include "Summary.h"
#include "Log.h"


//Global objects
MooringModel mm;
GiraffeModel gm;

//Global variables
std::string name_input;
std::string folder_name;
std::string name;	//with directory and extension
std::string version("0.01.32");

//Run Giraffe (if is in release mode)
void RunGiraffe();


int main(int argc, char* argv[])
{
	//Reading input data
	if (!IO::ReadFile())
		Log::SetError(Log::Error::Reading);
	else
	{
		//Creates SummaryFile (with header)
		Summary::CreateSumFile(folder_name + name_input, version);

		//Creates FEM model
		if (mm.GenerateGiraffeModel())
		{
			//Add description to summary file 
			Summary::Append2File();

			//GIRAFFE input file
			IO::WriteGiraffeModelFile();

#if _DEBUG == 0
			RunGiraffe(); 
#endif
		}
		else //ERROR
			Log::SetError(Log::Error::FEM_Generation);
	}
	
	//Check for error and/or warning messages
	Log::CheckLogs();
	
	//Wait until enter key is pressed before close the console
	std::cin.get();
	return 0;
}


//Run Giraffe if is in release mode
void RunGiraffe()
{
	if (gm.run_giraffe)
	{
		system("CLS");
		std::string GiraffeFile = "Giraffe.exe " + name_input;
		system(GiraffeFile.c_str());
	}
	else //only prints this message if Giraffe solver is not called
		Log::AddFinalMessage("\n\nGiraffeMoor execution has finished successfully!");
}