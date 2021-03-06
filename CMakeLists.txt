cmake_minimum_required(VERSION 3.10)
project("TMXL" VERSION 1.0.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)


option(BUILD_EXAMPLES "Build example projects" ON)
option(BUILD_TESTS "Build tests" OFF)
option(BUILD_TMXL_TEST_ONLY "Build TMXL test only" OFF)
option(BUILD_USE_PUGIXML "Use pugixml parser and build module" ON)
option(BUILD_SHARED_LIBS "Build library as shared" OFF)

if (NOT CMAKE_BUILD_TYPE)
    message(STATUS "No build type selected, default to Release")
	set(CMAKE_BUILD_TYPE "Release")
	message("CMAKE_CXX_FLAGS_RELEASE is ${CMAKE_CXX_FLAGS_RELEASE}")
endif()

#### TMXL Defines ####
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/TMXL/include")
set(CMAKE_DEBUG_POSTFIX d)
set(TMXL_LIBRARY_NAME ${PROJECT_NAME})
set(TMXL_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/TMXL/include")
set(TMXL_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR})
message("TMXL Binary dir: ${CMAKE_CURRENT_BINARY_DIR}")


#### PROJECT TMXL BUILD ####
file(GLOB_RECURSE TMXL_LIBRARY_HEADERS "${PROJECT_SOURCE_DIR}/TMXL/*.h")
file(GLOB_RECURSE TMXL_LIBRARY_SOURCES "${PROJECT_SOURCE_DIR}/TMXL/*.cpp")

if (NOT BUILD_USE_PUGIXML)
	list(REMOVE_ITEM TMXL_LIBRARY_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/TMXL/include/TMXL/Parsers/XML/PugiParser.h")
	list(REMOVE_ITEM TMXL_LIBRARY_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/TMXL/src/Parsers/XML/PugiParser.cpp")
endif()

if (BUILD_SHARED_LIBS)
	add_library(${TMXL_LIBRARY_NAME} SHARED ${TMXL_LIBRARY_HEADERS} ${TMXL_LIBRARY_SOURCES})
else()
	add_library(${TMXL_LIBRARY_NAME} STATIC ${TMXL_LIBRARY_HEADERS} ${TMXL_LIBRARY_SOURCES})
endif()


#### DETECT DEPENDENCIES ####
if (BUILD_USE_PUGIXML)
	add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/extlibs/pugixml")
	target_link_libraries(${TMXL_LIBRARY_NAME} pugixml)
endif()
#### DETECT DEPENDENCIES ####


#### BUILD TESTS #####
if(BUILD_TESTS OR BUILD_TMXL_TEST_ONLY)
    add_subdirectory(tests)
endif()
#### BUILD TESTS #####


#### EXAMPLES BUILD ####
if(BUILD_EXAMPLES)
	add_subdirectory(examples)
endif()
#### EXAMPLES BUILD ####


#### INSTALL SECTION ####
include(GNUInstallDirs)
install(TARGETS ${TMXL_LIBRARY_NAME}
		PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
		LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
		ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR})

install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/TMXL/include/TMXL" DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
#### INSTALL SECTION ####
