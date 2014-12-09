setup_module(bounce_mac)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ObjC++")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -ObjC++")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -ObjC++")

set(HEADERS
    include/app_delegate.h
    include/bounce_application.h
    include/bounce_window.h
    include/console_log_output.h
    include/osx_application_context.h
)

set(SOURCES
    src/main.mm
    src/app_delegate.mm
    src/bounce_application.mm
    src/bounce_window.mm
    src/console_log_output.mm
    src/osx_application_context.mm
)

add_library(
    ${MODULE_NAME}
    ${HEADERS}
    ${SOURCES}
)
    

#source_group(\\ FILES ${SOURCES})

find_library(COCOA_LIBRARY Cocoa)

target_link_libraries(${MODULE_NAME} ${COCOA_LIBRARY} engine)

#set_target_properties(${EXENAME} PROPERTIES
#    RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/build/Debug
#    RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/build/Release
#)

#set(RESOURCE_GUI
#${PROJECT_SOURCE_DIR}/resources/shaders/triangleShader.vert.glsl
#)

#set_source_files_properties(
#${RESOURCE_GUI}
#PROPERTIES
#RESOURCE Resources)


