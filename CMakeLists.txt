cmake_minimum_required(VERSION 3.16)
include(../../cmake/build.cmake)

# Project Values:
set(PROJECT_NAME ZyniacCommandHandler)
set(PROJECT_VERSION 0.1)
set(PROJECT_DESCRIPTION "The command handler for Zyniac")
set(PROJECT_TEST test_cmdhandler)
set(PROJECT_LIB command-handler)
#----------------

project(${PROJECT_NAME} VERSION ${PROJECT_VERSION} DESCRIPTION ${PROJECT_DESCRIPTION})

if(DEFINED $ENV{Boost_ROOT}) # Windows Boost Path
	cmake_policy(SET CMP0074 NEW)
endif()

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

list(APPEND LibraryDirs ${CMAKE_BINARY_DIR})

set(MADE_BUILD FALSE)
set(MADE_TEST_BUILD FALSE)
set(MADE_LIBRARY_BUILD FALSE)

#Project Set:
addproject("command-line-interface")
#------------

message(STATUS ${DEFINES})

set(IncludeDir "${CMAKE_CURRENT_SOURCE_DIR}/Include/")
set(SourceDir "${CMAKE_CURRENT_SOURCE_DIR}/src/")

find_package(Boost REQUIRED)

set(IncludeDirs ${IncludeDirs} ${IncludeDir} ${Boost_INCLUDE_DIRS})
set(LibraryDirs ${LibraryDirs} ${Boost_LIBRARY_DIRS})
set(Libraries ${Libraries} ${Boost_LIBRARIES})

file(GLOB_RECURSE IncludeFiles "${IncludeDir}*.h")
file(GLOB_RECURSE SourceFiles "${SourceDir}*.cpp")

set(MainFile "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp")

set(LibFiles ${SourceFiles})
set(ExeFiles ${IncludeFiles} ${SourceFiles})

list(LENGTH LibFiles liblength)
list(FIND LibFiles ${MainFile} LibContainsMain)

if(liblength GREATER 1)

    list(REMOVE_ITEM LibFiles ${MainFile})

    if(${LibContainsMain} GREATER -1)
        message(STATUS "Generating TEST executable and LIBRARY")
        genexe()
        genlib()
    else()
        message(STATUS "Generating only LIBRARY, TEST NOT FOUND")
        genlib()
    endif()

else()
    message(STATUS "FILES ARE MISSING")
    if(liblength EQUAL 1 AND ${LibContainsMain} GREATER -1) # AND LibContainsMain
        message(STATUS "CANNOT generate LIBRARY because files are missing, BUT TEST can generate")
        genexe()
    endif()
endif()

if(MADE_BUILD)
    message(STATUS "Build files will be written to")
    if(MADE_LIBRARY_BUILD)
        message(STATUS "    - Library DIR: ${LIBRARY_OUTPUT_PATH}")
    endif()

    if(MADE_TEST_BUILD)
        message(STATUS "    - Executable DIR: ${EXECUTABLE_OUTPUT_PATH}")
    endif()
else()
    message(STATUS "Build failed")
endif()