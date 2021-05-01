#include "PCH.h"
#include "MoorEnvironment.h"
#include "Log.h"

double MoorEnvironment::gravity;


MoorEnvironment::MoorEnvironment()
	: /*gravity(0.0), */ rhofluid(0.0), waterdepth(0.0), 
	seacurrent_exist(false), const_seacurrent(true)
{
	seacurrent_vector.reserve(10);
}

MoorEnvironment::~MoorEnvironment()
{}


bool MoorEnvironment::Read(FILE *f)
{
	char str[1000];			//salva palavras-chave lidas e valores lidos
	fpos_t pos;				//variável que salva ponto do stream de leitura
	bool readOk = true;


	//Warning messages
	std::string ss(" -\"Environment\" block:");
	
	//Environment general data
	if (fscanf(f, "%s %lf", str, &MoorEnvironment::gravity) && readOk && strcmp(str, "Gravity"))
		readOk = false;
	if (fscanf(f, "%s %lf", str, &rhofluid) && readOk && strcmp(str, "RhoFluid"))
		readOk = false;
	if (fscanf(f, "%s %lf", str, &waterdepth) && readOk && strcmp(str, "WaterDepth"))
		readOk = false;
	
	//Checks if there is an error
	if (!readOk)
	{
		ss += "\n   + Error reading general environment data.";
		Log::AddWarning(ss);
		return false;
	}

	//Reads seabed
	if (fscanf(f, "%s", str) != EOF && !strcmp(str, "Seabed"))
	{
		if (fscanf(f, "%s", str) && !strcmp(str, "flat"))
			seabed.flatseabed = true;
		//Check if there is a word after "Seabed", not a number
		else if (isalpha(str[0]))
			seabed.flatseabed = false;
		else
		{
			ss += "\n   + Error reading seabed data.";
			Log::AddWarning(ss);
			return false;
		}
		
		//Reads seabed data
		if (!seabed.Read(f))
		{
			ss += "\n   + Error reading seabed data.";
			Log::AddWarning(ss);
			return false;
		}
		readOk = false;
	}
	else //ERROR
		return false;
	

	
	//Try to read sea current 
	fgetpos(f, &pos);	//Salva a posição (stream) do início da leitura
	if (fscanf(f, "%s", str))
		seacurrent_exist = !strcmp(str, "SeaCurrent") ? true : false;
	if (isdigit(str[0]))
	{
		ss += "\n   + Error reading se current data.";
		Log::AddWarning(ss);
		return false;
	}

	//with sea current
	if (seacurrent_exist)	
	{
		fgetpos(f, &pos);	//Salva a posição (stream) do início da leitura
		
		bool flag_continue = true;
		
		//Check for error
		if (fscanf(f, "%s", str) == EOF || strcmp(str, "Depth"))
		{
			ss += "\n   + Error reading sea current data.";
			Log::AddWarning(ss);
			return false;
		}

		while (!strcmp(str, "Depth") && flag_continue && seacurrent_exist)
		{
			fsetpos(f, &pos);									//Sets stream to the position for reading a line of sea current information
			seacurrent_vector.emplace_back(SeaCurrent());		//Inserts in the vector
			if (!seacurrent_vector.back().Read(f))				//Reading and writing on last insertion in the vector
			{
				ss += "\n   +Error reading sea current data.";
				return false;
			}
			fgetpos(f, &pos);	//Salva a posição (stream) do início da leitura
			flag_continue = (fscanf(f, "%s", str) != EOF) ? true : false;
		}
	}
	//No sea current
	else
	{
		//seacurrent_vector.push_back(SeaCurrent());
		seacurrent_vector.emplace_back(SeaCurrent());
		seacurrent_vector[0].azimuth = 0;
		seacurrent_vector[0].depth = 0;
		seacurrent_vector[0].speed = 0;

		//seacurrent_vector.push_back(SeaCurrent());
		seacurrent_vector.emplace_back(SeaCurrent());
		seacurrent_vector[1].azimuth = 0;
		seacurrent_vector[1].depth = waterdepth;
		seacurrent_vector[1].speed = 0;
	}
	fsetpos(f, &pos);


	//All OK while reading
	return true;
}


