cmake_minimum_required(VERSION 3.15)

project(detekt 
	VERSION 1.0.0 
	DESCRIPTION "Memory leak detector"
	LANGUAGES CXX
	)

message(STATUS "Generator: ${CMAKE_GENERATOR}")
message(STATUS "Configuration types: ${CMAKE_CONFIGURATION_TYPES}")
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

# Enable grouping targets into folders
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Set output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Build the engine first
add_subdirectory(src)

# Build the tests
add_subdirectory(test)

