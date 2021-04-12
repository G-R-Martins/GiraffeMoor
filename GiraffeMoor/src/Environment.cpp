#include "PCH.h"
#include "Environment.h"


Environment::Environment()
	: gravity(0.0), rhofluid(0.0), waterdepth(0.0)
{
	seacurrent_vector.clear();
	bool_g.Clear();
	bool_current.Clear();
}

Environment::~Environment()
{
	seacurrent_vector.clear();
}

void Environment::WriteGiraffeModelFile(FILE *f)
{
//	fprintf(f, "\nEnvironment\n");
	fprintf(f, "\tGravityData\tG\t%.6e\t%.6e\t%.6e\t", 0.0, 0.0, -gravity);
	bool_g.Write(f);
	fprintf(f, "\tOceanData\tRhoFluid\t%.6e\tSurfacePosition\t%.6e\t%.6e\t%.6e\n\tSeaCurrent\tN\t%d\t",
		rhofluid, 0.0, 0.0, 0.0, (int)seacurrent_vector.size());
	bool_current.Write(f);
	for (int i = 0; i < seacurrent_vector.size(); i++)
	{
		fprintf(f, "\t\tDepth\t%lf\tSpeed\t%lf\tAngle\t%lf\n", seacurrent_vector[i].depth, seacurrent_vector[i].speed, seacurrent_vector[i].azimuth);
	}
}