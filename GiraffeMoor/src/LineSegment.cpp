#include "PCH.h"
#include "LineSegment.h"
#include "Log.h"


LineSegment::LineSegment()
	: length(0.0), property(0), discretization(0), n_nodes(0), n_elements(0)
{}

LineSegment::~LineSegment()
{}

LineSegment& LineSegment::operator=(LineSegment&& other) noexcept
{
	length = std::move(other.length);
	property = std::move(other.property);
	discretization = std::move(other.discretization);
	n_nodes = std::move(other.n_nodes);
	n_elements = std::move(other.n_elements);

	return *this;
}

LineSegment::LineSegment(LineSegment&& other) noexcept
	: length(std::move(other.length)), property(std::move(other.property)), 
	discretization(std::move(other.discretization)), n_nodes(std::move(other.n_nodes)), 
	n_elements(std::move(other.n_elements))
{}


//Reads input file
bool LineSegment::Read(FILE *f)
{
	char str[100];			//salva palavras-chave lidas e valores lidos
	


	if (fscanf(f, "%s", str) && isdigit(str[0]))
		length = atof(str);
	else
	{
		Log::getInstance().AddWarning("\n   + Error reading length of a segment");
		return false;
	}


	if (fscanf(f, "%s %d", str, &property) == EOF || strcmp(str, "Property"))
	{
		Log::getInstance().AddWarning("\n   + Error reading 'Property' keyword\n");
		return false;
	}

	if (fscanf(f, "%s %d", str, &discretization) == EOF || strcmp(str, "Discretization"))
	{
		Log::getInstance().AddWarning("\n   + Error reading 'Discretization' keyword");
		return false;
	}


	//All OK while reading
	return true;
}


