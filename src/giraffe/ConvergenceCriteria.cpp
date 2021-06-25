#include "PCH.h"
#include "ConvergenceCriteria.h"
#include "AuxFunctions.h"


ConvergenceCriteria::ConvergenceCriteria()
	: force_tol(1e-4), moment_tol(1e-4), force_min(1e0), moment_min(1e0), constraint_min(1e-7),
	disp_tol(1e-4), rot_tol(1e-4), lag_tol(1e-4), disp_min(1e-5), rot_min(1e-5), lag_min(1e-6), divergence_ref(1e15)
{}

ConvergenceCriteria::~ConvergenceCriteria()
{}

//Reads input file
bool ConvergenceCriteria::Read(FILE *f)
{
	char str[50];
	fpos_t pos;

	std::unordered_set<std::string_view> criteria{ "ForceTolerance", "MomentTolerance", "ForceMinimumReference", "MomentMinimumReference",
				"ConstraintMinimumReference", "DisplacementTolerance", "RotationTolerance", "LagrangeTolerance",
				"DisplacementMinimumReference", "RotationMinimumReference", "LagrangeMinimumReference", "DivergenceReference" };

	std::unordered_set<std::string_view>::iterator it;


	while (!fgetpos(f, &pos) && fscanf(f, "%s", str) != EOF)
	{
		it = criteria.find(std::string_view(str));
		if (it != criteria.end())
		{
			if (fscanf(f, "%s", str) != EOF && isdigit(str[0]) && 
				*it == "ForceTolerance")
				force_tol = atof(str);
			else if (*it == "MomentTolerance")					moment_tol = atof(str);
			else if (*it == "ForceMinimumReference")			force_min = atof(str);
			else if (*it == "MomentMinimumReference")			moment_min = atof(str);
			else if (*it == "ConstraintMinimumReference")		constraint_min = atof(str);
			else if (*it == "DisplacementTolerance")			disp_tol = atof(str);
			else if (*it == "RotationTolerance")				rot_tol = atof(str);
			else if (*it == "LagrangeTolerance")				lag_tol = atof(str);
			else if (*it == "DisplacementMinimumReference")		disp_min = atof(str);
			else if (*it == "RotationMinimumReference")			rot_min = atof(str);
			else if (*it == "LagrangeMinimumReference")			lag_min = atof(str);
			else if (*it == "DivergenceReference")				divergence_ref = atof(str);
		}
		else if (str[0] == '/' && AuxFunctions::Read::Comment(f, str))
			continue;
		//Other word -> backs position go to IO class
		else
		{
			fsetpos(f, &pos);
			return true;
		}
	}

	return true;
}

void ConvergenceCriteria::WriteGiraffeModelFile(std::ostream& fout) const
{

	fout << std::setprecision(6) <<
		"\tForceTolerance " << force_tol <<
		"\n\tMomentTolerance " << moment_tol <<
		"\n\tForceMinimumReference " << force_min <<
		"\n\tMomentMinimumReference " << moment_min <<
		"\n\tConstraintMinimumReference " << constraint_min <<
		"\n\tDisplacementTolerance " << disp_tol <<
		"\n\tRotationTolerance " << rot_tol <<
		"\n\tLagrangeTolerance " << lag_tol <<
		"\n\tDisplacementMinimumReference " << disp_min <<
		"\n\tRotationMinimumReference " << rot_min <<
		"\n\tLagrangeMinimumReference " << lag_min <<
		"\n\tDivergenceReference " << divergence_ref <<
		"\n";
}
