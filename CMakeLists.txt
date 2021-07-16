cmake_minimum_required(VERSION 3.20)

## Project name and version
project(GiraffeMoor VERSION 0.03.02)


## specify the C++ standard
#-- it must be located above the add_executable function
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)


## Organize source/header files 
## in a "filter tree" in Visual Studio solution explorer
FILE(GLOB_RECURSE files_aux 
	${CMAKE_SOURCE_DIR}/src/*.h ${CMAKE_SOURCE_DIR}/src/*.hpp ${CMAKE_SOURCE_DIR}/src/*.cpp
	${CMAKE_SOURCE_DIR}/src/auxiliary/*.h ${CMAKE_SOURCE_DIR}/src/auxiliary/*.hpp ${CMAKE_SOURCE_DIR}/src/auxiliary/*.cpp
	${CMAKE_SOURCE_DIR}/src/giraffe/*.h ${CMAKE_SOURCE_DIR}/src/giraffe/*.hpp ${CMAKE_SOURCE_DIR}/src/giraffe/*.cpp
	${CMAKE_SOURCE_DIR}/src/gmoor/*.h ${CMAKE_SOURCE_DIR}/src/gmoor/*.hpp ${CMAKE_SOURCE_DIR}/src/gmoor/*.cpp
	)
set(Source_Files_All ${files_aux})


#-- Create the tree in the VS solution explorer
set(Source_Tree ${Source_Files_All})
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
