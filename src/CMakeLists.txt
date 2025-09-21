file(GLOB DETEKT_SOURCES  "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/*.h")

add_library(detekt STATIC ${DETEKT_SOURCES})

# Set the folder for Visual Studio
set_target_properties(detekt PROPERTIES FOLDER "detekt")

include_directories(${CMAKE_SOURCE_DIR}/tsg/include)

target_link_libraries(detekt PRIVATE tsg)

# Settings compiler options
target_compile_features(detekt PUBLIC cxx_std_23)