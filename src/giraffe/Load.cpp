#include "PCH.h"
#include "Load.h"

Load::Load()
	: number(0), CS(1), isMathCode(false), extFile(false)
{}

Load::~Load()
{}


//Set functions
void Load::SetNumber(unsigned int ID)
{ this->number = ID; }
void Load::SetCoordinateSystem(unsigned int CS)
{ this->CS = CS; }
void Load::DefineMathCodeOption()
{ this->isMathCode = true; }
void Load::DefineExternalFileOption()
{ this->extFile = true; }

//Get functions
unsigned int Load::GetNumber()
{ return this->number; }
unsigned int Load::GetCoordinateSystem()
{ return this->CS; }
bool Load::CheckIfIsMathCode()
{ return this->isMathCode; }
bool Load::CheckIfIsExternalFile()
{ return this->extFile; }


