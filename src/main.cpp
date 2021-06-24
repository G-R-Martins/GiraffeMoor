//Pre-compiled headers
#include "PCH.h"
//Namespace with GiraffeMoor database headers and global functions (like 'Run')
#include "GiraffeMoor.h"


//Global objects (databases)
MooringModel mm;
GiraffeModel gm;

//Global variables
//std::string name_input;
////std::string folder_name;
//std::string name;	//with directory and extension
//std::string version("0.02.00");


int main(int argc, char* argv[])
{
	//Launch GiraffeMoor
	GiraffeMoor::Run();

	//Check for error and/or warning messages
	Log::CheckLogs();

	//Wait until enter key is pressed before close the console
	std::cin.get();
	return 0;
}
