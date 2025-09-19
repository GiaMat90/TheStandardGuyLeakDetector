file(GLOB TSLD_SOURCES  "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/*.h")

add_library(tsld STATIC ${TSLD_SOURCES})

# Set the folder for Visual Studio
set_target_properties(tsld PROPERTIES FOLDER "tsld")

include_directories(${CMAKE_SOURCE_DIR}/tsg/include)

target_link_libraries(tsld PRIVATE tsg)
