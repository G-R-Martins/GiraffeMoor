#include "PCH.h"
#include "SegmentProperty.h"
#include "LoopReading.h"
#include "Log.h"


SegmentProperty::SegmentProperty()
	: m_number(0), m_rho( 0.0 ), m_diameter(0.0),
	m_diameter_inner(0.0), m_diameter_contact(0.0),
	m_EA(0.0), m_EI(0.0), m_GJ(0.0), m_GA(0.0),
	m_CDt(0.0), m_CDn(0.0), m_CAt(0.0), m_CAn(0.0),
	m_E(0.0), m_nu(0.0), m_SG(1.0), m_MBS(0.0),
	m_is_chain(false), m_is_truss(false), m_is_beam(false)
{}

SegmentProperty::~SegmentProperty()
{}



//Writes Giraffe file data
void SegmentProperty::WriteGiraffeModelFile(std::ostream& fout) const
{
	fout << "\tSec " << m_number <<
		"\tEA " << m_EA << "\tEI " << m_EI << 
		"\tGJ " << m_GJ << "\tGA " << m_GA <<
		"\tRho " << m_rho <<
		"\tCDt " << m_CDt << "\tCDn " << m_CDn <<
		"\tCAt " << m_CAt << "\tCAn " << m_CAn <<
		"\tDe " << m_diameter << "\tDi " << m_diameter_inner <<
		"\n";
}



void SegmentProperty::SetIDNumber(size_t number)
{
	this->m_number = number;
}
void SegmentProperty::SetMass(double rho)
{
	this->m_rho = rho;
}
void SegmentProperty::SetDiameter(double diameter)
{
	this->m_diameter = diameter;
}
void SegmentProperty::SetInnerDiameter(double diameter_inner)
{
	this->m_diameter_inner = diameter_inner;
}
void SegmentProperty::SetContactDiameter(double diameter_contact)
{
	this->m_diameter_contact = diameter_contact;
}
void SegmentProperty::SetEA(double EA)
{
	this->m_EA = EA;
}
void SegmentProperty::SetEI(double EI)
{
	this->m_EI = EI;
}
void SegmentProperty::SetGJ(double GJ)
{
	this->m_GJ = GJ;
}
void SegmentProperty::SetGA(double GA)
{
	this->m_GA = GA;
}
void SegmentProperty::SetCDt(double CDt)
{
	this->m_CDt = CDt;
}
void SegmentProperty::SetCDn(double CDn)
{
	this->m_CDn = CDn;
}
void SegmentProperty::SetCAt(double CAt)
{
	this->m_CAt = CAt;
}
void SegmentProperty::SetCAn(double CAn)
{
	this->m_CAn = CAn;
}
void SegmentProperty::SetYoungMod(double E)
{
	this->m_E = E;
}
void SegmentProperty::SetPoisson(double nu)
{
	this->m_nu = nu;
}
void SegmentProperty::SetSG(double SG)
{
	this->m_SG = SG;
}
void SegmentProperty::SetMBS(double MBS)
{
	this->m_MBS = MBS;
}

void SegmentProperty::SetChainOpt(bool is_chain)
{
	this->m_is_chain = is_chain;
	this->m_is_truss = is_chain; // a chain uses truss FEM model
}

void SegmentProperty::SetTrussOpt(bool is_truss)
{
	this->m_is_truss = is_truss;
}

void SegmentProperty::SetBeamOpt(bool is_beam)
{
	this->m_is_beam = is_beam;
}


bool SegmentProperty::SetWizardStudless(double d, std::string_view grade)
{
	//Set grade
	double c;
	if ( grade == "2" )			c = 1.37e4;
	else if ( grade == "3" )    c = 1.96e4;
	else if ( grade == "ORQ" )  c = 2.11e4;
	else if ( grade == "R4" )   c = 2.74e4;
	else	return false;

	//Set properties
	this->m_diameter = 1.8 * d;
	this->m_diameter_inner = 0.0;
	this->m_diameter_contact = 3.35 * d;
	this->m_rho = pow( 19.9 * d, 2.0) * 1000.0;
	this->m_EA = pow(0.854 * 100'000'000.0 * d, 2.0) * 1'000.0;
	this->m_EI = 0.0;
	this->m_CDn = 2.4;
	this->m_CDt = 1.15;
	this->m_CAn = 1.0;
	this->m_CAt = 0.5;
	this->m_MBS = c * pow(d, 2.0) * ( 44.0 - 80.0 * d ) * 1000.0;

	return true;
}
bool SegmentProperty::SetWizardStudlink(double d, std::string_view grade)
{
	//Set grade
	double c;
	if ( grade == "2" )			c = 1.37e4;
	else if ( grade == "3" )    c = 1.96e4;
	else if ( grade == "ORQ" )  c = 2.11e4;
	else if ( grade == "R4" )   c = 2.74e4;
	else	return false;

	//Set properties
	this->m_diameter = 1.89 * d;
	this->m_diameter_inner = 0.0;
	this->m_diameter_contact = 3.6 * d;
	this->m_rho = pow(21.9 * d, 2.0) * 1000.0;
	this->m_EA = pow(1.01 * 100'000'000.0 * d, 2.0) * 1'000.0;
	this->m_EI = 0.0;
	this->m_CDn = 2.6;
	this->m_CDt = 1.4;
	this->m_CAn = 1.0;
	this->m_CAt = 0.5;
	this->m_MBS = c * pow(d, 2.0) * ( 44.0 - 80.0 * d ) * 1000.0;

	return true;
}




////Reads input file
//bool SegmentProperty::Read(FILE* f)
//{
//	namespace auxRead = AuxFunctions::Read;
//
//	// Valid and invalid words to read for current type
//	std::unordered_set<std::string_view> keywords, invalid_keywords;
//	std::unordered_set<std::string_view>::iterator it;
//
//	//Warning messages
//	std::stringstream ss(" - \"Segment properties\" block:");
//
//	//Save keywords and values
//	char str[500];
//
//	//Reading position
//	fpos_t pos;
//
//	//Reading boolean
//	bool readOk = true;
//
//	//Map readed 'diameter_contact'
//	bool defined_diameter_cont = false;
//
//
//	fgetpos(f, &pos);
//	//If a word is readed, return an error
//	if (fscanf(f, "%s", str) == EOF || isalpha(str[0]))
//	{
//		ss << "\n   + Error reading segment property ID number\n";
//		Log::AddWarning(ss);
//		return false;
//	}
//	else
//		number = atoi(str);
//
//	// Chain (wizard)
//	if (fscanf(f, "%s", str) != EOF && !strcmp(str, "chain"))
//	{
//		isChain = true;
//		//Only MBS can be redefined
//		keywords = { "MBS" };
//		invalid_keywords = { "SpecificGravity", "SpecificMass", "Diameter" , "ContactDiameter",
//			"EA", "EI", "GA", "GJ", "CDt", "CDn", "CAt", "CAn" };
//
//		char chain_grade[100];
//		if (!fscanf(f, "%s %lf %s", str, &diameter, chain_grade) || !strcmp(str, "Diameter") // read keyword
//			|| !SetWizardStudless(diameter, std::string_view(chain_grade)))	// try set properties
//		{
//			ss << "Error defining chain properties for segment number " << number << "\n";
//			Log::AddWarning(ss);
//			return false;
//		}
//
//		//Defined by the wizard generator
//		defined_diameter_cont = true;
//	}
//	//Truss 
//	else if (!strcmp(str, "truss"))
//	{
//		isTruss = true;
//		//Exclude bending and torsional stiffness
//		keywords = { "SpecificGravity", "SpecificMass", "Diameter" , "ContactDiameter",
//			"EA", "CDt", "CDn", "CAt", "CAn", "MBS" };
//		invalid_keywords = { "EI", "GA", "GJ" };
//	}
//	//Beam
//	else if (!strcmp(str, "beam"))
//	{
//		isBeam = true;
//		//All keywords are possible for beam 
//		keywords = { "SpecificGravity", "SpecificMass", "Diameter" , "ContactDiameter",
//			"EA", "EI", "GA", "GJ", "CDt", "CDn", "CAt", "CAn", "MBS" };
//		invalid_keywords = { " " };
//	}
//	else
//	{
//		ss << "\n   + Error reading segment property type.\n";
//		Log::AddWarning(ss);
//		return false;
//	}
//
//
//	//Searches for comment block before parameters
//	auxRead::TryComment(f);
//
//	//Loop to read solution parameters
//	while (!fgetpos(f, &pos) && fscanf(f, "%s", str) != EOF)
//	{
//		it = keywords.find(std::string_view(str));
//		//Checl if is a kewywor
//		if (it != keywords.end())
//		{
//			if (*it == "SpecificGravity")
//			{
//				keywords.erase(*it);
//				//Read value
//				if (!fscanf(f, "%lf", &SG)) { SetWarning_InvalidValue(*it, ss); return false; }
//			}
//			else if (*it == "SpecificMass")
//			{
//				keywords.erase(*it);
//				//Read value
//				if (!fscanf(f, "%lf", &rho)) { SetWarning_InvalidValue(*it, ss); return false; }
//			}
//			else if (*it == "Diameter")
//			{
//				keywords.erase(*it);
//				//Read value
//				if (!fscanf(f, "%lf", &diameter)) { SetWarning_InvalidValue(*it, ss); return false; }
//			}
//			else if (*it == "InnerDiameter")
//			{
//				keywords.erase(*it);
//				//Read value
//				if (!fscanf(f, "%lf", &diameter_inner)) { SetWarning_InvalidValue(*it, ss); return false; }
//			}
//			else if (*it == "ContactDiameter")
//			{
//				keywords.erase(*it);
//				//Read value
//				if (!fscanf(f, "%lf", &diameter_contact)) { SetWarning_InvalidValue(*it, ss); return false; }
//				defined_diameter_cont = true;
//			}
//			else if (*it == "EA")
//			{
//				keywords.erase(*it);
//				//Read value
//				if (!fscanf(f, "%lf", &EA)) { SetWarning_InvalidValue(*it, ss); return false; }
//			}
//			else if (*it == "EI")
//			{
//				keywords.erase(*it);
//				//Read value
//				if (!fscanf(f, "%lf", &EI)) { SetWarning_InvalidValue(*it, ss); return false; }
//			}
//			else if (*it == "GA")
//			{
//				keywords.erase(*it);
//				//Read value
//				if (!fscanf(f, "%lf", &GA)) { SetWarning_InvalidValue(*it, ss); return false; }
//			}
//			else if (*it == "GJ")
//			{
//				keywords.erase(*it);
//				//Read value
//				if (!fscanf(f, "%lf", &GJ)) { SetWarning_InvalidValue(*it, ss); return false; }
//			}
//			else if (*it == "CDn")
//			{
//				keywords.erase(*it);
//				//Read value
//				if (!fscanf(f, "%lf", &CDn)) { SetWarning_InvalidValue(*it, ss); return false; }
//			}
//			else if (*it == "CDt")
//			{
//				keywords.erase(*it);
//				//Read value
//				if (!fscanf(f, "%lf", &CDt)) { SetWarning_InvalidValue(*it, ss); return false; }
//			}
//			else if (*it == "CAn")
//			{
//				keywords.erase(*it);
//				//Read value
//				if (!fscanf(f, "%lf", &CAn)) { SetWarning_InvalidValue(*it, ss); return false; }
//			}
//			else if (*it == "CAt")
//			{
//				keywords.erase(*it);
//				//Read value
//				if (!fscanf(f, "%lf", &CAt)) { SetWarning_InvalidValue(*it, ss); return false; }
//			}
//			else if (*it == "MBS")
//			{
//				keywords.erase(*it);
//				//Read value
//				if (!fscanf(f, "%lf", &MBS)) { SetWarning_InvalidValue(*it, ss); return false; }
//			}
//		}
//		// Check if is a comment
//		else if (str[0] == '/' && AuxFunctions::Read::Comment(f, str))
//			continue;
//		//Otherwise, back position and break the loop
//		else
//		{
//			fsetpos(f, &pos); break;
//		}
//	}
//
//
//	/*
//	 * Verifications
//	 */
//
//	 //Exclude optional keywords, if they exist in the set
//	for (std::string_view try2remove : std::unordered_set<std::string_view>{ "SpecificGravity",
//		 "InnerDiameter", "ContactDiameter", "MBS" })
//	{
//		it = keywords.find(try2remove);
//		if (it != keywords.end())	keywords.erase(it);
//	}
//
//	//Now, the set must be empty!
//	if (!keywords.empty())
//	{
//		ss << "\n   + It is missing " << keywords.size() << " keywords for the segment number " << number << ": \n";
//		for (std::string_view missing_keyword : keywords)		ss << "\n     - " << missing_keyword << "\n";
//	}
//
//	//If 'diameter_contact' was not defined, it must be set equal to 'diameter'
//	if (!defined_diameter_cont)
//		diameter_contact = diameter;
//
//
//	//All OK while reading
//	return true;
//}


//Overloaded operators
bool operator<(const SegmentProperty& obj1, const SegmentProperty& obj2)
{
	return obj1.m_number < obj2.m_number;
}
bool operator>(const SegmentProperty& obj1, const SegmentProperty& obj2)
{
	return !(obj1 < obj2);
}
bool operator==(const SegmentProperty& obj1, const SegmentProperty& obj2)
{
	return obj1.m_number == obj2.m_number;
}
bool operator!=(const SegmentProperty& obj1, const SegmentProperty& obj2)
{
	return !(obj1 == obj2);
}