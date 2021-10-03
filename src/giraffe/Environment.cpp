#include "PCH.h"
#include "Environment.h"


Environment::Environment()
	: gravity(0.0), rhofluid(0.0), waterdepth(0.0)
{	bool_g.Clear();
	bool_current.Clear();
}

Environment::~Environment()
{}

void Environment::WriteGiraffeModelFile(std::ostream& fout) const
{
	fout << "\tGravityData\tG " << 0.0 << " " << 0.0 << " " << -gravity << " " << bool_g <<
		"\tOceanData\tRhoFluid " << rhofluid << "\tSurfacePosition " << 0.0 << " " << 0.0 << " " << 0.0 <<
		"\n\tSeaCurrent\tN " << seacurrent_vector.size() << " " << bool_current;
	for (const SeaCurrent& sc : GetSeaCurrentVec())
	{
		fout << "\t\tDepth " << sc.GetDepth() <<
			"\tSpeed " << sc.GetSpeed() << 
			"\tAngle " << sc.GetAzimuth() << 
			"\n";
	}
}

void Environment::SetGravity(double g)
{ this->gravity = g; }

void Environment::SetRhoFluid(double rho)
{ this->rhofluid = rho; }

void Environment::SetWaterDepth(double wd)
{ this->waterdepth = wd; }

void Environment::SetGravityBooltable(const BoolTable & bool_grav)
{ this->bool_g = bool_grav; }

void Environment::SetSeaCurrentBooltable(const BoolTable & bool_current)
{ this->bool_current = bool_current; }

void Environment::SetSeaCurrentVec(const std::vector<SeaCurrent>& current_vec)
{ this->seacurrent_vector = current_vec; }

double Environment::GetGravity() const
{ return this->gravity; }

double Environment::GetRhoFluid() const
{ return this->rhofluid; }

double Environment::GetWaterDepth() const
{ return this->waterdepth; }

BoolTable const& Environment::GetGravityBooltable() const
{ return this->bool_g; }
BoolTable& Environment::GetGravityBooltable()
{ return this->bool_g; }

BoolTable const& Environment::GetSeaCurrentBooltable() const
{ return this->bool_current; }
BoolTable& Environment::GetSeaCurrentBooltable() 
{ return this->bool_current; }

std::vector<SeaCurrent> const& Environment::GetSeaCurrentVec() const
{ return this->seacurrent_vector; }
std::vector<SeaCurrent>& Environment::GetSeaCurrentVec()
{ return this->seacurrent_vector; }
