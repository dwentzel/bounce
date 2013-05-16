set(EXENAME bounce)
set(SOURCES EntryPoint.cpp App.cpp ShaderManager.cpp)
add_library(
    ${EXENAME}
    SHARED
    ${SOURCES}
)
find_package(glew REQUIRED)
if (GLEW_FOUND)
    include_directories(${GLEW_INCLUDE_DIR})
    target_link_libraries(${EXENAME} ${GLEW_LIBRARIES})
endif (GLEW_FOUND)
find_package(OpenGL REQUIRED)
if (OPENGL_FOUND)
    message(${OPENGL_INCLUDE_DIR})
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
        copy_directory "${PROJECT_SOURCE_DIR}/bounce/shaders" "../shaders")
