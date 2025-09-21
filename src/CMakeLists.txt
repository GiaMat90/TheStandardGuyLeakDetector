file(GLOB DETEKT_SOURCES  "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/*.h")

add_library(detekt STATIC ${DETEKT_SOURCES})

# Set the folder for Visual Studio
set_target_properties(detekt PROPERTIES FOLDER "detekt")

# Settings compiler options
target_compile_features(detekt PUBLIC cxx_std_23)

# Ensure PDB files are generated
if(MSVC)
    target_compile_options(detekt PRIVATE $<$<CONFIG:Debug>:/Zi>)
    set_target_properties(detekt PROPERTIES 
        COMPILE_PDB_NAME_DEBUG "detektd"
        COMPILE_PDB_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/lib/Debug"
    )
endif()

# Add this to handle different configurations
if(CMAKE_CONFIGURATION_TYPES)
    # Multi-config generator (Visual Studio, Xcode)
    set_target_properties(detekt PROPERTIES
        DEBUG_POSTFIX "d"
        RELEASE_POSTFIX ""
    )    
	add_custom_target(build_all_configs
        COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --config Debug
        COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --config Release        
        COMMENT "Building all configurations"
    )
endif()

# install targets
install(TARGETS detekt 
	EXPORT detektTargets
	ARCHIVE DESTINATION lib
	LIBRARY DESTINATION lib
	RUNTIME DESTINATION bin
	)
	
# Install PDB files for debugging
if(WIN32)
    install(FILES 
        ${CMAKE_BINARY_DIR}/lib/Debug/detektd.pdb
        DESTINATION lib
        CONFIGURATIONS Debug
        OPTIONAL
    )
endif()
	
# install headers
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/
    DESTINATION include
    FILES_MATCHING PATTERN "*.h"
	)

# CPack configuration
set(CPACK_PACKAGE_NAME "detekt")
set(CPACK_PACKAGE_VERSION ${PROJECT_VERSION})
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "C++ Memory leak detector library")
set(CPACK_PACKAGE_VENDOR "Giacomo Matzeu")
set(CPACK_PACKAGE_CONTACT "giacominomatzeu@gmail.com")
set(CPACK_CONFIGURATION_TYPES "Debug;Release")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/../LICENSE")

if(WIN32)
    set(CPACK_GENERATOR "ZIP;NSIS")
	# NSIS installer configuration
    set(CPACK_NSIS_INSTALL_ROOT "$PROGRAMFILES64")
    set(CPACK_NSIS_PACKAGE_NAME "Detekt")
    set(CPACK_NSIS_DISPLAY_NAME "Detekt")
    set(CPACK_PACKAGE_INSTALL_DIRECTORY "Detekt")
elseif(APPLE)
    set(CPACK_GENERATOR "TGZ")
else()
    set(CPACK_GENERATOR "TGZ;DEB;RPM")
endif()

include(CPack)