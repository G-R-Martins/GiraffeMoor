#pragma once
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
extern MooringModel mm;
extern GiraffeModel gm;


namespace GiraffeMoor
{
/// <summary>
///		
/// 	Namespace to organize the application execution,
///		I/O, and logging
///		
/// </summary>


	//Function header
	static void RunGiraffe();

	void Run()
	{
		if (!IO::ReadFile())
			Log::SetError(Log::Error::READING);
		else if (!IO::CheckModel())
			Log::SetError(Log::Error::CHECKING_MODEL);
		else
		{
			//Creates SummaryFile (with header)
			Summary::CreateSumFile(IO::folder_name + IO::input_name, IO::version);

			//Creates FEM model
			if (mm.GenerateGiraffeModel())
			{
				//Add description to summary file 
				Summary::Append2File();

				//GIRAFFE input file
				IO::WriteGiraffeModelFile();

#ifdef NDEBUG
				RunGiraffe();
#endif
			}
		}
	} //end funtion that run GiraffeMoor

	
	//Run Giraffe if is in release mode
	static void RunGiraffe()
	{
		if (gm.gir_solver.RunGiraffe())
		{
			system("CLS");
			std::string GiraffeFile = "Giraffe.exe " + IO::input_name;
			system(GiraffeFile.c_str());
		}
		else //only prints this message if Giraffe solver is not called
			Log::SetFinalMessage("\n\nGiraffeMoor execution has finished successfully!");
	}
} //end GiraffeMoor namspace
