setup_module(renderer)

set(HEADERS
    ${MODULE_PUBLIC_INCLUDE_DIR}/bounce_gl.h
    ${MODULE_PUBLIC_INCLUDE_DIR}/directional_light_pass_program.h
    ${MODULE_PUBLIC_INCLUDE_DIR}/exceptions.h
    ${MODULE_PUBLIC_INCLUDE_DIR}/g_buffer.h
    ${MODULE_PUBLIC_INCLUDE_DIR}/geometry_pass_program.h
    ${MODULE_PUBLIC_INCLUDE_DIR}/light_pass_program.h
    ${MODULE_PUBLIC_INCLUDE_DIR}/lights.h
    ${MODULE_PUBLIC_INCLUDE_DIR}/material.h
    ${MODULE_PUBLIC_INCLUDE_DIR}/material_manager.h
    ${MODULE_PUBLIC_INCLUDE_DIR}/mesh.h
    ${MODULE_PUBLIC_INCLUDE_DIR}/mesh_loader.h
    ${MODULE_PUBLIC_INCLUDE_DIR}/model.h
    ${MODULE_PUBLIC_INCLUDE_DIR}/model_manager.h
    ${MODULE_PUBLIC_INCLUDE_DIR}/opengl_renderer.h
    ${MODULE_PUBLIC_INCLUDE_DIR}/point_light_pass_program.h
    ${MODULE_PUBLIC_INCLUDE_DIR}/shader_program.h
    ${MODULE_PUBLIC_INCLUDE_DIR}/texture.h
    ${MODULE_PUBLIC_INCLUDE_DIR}/texture_manager.h
    ${MODULE_PUBLIC_INCLUDE_DIR}/vertex_buffer.h
)

set(SOURCES
    src/bounce_gl.cc
    src/directional_light_pass_program.cc
    src/exceptions.cc
    src/g_buffer.cc
    src/geometry_pass_program.cc
    src/light_pass_program.cc
    src/material.cc
    src/material_manager.cc
    src/mesh.cc
    src/mesh_loader.cc
    src/model.cc
    src/model_manager.cc
    src/opengl_renderer.cc
    src/point_light_pass_program.cc
    src/shader_program.cc
    src/texture.cc
    src/texture_manager.cc
    src/vertex_buffer.cc
)

add_library(
    ${MODULE_NAME}
    STATIC
    ${HEADERS}
    ${SOURCES}
)

target_link_libraries(${MODULE_NAME} framework)

if (MSVC)
    set(GLEW_ROOT_DIR "${Bounce_SOURCE_DIR}/external/glew-1.10.0")
    set(GLEW_INCLUDE_DIR "${GLEW_ROOT_DIR}/include")
    set(GLEW_LIBRARY "${GLEW_ROOT_DIR}/lib/Release/Win32/glew32.lib")
endif()

find_package(GLEW REQUIRED)
if (GLEW_FOUND)
    include_directories(${GLEW_INCLUDE_DIR})
    target_link_libraries(${MODULE_NAME} ${GLEW_LIBRARIES})
endif (GLEW_FOUND)

find_package(OPENGL REQUIRED)
if (OPENGL_FOUND)
#    message("OPENGL_INCLUDE_DIR: ${OPENGL_INCLUDE_DIR}")
#    message("OPENGL_LIBRARIES: ${OPENGL_LIBRARIES}")
    include_directories(${OPENGL_INCLUDE_DIR})
    target_link_libraries(${MODULE_NAME} ${OPENGL_LIBRARIES})
endif (OPENGL_FOUND)

include_directories("${Bounce_SOURCE_DIR}/external/glm")
