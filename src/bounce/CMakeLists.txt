set(EXENAME bounce_main)
set(SOURCES bounce.cpp App.cpp loadShaders.cpp)
add_executable(
    ${EXENAME}
    #MACOSX_BUNDLE 
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
find_package(sdl REQUIRED)


if (SDL_FOUND)
    message(${SDL_LIBRARY})
    include_directories(${SDL_INCLUDE_DIR}/..)
    target_link_libraries(${EXENAME} ${SDL_LIBRARY})
endif (SDL_FOUND)


target_link_libraries(${EXENAME} bounceui)
