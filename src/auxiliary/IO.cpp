#include "PCH.h"
#include "IO.h"
//Database headers
#include "MooringModel.h"
#include "GiraffeModel.h"
//Auxiliary namespace headers
#include "LoopReading.h"
#include "Log.h"


//It changes the folder to search for input file
#define _DEV_

//Global objects
extern MooringModel mm;
extern GiraffeModel gm;

//Static variable
FirstLevelKeyword IO::cur_level = FirstLevelKeyword::None;
std::string IO::folder_name, IO::input_name, IO::name, IO::version("0.03.00-a ");


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
	else if (!strcmp(word, "DisplacementFields"))	cur_level = FirstLevelKeyword::DisplacementFields;
	//Comment after 
	else if (word[0] == '/' && 
			 AuxFunctions::Read::Comment(f, word))	cur_level = FirstLevelKeyword::CommentAfterBlock;
	//ERROR -> other word
	else											cur_level = FirstLevelKeyword::Error; //return false;
	

	//All ok while reading
	return true;
}

//Reads GiraffeMoor input file
bool IO::ReadFile()
{

	//Reading the input file 
	bool readOK = false;
	FILE* f = NULL;
	std::cout << " ______________________________________________________________ \n";
	std::cout << "|                                                              |\n";
	std::cout << "|                        GiraffeMoor                           |\n";
	std::cout << "|               University of Sao Paulo - Brazil               |\n";
	std::cout << "|                                                              |\n";
	std::cout << "|                                                v. " << IO::version << " |\n";
	std::cout << "|______________________________________________________________|\n\n";
	
	while ( !readOK )
	{
		if ( __argc > 1 )
			input_name = __argv[1];
		else
		{
			std::cout << "Enter the name of the input file: ";
			std::getline(std::cin, input_name);
		}

#ifdef _DEV_
		folder_name = "../inputs/" + input_name + "/";	// folder with inputs in the project directory
#else
		folder_name = "./" + input_name + "/";			//folder in the same location of the executable
#endif

		name = folder_name + input_name + ".gmr";

		std::cout << "\n";
		//tries to read the same location of the executable file of Giraffe
		f = fopen(name.c_str(), "r");
		if ( f == NULL )
		{
			folder_name = "C:/Users/Public/Documents/GiraffeMoor/";
			
			//checks if there isn't a 'GiraffeMoor' folder in public documents
			if ( !std::filesystem::is_directory(folder_name) )
				std::filesystem::create_directory(folder_name);

			name = folder_name + input_name + ".gmr";
			f = fopen(name.c_str(), "r");
			if ( f == NULL )
				std::cout << "Error reading the input file. Try again.\n";
			else
				readOK = true;
		}
		else
		{
			if ( __argc > 1 )
				std::cout << "Running file \"" << input_name << ".gmr\" . . .\n\n\n";
			readOK = true;
		}
	}
	

	char str[1000];
	fpos_t pos;		//variável que salva ponto do stream de leitura

	//Set with mandatory keywords to check if these blocks were defined
	std::unordered_set<std::string_view> mandatory_keywords({ "Environment", "Keypoints" , "Lines" , 
															"Vessels" , "SegmentProperties" , "Solution" });

	while ( ReadKeyword(f, pos, str) )
	{
		//Last keyword
		Log::SetLastKeyword(str);
		if ( cur_level != FirstLevelKeyword::CommentAfterBlock && cur_level != FirstLevelKeyword::Error )
			Log::SetLastValidKeyword(str);

		switch ( cur_level )
		{
		//First level only

			/*-+-+-+-+-+-+-+-+-+-+-+-+-+-+            Environment           +-+-+-+-+-+-+-+-+-+-+-+-+-+-*/
		case FirstLevelKeyword::Environment:
			if ( !mm.environment.Read(f) )
				return false;
			else
				mandatory_keywords.erase("Environment");
			break;

			/*-+-+-+-+-+-+-+-+-+-+-+-+-+-+             Solution             +-+-+-+-+-+-+-+-+-+-+-+-+-+-*/
		case FirstLevelKeyword::Solution:
			if ( !mm.moorsolution.Read(f) )
				return false;
			else
				mandatory_keywords.erase("Solution");
			break;

			/*-+-+-+-+-+-+-+-+-+-+-+-+-+-+           PostProcessing          +-+-+-+-+-+-+-+-+-+-+-+-+-+-*/
		case FirstLevelKeyword::PostProcessing:
			if ( !mm.moorpost.Read(f) )
				return false;
			break;

			/*-+-+-+-+-+-+-+-+-+-+-+-+-+-+           StiffnessMatrix          -+-+-+-+-+-+-+-+-+-+-+-+-+-*/
		case FirstLevelKeyword::StiffnessMatrix:
			mm.stiff_matrix = std::make_unique<StiffnessMatrix>();
			if ( !mm.stiff_matrix->Read(f) )
				return false;
			break;

			/*-+-+-+-+-+-+-+-+-+-+-+-+-+-+           GiraffeSolver           +-+-+-+-+-+-+-+-+-+-+-+-+-+-*/
		case FirstLevelKeyword::GiraffeSolver:
			if ( !gm.gir_solver.Read(f) )
				return false;
			break;

			/*-+-+-+-+-+-+-+-+-+-+-+-+-+-+              Monitors              +-+-+-+-+-+-+-+-+-+-+-+-+-+-*/
		case FirstLevelKeyword::Monitors:
			if ( !gm.monitor.Read(f) )
				return false;
			break;

			/*-+-+-+-+-+-+-+-+-+-+-+-+-+-+     GiraffeConvergenceCriteria     +-+-+-+-+-+-+-+-+-+-+-+-+-+-*/
		case FirstLevelKeyword::GiraffeConvergenceCriteria:
			if ( !gm.conv_criteria.Read(f) )
				return false;
			break;

			/*-+-+-+-+-+-+-+-+-+-+-+-+-+-+             Constraints            +-+-+-+-+-+-+-+-+-+-+-+-+-+-*/
		case FirstLevelKeyword::Constraints:
			if ( !mm.moor_constraint.Read(f) )
				return false;
			break;


		//Two levels

			/*-+-+-+-+-+-+-+-+-+-+-+-+-+-+              Keypoints             -+-+-+-+-+-+-+-+-+-+-+-+-+-*/
		case FirstLevelKeyword::Keypoints:
			if ( !LoopReading::TryKeyword(mm.keypoint_vector, std::unordered_set<std::string_view>({"Keypoint"}), f, pos, str) )
				return false;
			else
				mandatory_keywords.erase("Keypoints");
			break;

			/*-+-+-+-+-+-+-+-+-+-+-+-+-+-+               Vessels              +-+-+-+-+-+-+-+-+-+-+-+-+-+-*/
		case FirstLevelKeyword::Vessels:
			if ( !LoopReading::TryKeyword(mm.vessel_vector, std::unordered_set<std::string_view>({"Vessel"}), f, pos, str) )
				return false;
			else
				mandatory_keywords.erase("Vessels");
			break;

			/*-+-+-+-+-+-+-+-+-+-+-+-+-+-+           SegmentProperty          +-+-+-+-+-+-+-+-+-+-+-+-+-+-*/
		case FirstLevelKeyword::SegmentProperties:
			if ( !LoopReading::TryKeyword(mm.segment_property_vector, std::unordered_set<std::string_view>({"SegmentProperty"}), f, pos, str) )
				return false;
			else
				mandatory_keywords.erase("SegmentProperties");
			break;

			/*-+-+-+-+-+-+-+-+-+-+-+-+-+-+             NodalForces            +-+-+-+-+-+-+-+-+-+-+-+-+-+-*/
		case FirstLevelKeyword::NodalForces:
			if ( !LoopReading::TryKeyword_UnorderedMultiple(mm.moorload_vector, std::unordered_set<std::string_view>({"Node"}), f, pos, str) )
				return false;
			break;

			/*-+-+-+-+-+-+-+-+-+-+-+-+-+-+         VesselDisplacements        +-+-+-+-+-+-+-+-+-+-+-+-+-+-*/
		case FirstLevelKeyword::VesselDisplacements:
			if ( !LoopReading::TryKeyword_UnorderedMultiple(mm.vessel_disp_vector, std::unordered_set<std::string_view>({"DispVesselID"}), f, pos, str) )
				return false;
			break;

			/*-+-+-+-+-+-+-+-+-+-+-+-+-+-+             SegmentSets            +-+-+-+-+-+-+-+-+-+-+-+-+-+-*/
		case FirstLevelKeyword::SegmentSets:
			if ( !LoopReading::TryKeyword(mm.segment_set_vector, std::unordered_set<std::string_view>({"Set"}), f, pos, str) )
				return false;
			break;

			/*-+-+-+-+-+-+-+-+-+-+-+-+-+-+          DisplacementFields        +-+-+-+-+-+-+-+-+-+-+-+-+-+-*/
		case FirstLevelKeyword::DisplacementFields:
			if ( !LoopReading::TryKeyword(mm.disp_field_vector, std::unordered_set<std::string_view>({"DispLineID"}), f, pos, str) )
				return false;
			break;


		//Three levels

			/*-+-+-+-+-+-+-+-+-+-+-+-+-+-+                Lines               +-+-+-+-+-+-+-+-+-+-+-+-+-+-*/
		case FirstLevelKeyword::Lines:
			if ( !LoopReading::TryKeyword(mm.line_vector, std::unordered_set<std::string_view>({"Line", "MooringLine", "Cable"}), f, pos, str) )
				return false;
			else
				mandatory_keywords.erase("Lines");
			break;

			/*-+-+-+-+-+-+-+-+-+-+-+-+-+-+              Platforms             +-+-+-+-+-+-+-+-+-+-+-+-+-+-*/
		case FirstLevelKeyword::Platforms:
			if ( !LoopReading::TryKeyword(mm.platform_vector, std::unordered_set<std::string_view>({"Platform"}), f, pos, str) )
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
			/*-+-+-+-+-+-+-+-+-+-+-+-+-+-+                 ERROR              +-+-+-+-+-+-+-+-+-+-+-+-+-+-*/
		case FirstLevelKeyword::Error:
			std::string warning = std::string("   + \"") + str + "\" is not a valid keyword!";
			Log::AddWarning(warning);

			return false;
		}

	}
END:	fclose(f);

	//Checks if all mandatory blocks were defined
	if (!mandatory_keywords.empty())
	{
		//Initial message
		std::string w = std::string("\n   + ") + std::to_string(mandatory_keywords.size()) + " mandatory block(s) missed:\n";
		Log::AddWarning(w);

		//Appends missed mandatory keywords
		for (const std::string_view& missed_block : mandatory_keywords)
		{
			Log::AddWarning(missed_block);
			Log::AddWarning("\n");
		}
		return false;
	}

	mm.penetration = new Table[mm.line_vector.size()];


	//All ok while reading
	return true;
}


//Check input data before trying to generate the FE model
bool IO::CheckModel()
{
	/// <summary>
	/// 
	/// Talvez seja interessante criar funções para checar cada caso e colocar tudo em um único loop.
	/// Ficaria mais inteligível e fácil de ampliar - principalmente se essas funções auxiliares forem templates
	/// 
	/// </summary>
	/// 
	/// <returns> booleano q indica se o modelo passou por todas as etapas </returns>

	//Track checking status (returned by this function)
	bool modelOk = true;

	std::map<std::string_view, std::size_t> n_keywords{
		//Mandatory blocks
		{"Keypoints", mm.keypoint_vector.size()}, {"Lines", mm.line_vector.size()}, {"Vessels", mm.vessel_vector.size()},
		{"SegmentProperties", mm.segment_property_vector.size()}, {"SolSteps", mm.moorsolution.GetStepsVec().size()},
		/*nothing to check:*/{"Environment", 1}, {"Solution", 1},
	};

	
	//Checks mandatory keywords
	if (mm.keypoint_vector.front().GetNumber() != 1 || mm.keypoint_vector.back().GetNumber() != n_keywords["Keypoints"])				{ Log::AddWarning("\n   + Invalid keypoint numbering");	modelOk = false; }
	if (mm.segment_property_vector.front().GetNumber() != 1 || mm.segment_property_vector.back().GetNumber() == n_keywords["SegProp"])	{ Log::AddWarning("\n   + Invalid segment property numbering");	modelOk = false; }
	if (mm.line_vector.front().GetNumber() != 1 || mm.line_vector.back().GetNumber() != n_keywords["Lines"])							{ Log::AddWarning("\n   + Invalid line numbering"); modelOk = false; }
	{
		std::stringstream ss;
		bool isOk = true;

		std::for_each(mm.line_vector.cbegin(), mm.line_vector.cend(), [&](const Line& line) {
			if (line.keypoint_A > n_keywords["Keypoints"] || line.keypoint_B > n_keywords["Keypoints"]) { 
				ss << "\n   + Invalid keypoint referenced at line number " << line.number ; isOk = false; }
			if (!line.usingSegmentSet)
				std::for_each(line.segments.cbegin(), line.segments.cend(), [&](const LineSegment& seg) {
				if (seg.GetProperty() > n_keywords["SegmentProperties"]) { 
					ss << "\n   + Invalid segment property referenced at line number " << line.number ; isOk = false; }; }
			);//end of nested for_each (segments)
		});//end of first for_each (lines)
		
		if (!isOk)																											{ Log::AddWarning(ss);	modelOk = false; };
	}
	if (mm.vessel_vector.front().GetNumber() != 1 || mm.vessel_vector.back().GetNumber() != n_keywords["Vessels"])					{ Log::AddWarning("\n   + Invalid vessel numbering");	modelOk = false; }
	{
		std::stringstream ss;
		bool isOk = true;

		std::for_each(mm.vessel_vector.cbegin(), mm.vessel_vector.cend(), [&](const Vessel& vessel) { 
			if (vessel.GetKeypoint() > n_keywords["Keypoints"]) { 
				ss << "\n   + Invalid pilot node referenced at vessel number " << vessel.GetNumber() ; isOk = false; }; }
		);//end of for_each
		if (!isOk)																											{ Log::AddWarning(ss);	modelOk = false; }
	}
	if (mm.moorsolution.GetStepsVec().front().GetNumber() != 1 || mm.moorsolution.GetStepsVec().back().GetNumber() != n_keywords["SolSteps"]) { Log::AddWarning("\n   + Invalid solution steps numbering");	modelOk = false; }
	
	//Checks optional keywords
	if (!mm.segment_set_vector.empty())
	{
		std::for_each(mm.segment_set_vector.cbegin(), mm.segment_set_vector.cend(), [&](const SegmentSet& set) {
			std::for_each(set.GetAllSegment().cbegin(), set.GetAllSegment().cend(), [&](const LineSegment& seg) {
				if (seg.GetProperty() > n_keywords["Keypoints"]){
					std::stringstream ss; ss << "\n   + Invalid segment property referenced at segment set number " << set.GetSetID() ; Log::AddWarning(ss); modelOk = false;
				}
			});//end of nested for_each (line segments)
		});//end of first for_each (segment set)
	}
	if (!mm.vessel_disp_vector.empty())
	{
		std::for_each(mm.vessel_disp_vector.cbegin(), mm.vessel_disp_vector.cend(), [&](const VesselDisplacement& disp) {
			if (disp.GetVesselID() > n_keywords["Vessels"]) {
				std::stringstream ss; ss << "\n   + \"" << disp.GetVesselID() << "\" is not a valid vessel ID to apply displacement" ; Log::AddWarning(ss); modelOk = false;
			}
			if (disp.GetStep() > n_keywords["SolSteps"] ){
				std::stringstream ss; ss << "\n   + Invalid analysis step number to displace the vessel number " << disp.GetVesselID(); Log::AddWarning(ss); modelOk = false;
			}
		});//end for (vessel displacements)
	}
	if (!mm.moorpost.platform_cads.empty())
	{
		std::for_each(mm.moorpost.platform_cads.cbegin(), mm.moorpost.platform_cads.cend(), [&](const CADData& c) {
			if (c.GetNumber() > n_keywords["Vessels"]) { 
				std::stringstream ss; ss << "\n   + \"" << c.GetNumber() << "\" is not a valid vessel ID to link a CAD file" ; Log::AddWarning(ss); modelOk = false; }
		});
	}
	if (!mm.disp_field_vector.empty())
	{
		std::for_each(mm.disp_field_vector.cbegin(), mm.disp_field_vector.cend(), [&](const LineDisplacementField& disp) {
			if (disp.GetNumber() > n_keywords["Lines"]) {
				std::stringstream ss; ss << "\n   + \"" << disp.GetNumber() << "\" is not a valid line ID to apply displacement field" ; Log::AddWarning(ss); modelOk = false;
			}
			if (disp.GetStep() > n_keywords["SolSteps"]) {
				std::stringstream ss; ss << "\n   + Invalid analysis step number to displace the vessel number " << disp.GetNumber(); Log::AddWarning(ss); modelOk = false;
			}
		});//end for (displacement fields)
	}
	if (!mm.moorload_vector.empty())
	{
		std::for_each(mm.moorload_vector.cbegin(), mm.moorload_vector.cend(), [&](const MoorLoad& load) {
			//Description
			auto description = load.GetDescription();
			// Warning message
			std::stringstream ss; 
			
			//Check vessel number
			if (description == "vessel")
			{
				if ( load.GetNodeID() > n_keywords["Vessels"] )
					ss << "\n   + Invalid vessel number to apply load: " << load.GetNodeID(); modelOk = false;
			}
			else 
			{ 
				//Check line number
				if ( load.GetLineID() > n_keywords["Lines"] )
				{ ss << "\n   + Invalid line number to apply load: " << load.GetLineID(); modelOk = false; }
				else
				{
					if ( size_t seg = load.GetSegmentID() )
					{
						//With segment defined (not using SegmentSet)
						if ( mm.line_vector[load.GetLineID() - 1].GetNSegments() > 0 && seg > n_keywords["SegmentProperties"] )
						{ ss << "\n   + Invalid segment number to apply load: " << load.GetNodeID() << " at line number " << load.GetLineID(); modelOk = false; }
						//Seg == 0 -> use SegmentSet 
						else
						{
							// No segment set: 
							if ( mm.segment_set_vector.empty() )
							{ ss << "\n   + Invalid segment number to apply load at line number " << load.GetLineID() << ":  no SegmentSet defined"; modelOk = false; }
							else
							{ // Check segment set
								size_t segset_size = mm.segment_set_vector[mm.line_vector[load.GetLineID() - 1].GetSegmentSet() - 1].GetSegmentSetSize();
								if ( seg > segset_size )
								{
									ss << "\n   + Invalid segment number to apply load at line number " << load.GetLineID() << ": segment number " <<
										seg << " is not defined at SegmentSet number " << mm.line_vector[load.GetLineID() - 1].GetSegmentSet(); modelOk = false;
								}
							}
						}// end 'seg == 0'
					} 
				}
			} // end 'else vessel'
			/// Approach for check empty stringstream adapted from https://stackoverflow.com/questions/8046357/how-do-i-check-if-a-stringstream-variable-is-empty-null/36327567
			if (ss.peek() != decltype(ss)::traits_type::eof())
				Log::AddWarning(ss); 

		});//end for (loads)
	}
	mm.moor_constraint.CheckModel(modelOk, n_keywords);



	return modelOk;
}

//Writes Giraffe model file
void IO::WriteGiraffeModelFile()
{
	//Giraffe input file
	std::ofstream fgir(folder_name + input_name + ".txt", std::ofstream::out);

	fgir << "/////////////////////////////////////////////////////////////////////////////\n";
	fgir << "//                                                                         //\n";
	fgir << "//   GIRAFFE input file generated automatically by GIRAFFEMoor v" << version << " //\n";
	fgir << "//                                                                         //\n";
	fgir << "/////////////////////////////////////////////////////////////////////////////\n\n";

	fgir << "\n/*Units:\n\tTime: s\n\tMass: kg\n\tLinear: m\n\tForce: N\n\tRotation: rad\n\tAzimuth: degree\n*/\n";

	//Use scientific notation to float points
	fgir.setf(std::ofstream::scientific);

	fgir << "\nSolutionSteps\t" << gm.solution_vector.size() << "\n";
	for ( Solution* sol : gm.solution_vector )
		sol->WriteGiraffeModelFile(fgir);

	fgir << "\nMonitor\n";
	gm.monitor.WriteGiraffeModelFile(fgir);

	fgir << "\nPostFiles\n";
	gm.post.WriteGiraffeModelFile(fgir);

	fgir << "\nSolverOptions\n";
	gm.gir_solver.WriteGiraffeModelFile(fgir);

	fgir << "\nConvergenceCriteria\n";
	gm.conv_criteria.WriteGiraffeModelFile(fgir);

	/************************
	 * SORT NODE SET VECTOR *
	 ************************/
	std::sort(gm.node_set_vector.begin(), gm.node_set_vector.end());

	fgir << "\nNodeSets\t" << gm.node_set_vector.size() << "\n";
	for ( NodeSet& ns : gm.node_set_vector )
		ns.WriteGiraffeModelFile(fgir);

	fgir << "\nPipeSections\t" << gm.pipe_section_vector.size() << "\n";
	for ( PipeSection& ps : gm.pipe_section_vector )
		ps.WriteGiraffeModelFile(fgir);

	fgir << "\nRigidBodyData\t" << gm.rbdata_vector.size() << "\n";
	for ( RigidBodyData& rbdata : gm.rbdata_vector )
		rbdata.WriteGiraffeModelFile(fgir);

	if ( !gm.post.cads_vector.empty() )
	{
		fgir << "\nCADData\t" << gm.post.cads_vector.size() << "\n";
		for ( CADData& cad : gm.post.cads_vector )
			cad.WriteGiraffeModelFile(fgir);
	}

	fgir << "\nConstraints\t" << gm.constraint_vector.size() << "\n";
	for ( Constraint* constraint : gm.constraint_vector )
		constraint->WriteGiraffeModelFile(fgir);

	fgir << "\nEnvironment\n";
	gm.environment.WriteGiraffeModelFile(fgir);

	fgir << "\nContacts\t" << gm.contact_vector.size() << "\n";
	for ( Contact* cont : gm.contact_vector )
		cont->WriteGiraffeModelFile(fgir);

	fgir << "\nSurfaces\t" << gm.oscillatory_vector.size() << "\n";
	for ( OscillatorySurf& osc_surf : gm.oscillatory_vector )
		osc_surf.WriteGiraffeModelFile(fgir);

	fgir << "\nSurfaceSets\t" << gm.surface_set_vector.size() << "\n";
	for ( SurfaceSet& surf_set : gm.surface_set_vector )
		surf_set.WriteGiraffeModelFile(fgir);

	fgir << "\nCoordinateSystems\t" << gm.cs_vector.size() << "\n";
	for ( CoordinateSystem& cood_sys : gm.cs_vector )
		cood_sys.WriteGiraffeModelFile(fgir);

	fgir << "\nSpecialConstraints\t" << gm.special_constraint_vector.size() << "\n";
	for ( SpecialConstraint* spec_constr : gm.special_constraint_vector )
		spec_constr->WriteGiraffeModelFile(fgir);

	fgir << "\nElements\t" << gm.element_vector.size() << "\n";
	for ( Element* element : gm.element_vector )
		element->WriteGiraffeModelFile(fgir);

	fgir << "\nNodes\t" << gm.node_vector.size() << "\n";
	for ( Node& node : gm.node_vector )
		node.WriteGiraffeModelFile(fgir);

	fgir << "\nDisplacements\t" << gm.displacement_vector.size() << "\n";
	for ( Displacement* disp : gm.displacement_vector )
		disp->WriteGiraffeModelFile(fgir);

	if ( !gm.load_vector.empty() )
	{
		fgir << "\nLoads\t" << gm.load_vector.size() << "\n";
		for ( Load* load : gm.load_vector )
			load->WriteGiraffeModelFile(fgir);
	}

	fgir.close();
}
