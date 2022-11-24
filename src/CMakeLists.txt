include_directories(${PROJECT_SOURCE_DIR}/src/coreapi)
include_directories(${PROJECT_SOURCE_DIR}/common/logger)

add_subdirectory(coreapi)
add_subdirectory(workers)

# create the libraries
add_executable(PluginRecon main.cpp)
target_link_libraries(PluginRecon coreapi FLogger)

install(TARGETS
    PluginRecon
    ARCHIVE
    DESTINATION ${INSTALL_LIBDIR}
    COMPONENT lib
    RUNTIME
    DESTINATION ${INSTALL_BINDIR}
    COMPONENT bin
    LIBRARY
    DESTINATION ${INSTALL_LIBDIR}
    COMPONENT lib
    PUBLIC_HEADER
    DESTINATION ${INSTALL_INCLUDEDIR}
    COMPONENT dev)
	
message (STATUS "Copying configuration files Config.json to the binary directory")
add_custom_command(TARGET PluginRecon 
                    POST_BUILD
                    COMMAND ${CMAKE_COMMAND} -E copy_if_different 
                    ${PROJECT_SOURCE_DIR}/ConfigFiles/logConfig.JSON 
                    $<TARGET_FILE_DIR:PluginRecon>)
