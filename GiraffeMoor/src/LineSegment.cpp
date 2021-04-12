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
{
//		length = other.length;
//		property = other.property;
//		discretization = other.discretization;
//		n_nodes = other.n_nodes;
//		n_elements = other.n_elements;
}


//Reads input file
bool LineSegment::Read(FILE *f)
{
	char str[100];			//salva palavras-chave lidas e valores lidos
	
	if (fscanf(f, "%s %lf", str, &length) == EOF || strcmp(str, "Length"))
	{
		Log::AddWarning("\n   +Error reading 'Length' keyword.");
		return false;
	}

	if (fscanf(f, "%s %d", str, &property) == EOF || strcmp(str, "Property"))
	{
		Log::AddWarning("\n   +Error reading 'Property' keyword.\n");
		return false;
	}

	if (fscanf(f, "%s %d", str, &discretization) == EOF || strcmp(str, "Discretization"))
	{
		Log::AddWarning("\n   +Error reading 'Discretization' keyword.");
		return false;
	}


	//All OK while reading
	return true;
}


