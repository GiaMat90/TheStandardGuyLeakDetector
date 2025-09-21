file(GLOB_RECURSE TEST_SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp	${CMAKE_CURRENT_SOURCE_DIR}/*.h)

add_executable(test ${TEST_SOURCE})

# Set the folder for Visual Studio
set_target_properties(test PROPERTIES FOLDER "test")

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/src/)

# Set up source groups for Visual Studio filters
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} PREFIX "source" FILES ${TEST_SOURCE})

target_link_libraries(test PRIVATE detekt)
# Settings compiler options
target_compile_features(test PUBLIC cxx_std_23)
if(MSVC)
	target_compile_options(test PRIVATE /W4)
else()
	target_compile_options(test PRIVATE -Wall -Wextra)
endif()


