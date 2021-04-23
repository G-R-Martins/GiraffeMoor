#include "PCH.h"
#include "IO.h"
#include "TemplateReading.h"
#include "Log.h"


//Global objects
extern MooringModel mm;
extern GiraffeModel gm;

//Global variables
extern std::string name_input;
extern std::string folder_name;
extern std::string name; //with directory and extension
extern std::string version;

IO::IO()
	: cur_level(FirstLevelKeyword::None)
{}

IO::~IO()
{}

bool IO::ReadKeyword(FILE* f, fpos_t& pos, char* word)
{
	//Finish
	if (fscanf(f, "%s", word) == EOF)				cur_level = FirstLevelKeyword::EndOfFile;
	//Mandatory
	else if (!strcmp(word, "Environment"))			cur_level = FirstLevelKeyword::Environment;
	else if (!strcmp(word, "Keypoints"))			cur_level = FirstLevelKeyword::Keypoints;
	else if (!strcmp(word, "Lines"))				cur_level = FirstLevelKeyword::Lines;
	else if (!strcmp(word, "Vessels"))				cur_level = FirstLevelKeyword::Vessels;
	else if (!strcmp(word, "SegmentProperties"))	cur_level = FirstLevelKeyword::SegmentProperties;
	else if (!strcmp(word, "Solution"))				cur_level = FirstLevelKeyword::Solution;
	//Optional
	else if (!strcmp(word, "SegmentSets"))			cur_level = FirstLevelKeyword::SegmentSets;
	else if (!strcmp(word, "VesselDisplacements"))	cur_level = FirstLevelKeyword::VesselDisplacements;
	else if (!strcmp(word, "Platforms"))			cur_level = FirstLevelKeyword::Platforms;
	else if (!strcmp(word, "GiraffeConvergenceCriteria"))	cur_level = FirstLevelKeyword::GiraffeConvergenceCriteria;
	else if (!strcmp(word, "Monitors"))				cur_level = FirstLevelKeyword::Monitors;
	else if (!strcmp(word, "PostProcessing"))		cur_level = FirstLevelKeyword::PostProcessing;
	else if (!strcmp(word, "StiffnessMatrix"))		cur_level = FirstLevelKeyword::StiffnessMatrix;
	else if (!strcmp(word, "GiraffeSolver"))		cur_level = FirstLevelKeyword::GiraffeSolver;
	else if (!strcmp(word, "Constraints"))			cur_level = FirstLevelKeyword::Constraints;
	else if (!strcmp(word, "NodalForces"))			cur_level = FirstLevelKeyword::NodalForces;
	//Comment after 
	else if (word[0] == '/' && 
			 AuxFunctions::ReadComment(f, word))	cur_level = FirstLevelKeyword::CommentAfterBlock;
	//ERROR -> other word
	else											cur_level = FirstLevelKeyword::Error; //return false;
	

	//All ok while reading
	return true;
}

//Reads GiraffeMoor input file
bool IO::ReadFile()
{
	//Reading the input file name
	bool readOK = false;
	FILE* f = NULL;
	std::cout << " ____________________________________________________________ \n";
	std::cout << "|                                                            |\n";
	std::cout << "|                        GiraffeMoor                         |\n";
	std::cout << "|               University of Sao Paulo - Brazil             |\n";
	std::cout << "|                                                            |\n";
	std::cout << "|                                                 v. " << version << "  |\n";
	std::cout << "|____________________________________________________________|\n\n";

	while (!readOK)
	{
		if (__argc > 1)
			name_input = __argv[1];
		else
		{
			std::cout << "Enter the name of the input file: ";
			std::getline(std::cin, name_input);
		}

#if _DEBUG == 1
		folder_name = "../inputs/"; // folder with inputs in the project directory
#else
		folder_name = "./";	//folder in the same location of the executable
#endif

		folder_name += name_input + "/";
		name += folder_name + name_input + ".gmr";

		std::cout << "\n";
		//tries to read the same location of the executable file of Giraffe
		f = fopen(name.c_str(), "r");
		if (f == NULL)
		{
			folder_name = "C:/Users/Public/Documents/GiraffeMoor/";
			struct stat info;
			//checks if there is a folder called "GiraffeMoor" in this directory
			if (stat(folder_name.c_str(), &info) != 0)
				auto return_to_ignore = _mkdir(folder_name.c_str());
			name = folder_name + name_input + ".gmr";
			f = fopen(name.c_str(), "r");
			if (f == NULL)
				printf("Error reading the input file. Try again.\n");
			else
				readOK = true;
		}
		else
		{
			if (__argc > 1)
				std::cout << "Running file \"" << name_input << ".gmr\" . . .\n\n\n";
			readOK = true;
		}
	}

	char str[1000];
	fpos_t pos;		//variável que salva ponto do stream de leitura

	//Set with mandatory keywords to check if these blocks were defined
	std::unordered_set<std::string_view> mandatory_keywords({ "Environment", "Keypoints" , "Lines" , "Vessels" , "SegmentProperties" , "Solution" });

END: while (cur_level != FirstLevelKeyword::EndOfFile)
{
	while (ReadKeyword(f, pos, str))// && cur_level != FirstLevelKeyword::EndOfFile)
	{
		//Last valid keyword
		Log::getInstance().SetLastKeyword(str);

		switch (cur_level)
		{
		//First level only

			/*-+-+-+-+-+-+-+-+-+-+-+-+-+-+            Environment           +-+-+-+-+-+-+-+-+-+-+-+-+-+-*/
		case FirstLevelKeyword::Environment:
			if (!mm.environment.Read(f))
				return false;
			else
				mandatory_keywords.erase("Environment");
			break;

			/*-+-+-+-+-+-+-+-+-+-+-+-+-+-+             Solution             +-+-+-+-+-+-+-+-+-+-+-+-+-+-*/
		case FirstLevelKeyword::Solution:
			if (!mm.moorsolution.Read(f))
				return false;
			else
				mandatory_keywords.erase("Solution");
			break;

			/*-+-+-+-+-+-+-+-+-+-+-+-+-+-+           PostProcessing          +-+-+-+-+-+-+-+-+-+-+-+-+-+-*/
		case FirstLevelKeyword::PostProcessing:
			if (!mm.moorpost.Read(f))
				return false;
			break;

			/*-+-+-+-+-+-+-+-+-+-+-+-+-+-+           StiffnessMatrix          -+-+-+-+-+-+-+-+-+-+-+-+-+-*/
		case FirstLevelKeyword::StiffnessMatrix:
			mm.stiff_matrix = new StiffnessMatrix();
			if (!mm.stiff_matrix->Read(f))
				return false;
			break;

			/*-+-+-+-+-+-+-+-+-+-+-+-+-+-+           GiraffeSolver           +-+-+-+-+-+-+-+-+-+-+-+-+-+-*/
		case FirstLevelKeyword::GiraffeSolver:
			if (!gm.ReadGiraffeAddress(f))
				return false;
			break;

			/*-+-+-+-+-+-+-+-+-+-+-+-+-+-+              Monitors              +-+-+-+-+-+-+-+-+-+-+-+-+-+-*/
		case FirstLevelKeyword::Monitors:
			if (!gm.monitor.Read(f))
				return false;
			break;

			/*-+-+-+-+-+-+-+-+-+-+-+-+-+-+     GiraffeConvergenceCriteria     +-+-+-+-+-+-+-+-+-+-+-+-+-+-*/
		case FirstLevelKeyword::GiraffeConvergenceCriteria:
			if (!gm.conv_criteria.Read(f))
				return false;
			break;


		//Two levels

			/*-+-+-+-+-+-+-+-+-+-+-+-+-+-+              Keypoints             -+-+-+-+-+-+-+-+-+-+-+-+-+-*/
		case FirstLevelKeyword::Keypoints:
			if (!LoopReading::TryKeyword(mm.keypoint_vector, std::unordered_set<std::string_view>({ "Keypoint" }), f, pos, str))
				return false;
			else
				mandatory_keywords.erase("Keypoints");
			break;

			/*-+-+-+-+-+-+-+-+-+-+-+-+-+-+               Vessels              +-+-+-+-+-+-+-+-+-+-+-+-+-+-*/
		case FirstLevelKeyword::Vessels:
			if (!LoopReading::TryKeyword(mm.vessel_vector, std::unordered_set<std::string_view>({ "Vessel" }), f, pos, str))
				return false;
			else
				mandatory_keywords.erase("Vessels");
			break;

			/*-+-+-+-+-+-+-+-+-+-+-+-+-+-+           SegmentProperty          +-+-+-+-+-+-+-+-+-+-+-+-+-+-*/
		case FirstLevelKeyword::SegmentProperties:
			if (!LoopReading::TryKeyword(mm.segment_property_vector, std::unordered_set<std::string_view>({ "SegmentProperty" }), f, pos, str))
				return false;
			else
				mandatory_keywords.erase("SegmentProperties");
			break;

			/*-+-+-+-+-+-+-+-+-+-+-+-+-+-+             NodalForces            +-+-+-+-+-+-+-+-+-+-+-+-+-+-*/
		case FirstLevelKeyword::NodalForces:
			if (!LoopReading::TryKeyword_UnorderedMultiple(mm.moorload_vector, std::unordered_set<std::string_view>({ "Node" }), f, pos, str))
				return false;
			break;

			/*-+-+-+-+-+-+-+-+-+-+-+-+-+-+         VesselDisplacements        +-+-+-+-+-+-+-+-+-+-+-+-+-+-*/
		case FirstLevelKeyword::VesselDisplacements:
			if (!LoopReading::TryKeyword_UnorderedMultiple(mm.vessel_disp_vector, std::unordered_set<std::string_view>({ "VesselDispID" }), f, pos, str))
				return false;
			break;

			/*-+-+-+-+-+-+-+-+-+-+-+-+-+-+             Constraints            +-+-+-+-+-+-+-+-+-+-+-+-+-+-*/
		case FirstLevelKeyword::Constraints:
			if (!mm.moor_constraint.Read(f))
				return false;
			break;

			/*-+-+-+-+-+-+-+-+-+-+-+-+-+-+             SegmentSets            +-+-+-+-+-+-+-+-+-+-+-+-+-+-*/
		case FirstLevelKeyword::SegmentSets:
			if (!LoopReading::TryKeyword(mm.segment_set_vector, std::unordered_set<std::string_view>({ "Set" }), f, pos, str))
				return false;
			break;


		//Three levels

			/*-+-+-+-+-+-+-+-+-+-+-+-+-+-+                Lines               +-+-+-+-+-+-+-+-+-+-+-+-+-+-*/
		case FirstLevelKeyword::Lines:
			if (!LoopReading::TryKeyword(mm.line_vector, std::unordered_set<std::string_view>({ "Line", "MooringLine", "Cable" }), f, pos, str))
				return false;
			else
				mandatory_keywords.erase("Lines");
			break;

			/*-+-+-+-+-+-+-+-+-+-+-+-+-+-+              Platforms             +-+-+-+-+-+-+-+-+-+-+-+-+-+-*/
		case FirstLevelKeyword::Platforms:
			if (!LoopReading::TryKeyword(mm.platform_vector, std::unordered_set<std::string_view>({ "Platform" }), f, pos, str))
				return false;
			break;


		//EOF
			/*-+-+-+-+-+-+-+-+-+-+-+-+-+-+             End Of File            +-+-+-+-+-+-+-+-+-+-+-+-+-+-*/
		case FirstLevelKeyword::EndOfFile:
			goto END;

		//Comment
			/*-+-+-+-+-+-+-+-+-+-+-+-+-+-+               Comment              +-+-+-+-+-+-+-+-+-+-+-+-+-+-*/
		case FirstLevelKeyword::CommentAfterBlock:
			break;

		//ERROR -> other word
			/*-+-+-+-+-+-+-+-+-+-+-+-+-+-+               Comment              +-+-+-+-+-+-+-+-+-+-+-+-+-+-*/
		case FirstLevelKeyword::Error:
			std::stringstream ss;
			ss << "   \"" << str << "\" is not a valid keyword.";
			Log::getInstance().AddWarning(ss);

			return false;
		}
	}
}
	fclose(f);

	//Checks if all mandatory blocks were defined
	if (!mandatory_keywords.empty())
	{
		//Initial message
		std::string w = std::string("\n   + ") + std::to_string(mandatory_keywords.size()) + " mandatory block(s) missed:\n";
		Log::getInstance().AddWarning(w);

		//Appends missed mandatory keywords
		for (const std::string_view& missed_block : mandatory_keywords)
		{
			//auto warning_keyword = missed_block + "\n";
			Log::getInstance().AddWarning(missed_block);
			Log::getInstance().AddWarning("\n");
		}
		return false;
	}

	mm.penetration = new Table[mm.line_vector.size()];

	
	//All ok while reading
	return true;
}


//Writes Giraffe model file
void IO::WriteGiraffeModelFile()
{
	FILE *f;
	std::string name_giraffe = folder_name + name_input + ".inp";
	f = fopen(name_giraffe.c_str(), "w");

	fprintf(f, "///////////////////////////////////////////////////////////////////////////\n");
	fprintf(f, "//                                                                       //\n");
	fprintf(f, "//   GIRAFFE input file generated automatically by GIRAFFEMoor v%s   //\n", version.c_str());
	fprintf(f, "//                                                                       //\n");
	fprintf(f, "///////////////////////////////////////////////////////////////////////////\n\n");

	fprintf(f, "\n/*Units:\n\tTime: s\n\tMass: kg\n\tLinear: m\n\tForce: N\n\tRotation: rad\n\tAzimuth: degree\n*/\n");

	fprintf(f, "\nSolutionSteps\t%d\n", ( int )gm.solution_vector.size());
	for (int i = 0; i < ( int )gm.solution_vector.size(); i++)
		gm.solution_vector[i]->WriteGiraffeModelFile(f);

	fprintf(f, "\nMonitor\n");
	gm.monitor.WriteGiraffeModelFile(f);

	fprintf(f, "\nPostFiles\n");
	gm.post.WriteGiraffeModelFile(f);


	/***********************
	 * SORT NODESET VECTOR *
	 ***********************/

	//Sorting and excluding repeated objects
	std::sort(gm.node_set_vector.begin(), gm.node_set_vector.end());


	fprintf(f, "\nNodeSets\t%d\n", ( int )gm.node_set_vector.size());
	for (int i = 0; i < ( int )gm.node_set_vector.size(); i++)
		gm.node_set_vector[i].WriteGiraffeModelFile(f);

	fprintf(f, "\nConstraints\t%d\n", ( int )gm.constraint_vector.size());
	for (int i = 0; i < ( int )gm.constraint_vector.size(); i++)
		gm.constraint_vector[i]->WriteGiraffeModelFile(f);

	fprintf(f, "\nContacts\t%d\n", ( int )gm.contact_vector.size());
	for (int i = 0; i < ( int )gm.contact_vector.size(); i++)
		gm.contact_vector[i]->WriteGiraffeModelFile(f);

	fprintf(f, "\nPipeSections\t%d\n", ( int )gm.pipe_section_vector.size());
	for (int i = 0; i < ( int )gm.pipe_section_vector.size(); i++)
		gm.pipe_section_vector[i].WriteGiraffeModelFile(f);

	fprintf(f, "\nRigidBodyData\t%d\n", ( int )gm.rbdata_vector.size());
	for (int i = 0; i < ( int )gm.rbdata_vector.size(); i++)
		gm.rbdata_vector[i].WriteGiraffeModelFile(f);

	fprintf(f, "\nEnvironment\n");
	gm.environment.WriteGiraffeModelFile(f);

	fprintf(f, "\nSurfaces\t%d\n", ( int )gm.oscillatory_vector.size());
	for (int i = 0; i < ( int )gm.oscillatory_vector.size(); i++)
		gm.oscillatory_vector[i].WriteGiraffeModelFile(f);

	fprintf(f, "\nSurfaceSets\t%d\n", ( int )gm.surface_set_vector.size());
	for (int i = 0; i < ( int )gm.surface_set_vector.size(); i++)
		gm.surface_set_vector[i].WriteGiraffeModelFile(f);

	fprintf(f, "\nConvergenceCriteria\n");
	gm.conv_criteria.WriteGiraffeModelFile(f);

	fprintf(f, "\nSpecialConstraints\t%d\n", ( int )gm.special_constraint_vector.size());
	for (int i = 0; i < ( int )gm.special_constraint_vector.size(); i++)
		gm.special_constraint_vector[i]->WriteGiraffeModelFile(f);

	fprintf(f, "\nCoordinateSystems\t%d\n", ( int )gm.cs_vector.size());
	for (int i = 0; i < ( int )gm.cs_vector.size(); i++)
		gm.cs_vector[i].WriteGiraffeModelFile(f);

	if (gm.load_vector.size() > 0)
	{
		fprintf(f, "\nLoads\t%d\n", ( int )gm.load_vector.size());
		for (int i = 0; i < ( int )gm.load_vector.size(); i++)
			gm.load_vector[i]->WriteGiraffeModelFile(f);
	}

	fprintf(f, "\nElements\t%d\n", ( int )gm.element_vector.size());
	for (int i = 0; i < ( int )gm.element_vector.size(); i++)
		gm.element_vector[i]->WriteGiraffeModelFile(f);

	fprintf(f, "\nNodes\t%d\n", ( int )gm.node_vector.size());
	for (int i = 0; i < ( int )gm.node_vector.size(); i++)
		gm.node_vector[i].WriteGiraffeModelFile(f);

	fprintf(f, "\nDisplacements\t%d\n", ( int )gm.displacement_vector.size());
	for (int i = 0; i < gm.displacement_vector.size(); i++)
		gm.displacement_vector[i]->WriteGiraffeModelFile(f);

	fclose(f);
}
