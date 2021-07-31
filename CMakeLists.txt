cmake_minimum_required(VERSION 3.20)


## Set target configuration and platform
set(CMAKE_CONFIGURATION_TYPES "Debug;Release")
set(CMAKE_GENERATOR_PLATFORM x64)
set(MKL_INTERFACE lp64)


## Project name and version
project(GiraffeMoor VERSION 0.03.04 LANGUAGES CXX)


## specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)


## Set "GiraffeMoor" as startup project, not the default ALL_BUILD
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT GiraffeMoor)


## If true, the computer must have oneMKL installed, 
# Otherwise, it is assumed that MKL DLLs will be used in .exe 
# directory or its folder is already added to system path 
option(USE_oneMKL "installed from Intel oneAPI" ON)
#-- Search for oneMKL
if(USE_oneMKL)
	find_package(MKL CONFIG REQUIRED)
endif()


## Organize files in solution explorer with a "filter tree"
FILE(GLOB_RECURSE files
	${CMAKE_CURRENT_SOURCE_DIR}/src/*.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
	)
#-- Create the tree in the VS solution explorer
set(TREE_FILES ${files})
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${TREE_FILES})


## Include directories
file(GLOB INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src/*)
list(APPEND INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src )
list(REMOVE_DUPLICATES INCLUDE_DIR)
#-- Remove possible headers and source files
list(FILTER INCLUDE_DIR EXCLUDE REGEX ".h$")
list(FILTER INCLUDE_DIR EXCLUDE REGEX ".hpp$")
list(FILTER INCLUDE_DIR EXCLUDE REGEX ".cpp$")


## Configure a header file to pass some of the CMake settings to the source code
configure_file(${PROJECT_NAME}Config.h.in ${PROJECT_NAME}Config.h)


## Other files to include in Visual Studio solution explorer
set(FILES_TO_ADD README.md)

## Create the executable
add_executable(${PROJECT_NAME} ${TREE_FILES} ${FILES_TO_ADD})


# To use 'scanf' instead of 'scanf_s' or c++ fstream without getting any errors
target_compile_definitions(${PROJECT_NAME} PRIVATE _CRT_SECURE_NO_WARNINGS)


##
## Define different options for oneMKL or DLLs
##
if(USE_oneMKL)
	target_compile_options(${PROJECT_NAME} 
	  PUBLIC 
		$<TARGET_PROPERTY:MKL::MKL,INTERFACE_COMPILE_OPTIONS>
	  PRIVATE
		# Set the warning level. Solution taken from: https://stackoverflow.com/questions/2368811/how-to-set-warning-level-in-cmake
		$<$<CXX_COMPILER_ID:MSVC>:/W3> # '/WX' to treat warnings as erros in VS
		$<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -pedantic> # '-Werror' to treat warnings as errors in other compilers
		)
	target_include_directories(${PROJECT_NAME} 
	  PUBLIC
		$<TARGET_PROPERTY:MKL::MKL,INTERFACE_INCLUDE_DIRECTORIES> # oneMKL
		${PROJECT_BINARY_DIR} # to use the 'configure_file'
	  PRIVATE
		${INCLUDE_DIR}
		)
		
	target_link_libraries(${PROJECT_NAME} PUBLIC $<LINK_ONLY:MKL::MKL>)
# MKL DLLs
else() 
	target_compile_options(${PROJECT_NAME} 
	  PRIVATE
		# Set the warning level. 
		$<$<CXX_COMPILER_ID:MSVC>:/W3> # add '/WX' to treat warnings as erros in VS
		$<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -pedantic> # add '-Werror' to treat warnings as errors in other compilers
		)
		
	target_include_directories(${PROJECT_NAME} 
	  PRIVATE
		${INCLUDE_DIR}
		)
	
	target_link_libraries(${PROJECT_NAME} 
	  PUBLIC 
		mkl_intel_lp64_dll.lib 
		mkl_core_dll.lib 
		mkl_intel_thread_dll.lib 
		libiomp5md.lib 
		)
	
	target_link_directories(${PROJECT_NAME} 
	  PUBLIC  
		${CMAKE_SOURCE_DIR}/dependencies/mkl/lib
		)
endif() # oneMKL or MKL DLLs



## Compiler flags
if (MSVC)
	# Precompiled header 
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /YuPCH.h /FIPCH.h")
	set_source_files_properties(src/PCH.cpp	PROPERTIES COMPILE_FLAGS "/YcPCH.h")
	
	# Change the Visual Studio working directory
	set_target_properties(${PROJECT_NAME} PROPERTIES
		VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/inputs")
endif()

