#include "PCH.h"
#include "MathCode.h"
#include "Log.h"


constexpr int MAX_SIZE_LINE = 500;

MathCode::MathCode()
	: start_time(-1)
{}

MathCode::~MathCode()
{}

//Math GiraffeMoor and Giraffe times
void MathCode::SetStartTime(const double& start)
{
	start_time = start;
}

const double& MathCode::GetStartTime()
{
	return this->start_time;
}

//Setting start time ('t0') to apply math code
void MathCode::SetEquationInitialTime(const double& init)
{
	start_time = init;
	for (std::string& eq : equations)
	{
		//Erases '\n' from the end of a readed equation
		if (eq != "0") eq.pop_back();

		size_t rf = eq.rfind("t0");
		while (rf != std::string::npos)
		{
			std::string::iterator it = eq.begin();
			eq.replace(it + rf, it + rf + 2, std::to_string(start_time));
			rf = eq.rfind("t0");
		}
	}
}

//Reads input file
bool MathCode::Read(FILE *f)
{
	char str[MAX_SIZE_LINE];
	fpos_t pos;
	bool readOk = true;
	int i;
	
	do {
		//Saves current position after trying to read direction
		fgetpos(f, &pos);

		//Tries to read direction
		if (fscanf(f, "%s", str) != EOF && !strcmp(str, "X")) i = 0;
		else if (!strcmp(str, "Y")) i = 1;
		else if (!strcmp(str, "Z")) i = 2;
		else if (!strcmp(str, "ROTX")) i = 3;
		else if (!strcmp(str, "ROTY")) i = 4;
		else if (!strcmp(str, "ROTZ")) i = 5;
		//Can be other keyword
		else
		{
			fsetpos(f, &pos);
			readOk = false;

			//Back to IO class and try to read other keyword
			return true; 
		}

		if (fgets(str, MAX_SIZE_LINE, f) != NULL)
			equations[i] = str;
		else
		{
			Log::AddWarning("\n   + Error reading MathCode line");
			return false;
		}

	} while (readOk);
	

	return true;
}

//Writes Giraffe file
std::ostream& operator<<(std::ostream& out, const MathCode& mc)
{
	out << "\t\t//X\n\t\tBegin\t" << mc.equations[0] << " End \n" <<
		"\t\t//Y\n\t\tBegin \t" << mc.equations[1] << " End \n" <<
		"\t\t//Z\n\t\tBegin \t" << mc.equations[2] << " End \n" <<
		"\t\t//ROTX\n\t\tBegin" << mc.equations[3] << " End \n" <<
		"\t\t//ROTY\n\t\tBegin" << mc.equations[4] << " End \n" <<
		"\t\t//ROTZ\n\t\tBegin" << mc.equations[5] << " End \n";


	return out;
}
std::ostream& operator<<(std::ostream& out, MathCode* mcPtr)
{
	out << "\t\t//X\n\t\tBegin\t" << mcPtr->equations[0] << " End \n" <<
		"\t\t//Y\n\t\tBegin \t" << mcPtr->equations[1] << " End \n" <<
		"\t\t//Z\n\t\tBegin \t" << mcPtr->equations[2] << " End \n" <<
		"\t\t//ROTX\n\t\tBegin\t" << mcPtr->equations[3] << " End \n" <<
		"\t\t//ROTY\n\t\tBegin\t" << mcPtr->equations[4] << " End \n" <<
		"\t\t//ROTZ\n\t\tBegin\t" << mcPtr->equations[5] << " End \n";


	return out;
}

