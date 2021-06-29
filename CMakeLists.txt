cmake_minimum_required(VERSION 3.20)

## Project name and version
project(GiraffeMoor VERSION 0.03.01)


## specify the C++ standard
#-- it must be located above the add_executable function
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)


## Organize source/header files 
## in a "filter tree" in Visual Studio

#-- Header files
set(Header_Files_Auxiliary
	src/auxiliary/AuxFunctions.h
	src/auxiliary/BoolTable.h
	src/auxiliary/IO.h
	src/auxiliary/Log.h
	src/auxiliary/LoopReading.h
	src/auxiliary/MathCode.h
	src/auxiliary/Matrix.h
	src/auxiliary/Summary.h
	src/auxiliary/Table.h
	)
set(Header_Files_Giraffe
	src/giraffe/CADData.h
	src/giraffe/Contact.h
	src/giraffe/ConvergenceCriteria.h
	src/giraffe/CoordinateSystem.h
	src/giraffe/Displacement.h
	src/giraffe/DisplacementField.h
	src/giraffe/Dynamic.h
	src/giraffe/Element.h
	src/giraffe/Environment.h
	src/giraffe/GiraffeModel.h
	src/giraffe/GiraffeSolver.h
	src/giraffe/Load.h
	src/giraffe/NodalConstraint.h
	src/giraffe/NodalDisplacement.h
	src/giraffe/NodalForce.h
	src/giraffe/Node.h
	src/giraffe/NodeSet.h
	src/giraffe/NSSS.h
	src/giraffe/OscillatorySurf.h
	src/giraffe/Pipe.h
	src/giraffe/PipeSection.h
	src/giraffe/Post.h
	src/giraffe/RigidBody.h
	src/giraffe/RigidBodyData.h
	src/giraffe/RigidNodeSet.h
	src/giraffe/SameDisplacement.h
	src/giraffe/SameRotation.h
	src/giraffe/SeaCurrent.h
	src/giraffe/Solution.h
	src/giraffe/SpecialConstraint.h
	src/giraffe/Static.h
	src/giraffe/SurfaceSet.h
	src/giraffe/Truss.h
	src/giraffe/Monitor.h
	)
set(Header_Files_GMoor
	src/gmoor/AnchorConstraint.h
	src/gmoor/ConcentratedMass.h
	src/gmoor/Connectivity.h
	src/gmoor/GiraffeMoor.h
	src/gmoor/Keypoint.h
	src/gmoor/Line.h
	src/gmoor/LineConstraint.h
	src/gmoor/LineDisplacementField.h
	src/gmoor/LineSegment.h
	src/gmoor/MoorConstraint.h
	src/gmoor/MoorEnvironment.h
	src/gmoor/MooringModel.h
	src/gmoor/MoorLoad.h
	src/gmoor/MoorPost.h
	src/gmoor/MoorSolution.h
	src/gmoor/Platform.h
	src/gmoor/Seabed.h
	src/gmoor/SegmentProperty.h
	src/gmoor/SegmentSet.h
	src/gmoor/SineWaveDisplacement.h
	src/gmoor/SolutionStep.h
	src/gmoor/StiffnessMatrix.h
	src/gmoor/TouchdownZone.h
	src/gmoor/Vessel.h
	src/gmoor/VesselConstraint.h
	src/gmoor/VesselDisplacement.h
	)
set(Header_Files_All
	src/main.cpp
	src/PCH.h
	${Header_Files_Auxiliary} #Auxiliary
	${Header_Files_Giraffe} #Giraffe
	${Header_Files_GMoor} #GiraffeMoor
	)

#-- Source Files
set(Source_Files_Auxiliary
	src/auxiliary/BoolTable.cpp
	src/auxiliary/IO.cpp
	src/auxiliary/Log.cpp
	src/auxiliary/MathCode.cpp
	src/auxiliary/Matrix.cpp
	src/auxiliary/Summary.cpp
	src/auxiliary/Table.cpp
	)
set(Source_Files_Giraffe
	src/giraffe/CADData.cpp
	src/giraffe/Constraint.h
	src/giraffe/Constraint.cpp
	src/giraffe/Contact.cpp
	src/giraffe/ConvergenceCriteria.cpp
	src/giraffe/CoordinateSystem.cpp
	src/giraffe/Displacement.cpp
	src/giraffe/DisplacementField.cpp
	src/giraffe/Dynamic.cpp
	src/giraffe/Element.cpp
	src/giraffe/Environment.cpp
	src/giraffe/GiraffeModel.cpp
	src/giraffe/GiraffeSolver.cpp
	src/giraffe/Load.cpp
	src/giraffe/Monitor.cpp
	src/giraffe/NodalConstraint.cpp
	src/giraffe/NodalDisplacement.cpp
	src/giraffe/NodalForce.cpp
	src/giraffe/Node.cpp
	src/giraffe/NodeSet.cpp
	src/giraffe/NSSS.cpp
	src/giraffe/OscillatorySurf.cpp
	src/giraffe/Pipe.cpp
	src/giraffe/PipeSection.cpp
	src/giraffe/Post.cpp
	src/giraffe/RigidBody.cpp
	src/giraffe/RigidBodyData.cpp
	src/giraffe/RigidNodeSet.cpp
	src/giraffe/SameDisplacement.cpp
	src/giraffe/SameRotation.cpp
	src/giraffe/SeaCurrent.cpp
	src/giraffe/Solution.cpp
	src/giraffe/SpecialConstraint.cpp
	src/giraffe/Static.cpp
	src/giraffe/SurfaceSet.cpp
	src/giraffe/Truss.cpp
	)
set(Source_Files_GMoor
	src/gmoor/AnchorConstraint.cpp
	src/gmoor/ConcentratedMass.cpp
	src/gmoor/Connectivity.cpp
	src/gmoor/Cylinder.cpp
	src/gmoor/Cylinder.h
	src/gmoor/Keypoint.cpp
	src/gmoor/Line.cpp
	src/gmoor/LineConstraint.cpp
	src/gmoor/LineDisplacementField.cpp
	src/gmoor/LineSegment.cpp
	src/gmoor/MoorConstraint.cpp
	src/gmoor/MoorEnvironment.cpp
	src/gmoor/MooringModel.cpp
	src/gmoor/MoorLoad.cpp
	src/gmoor/MoorPost.cpp
	src/gmoor/MoorSolution.cpp
	src/gmoor/Platform.cpp
	src/gmoor/Seabed.cpp
	src/gmoor/SegmentProperty.cpp
	src/gmoor/SegmentSet.cpp
	src/gmoor/SineWaveDisplacement.cpp
	src/gmoor/SolutionStep.cpp
	src/gmoor/StiffnessMatrix.cpp
	src/gmoor/TouchdownZone.cpp
	src/gmoor/Vessel.cpp
	src/gmoor/VesselConstraint.cpp
	src/gmoor/VesselDisplacement.cpp
	)
set(Source_Files_All
	src/main.cpp
	src/PCH.cpp
	${Source_Files_Auxiliary}	# Auxiliary
	${Source_Files_Giraffe}		# Giraffe
	${Source_Files_GMoor}		# GiraffeMoor
	)


#-- Create the tree in the VS solution explorer
set(Source_Tree ${Source_Files_All} ${Header_Files_All})
#add_executable(${PROJECT_NAME} ${Source_Tree})
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${Source_Tree})


## Configure a header file to pass some of the CMake settings to the source code
configure_file(${PROJECT_NAME}Config.h.in ${PROJECT_NAME}Config.h)

## Create exe and set GiraffeMoor as startup
add_executable(${PROJECT_NAME} ${Source_Tree})
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})


## Folders with headers
target_include_directories(${PROJECT_NAME} 
	PUBLIC
	${PROJECT_BINARY_DIR}
	${CMAKE_CURRENT_SOURCE_DIR}/src 
	${CMAKE_CURRENT_SOURCE_DIR}/src/auxiliary 
	${CMAKE_CURRENT_SOURCE_DIR}/src/giraffe 
	${CMAKE_CURRENT_SOURCE_DIR}/src/gmoor
	)


# To use 'fscanf' instead of 'fscanf_s' or c++ ifstream without getting any errors
# and other C-functions without proper security implementations
target_compile_definitions(${PROJECT_NAME}  PRIVATE _CRT_SECURE_NO_WARNINGS)

#####################################################################################
#							Precompiled header										#
#																					#
# Solution taken from the Mark's comment (at may 2016) in:							#
# https://stackoverflow.com/questions/148570/using-pre-compiled-headers-with-cmake/ #
#####################################################################################
if (MSVC)
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /YuPCH.h /FIPCH.h")
endif()

set_source_files_properties(src/PCH.cpp
    PROPERTIES	COMPILE_FLAGS "/YcPCH.h")
## End precompiled


#	#if(USE_MKL)
	#set(DSUFIX "")
	#if(BUILD_SHARED)
	#    set(DSUFIX "_dll")
	#endif()
	#target_link_libraries(${PROJECT_NAME} 
	#	mkl_intel_lp64${DSUFIX} 
	#	mkl_intel_thread${DSUFIX} 
	#	mkl_core${DSUFIX} 
	#	libiomp5md
	#	)
	#    #else()
	#    #    target_link_libraries(${PROJECT_NAME} libopenblas)
	#    #endif()
		
		