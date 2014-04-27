set(EXENAME bounce)
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)

set(SOURCES
#    App.h
    App.cpp
#    bounceGL.h
#    DefaultLogger.h
#    EntryPoint.h
    EntryPoint.cpp
#    log.h
#    Logger.h
#    LogManager.h
    logging/LogManager.cpp
    KeyboardState.cpp
#    framework/Timer.h
#    ShaderManager.h
    ShaderManager.cpp)

set(EVENT_SOURCES event/Event.h)


add_library(
    ${EXENAME}
    SHARED
    ${SOURCES}
#    ${HEADERS}
)

#source_group(\\ FILES ${SOURCES} ${HEADERS})
#source_group(\\event FILES ${EVENT_SOURCES})

find_package(glew REQUIRED)
if (GLEW_FOUND)
    include_directories(${GLEW_INCLUDE_DIR})
    target_link_libraries(${EXENAME} ${GLEW_LIBRARIES})
endif (GLEW_FOUND)

find_package(OpenGL REQUIRED)
if (OPENGL_FOUND)
    include_directories(${OPENGL_INCLUDE_DIR})
    target_link_libraries(${EXENAME} ${OPENGL_LIBRARIES})
endif (OPENGL_FOUND)

#find_package(sdl REQUIRED)
#if (SDL_FOUND)
#    message(${SDL_LIBRARY})
#    include_directories(${SDL_INCLUDE_DIR}/..)
#    target_link_libraries(${EXENAME} ${SDL_LIBRARY} ${SDLMAIN_LIBRARY} )
#endif (SDL_FOUND)

target_link_libraries(${EXENAME} bounceui)

add_custom_target(copy_shaders ALL)

add_custom_command(TARGET copy_shaders POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E 
        copy_directory "${PROJECT_SOURCE_DIR}/bounce/shaders" "${CMAKE_BINARY_DIR}/bin/shaders")
