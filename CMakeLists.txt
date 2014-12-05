cmake_minimum_required(VERSION 3.18)

project(CPPDlopen)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
set( CMAKE_CXX_FLAGS "-g -Wall -Wl,--no-as-needed -ldl" )

include(CTest)
include(GNUInstallDirs)
include(CMakeOptions.txt)
include_directories(src)

if(${COVERAGE})
	include(CodeCoverage)
endif(${COVERAGE})

add_subdirectory(lib)
if(${TESTS})
add_subdirectory(tests)
	if(${COVERAGE})
		coverage_target(. */lib/* check)
	endif(${COVERAGE})
endif(${TESTS})
if (${SAMPLES})
add_subdirectory(samples)
endif(${SAMPLES})

message(STATUS "TESTS " ${TESTS})
message(STATUS "SAMPLES " ${SAMPLES})
message(STATUS "COVERAGE " ${COVERAGE})
