//Pre-compiled headers
#include "PCH.h"
//Namespace with GiraffeMoor database headers and global functions
#include "GiraffeMoor.h"


//Global objects (databases)
MooringModel mm;
GiraffeModel gm;


int main(int argc, char* argv[])
{
	//Launch GiraffeMoor
	GiraffeMoor::Run();

	//Check for error and/or warning messages
	Log::CheckLogs();


	std::cin.get();
	return 0;
}
