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
		//Reading input data
		if ( !IO::ReadFile() )
			Log::SetError(Log::Error::Reading);
		else if ( !IO::CheckModel() )
			Log::SetError(Log::Error::InputModel);
		else
		{
			//Creates SummaryFile (with header)
			Summary::CreateSumFile(IO::folder_name + IO::input_name, IO::version);

			//Creates FEM model
			if ( mm.GenerateGiraffeModel() )
			{
				//Add description to summary file 
				Summary::Append2File();

				//GIRAFFE input file
				IO::WriteGiraffeModelFile();

#ifdef NDEBUG
				RunGiraffe();
#endif
			}
			else //ERROR
				Log::SetError(Log::Error::FEM_Generation);
		}
	} //end funtion that run GiraffeMoor

	
	//Run Giraffe if is in release mode
	static void RunGiraffe()
	{
		if (gm.gir_solver.GetRunOption())
		{
			system("CLS");
			std::string GiraffeFile = "Giraffe.exe " + IO::input_name;
			system(GiraffeFile.c_str());
		}
		else //only prints this message if Giraffe solver is not called
			Log::AddFinalMessage("\n\nGiraffeMoor execution has finished successfully!");
	}
} //end GiraffeMoor namspace
