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
    ${MODULE_PUBLIC_INCLUDE_DIR}/model_loader.h
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
    src/directional_light_pass_program.cc
    src/geometry_pass_program.cc
    src/light_pass_program.cc
    src/material.cc
    src/material_manager.cc
    src/mesh.cc
    src/mesh_loader.cc
    src/model.cc
    src/model_loader.cc
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
    OBJECT
    ${HEADERS}
    ${SOURCES}
)

setup_compiler(${MODULE_NAME})

find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIR})

find_package(OPENGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})
target_compile_definitions(${MODULE_NAME} PUBLIC -DOPENGL_INCLUDE=<OpenGL/gl.h>)

find_package(ASSIMP REQUIRED)
include_directories(${ASSIMP_INCLUDE_DIR})

include_directories("${Bounce_SOURCE_DIR}/external/glm")

###########################################################
# Tests

set(TEST_HEADERS
    test/glmock.h
    test/glmock_defines.h
)

set(TEST_SOURCES
    test/main.cc
    test/glmock.cc
    test/g_buffer_test.cc
    test/opengl_renderer_test.cc
)

set(TEST_EXE_NAME ${MODULE_NAME}_unit_tests)

add_executable(
    ${TEST_EXE_NAME}
    ${TEST_HEADERS}
    ${TEST_SOURCES}
    ${SOURCES}
    $<TARGET_OBJECTS:logging>
    $<TARGET_OBJECTS:framework>
    $<TARGET_OBJECTS:importer>
)

target_compile_definitions(${TEST_EXE_NAME} PUBLIC -DOPENGL_INCLUDE="glmock.h")

if (XCODE)
    setup_xcode(${TEST_EXE_NAME})
endif (XCODE)

target_include_directories(
    ${TEST_EXE_NAME} PRIVATE
    test
    ${PUBLIC_INCLUDE_DIR}
    ${gmock_SOURCE_DIR}/include
    ${gtest_SOURCE_DIR}/include
    ${gtest_SOURCE_DIR}
)

target_link_libraries(${TEST_EXE_NAME} ${GLEW_LIBRARY})
target_link_libraries(${TEST_EXE_NAME} ${OPENGL_LIBRARIES})
target_link_libraries(${TEST_EXE_NAME} ${ASSIMP_LIBRARIES})

target_link_libraries(${TEST_EXE_NAME} gmock gtest)

add_test(${TEST_EXE_NAME} ${TEST_EXE_NAME})
