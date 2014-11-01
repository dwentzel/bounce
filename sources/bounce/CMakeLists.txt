setup_module(bounce)

set(HEADERS
    ${MODULE_PUBLIC_INCLUDE_DIR}/application_context.h
    ${MODULE_PUBLIC_INCLUDE_DIR}/event.h
    ${MODULE_PUBLIC_INCLUDE_DIR}/lock_free_queue.h
    ${MODULE_PUBLIC_INCLUDE_DIR}/entry_point.h
    include/app.h
    include/bounce_gl.h
    include/console.h
    include/control_component.h
    include/game_component.h
    include/game_component_type.h
    include/game_entity.h
    include/game_system.h
    include/importer.h
    include/keyboard_state.h
    include/material.h
    include/mesh.h
    include/message.h
    include/model.h
    include/movement_component.h
    include/object.h
    include/render_component.h
    include/render_system.h
    include/shader_manager.h
    include/single_color_texture_generator.h
    include/timer.h
    include/transform_component.h
    include/vertex_buffer.h
    include/world_manager.h)

set(SOURCES
    src/app.cc
    src/application_context.cc
    src/console.cc
    src/control_component.cc
    src/entry_point.cc
    src/event.cc
    src/game_component.cc
    src/game_entity.cc
    src/game_system.cc
    src/importer.cc
    src/keyboard_state.cc
    src/material.cc
    src/mesh.cc
    src/message.cc
    src/model.cc
    src/movement_component.cc
    src/object.cc
    src/render_component.cc
    src/render_system.cc
    src/shader_manager.cc
    src/single_color_texture_generator.cc
    src/transform_component.cc
    src/vertex_buffer.cc
    src/world_manager.cc)

add_library(
    ${MODULE_NAME}
    STATIC
    ${HEADERS}
    ${SOURCES})

if (MSVC)
	set(GLEW_ROOT_DIR "${Bounce_SOURCE_DIR}/external/glew-1.10.0")
	set(GLEW_INCLUDE_DIR "${GLEW_ROOT_DIR}/include")
	set(GLEW_LIBRARY "${GLEW_ROOT_DIR}/lib/Release/Win32/glew32.lib")
endif()

find_package(assimp REQUIRED)
if (assimp_FOUND)
    message("assimp_INCLUDE_DIR: ${assimp_INCLUDE_DIR}")
	include_directories(${assimp_INCLUDE_DIR})
    message("assimp_LIBRARIES: ${assimp_LIBRARIES}")
	target_link_libraries(${MODULE_NAME} ${assimp_LIBRARIES})
else (assimp_FOUND)
    message("Could not find assimp")
endif (assimp_FOUND)


find_package(glew REQUIRED)
if (GLEW_FOUND)
    include_directories(${GLEW_INCLUDE_DIR})
    target_link_libraries(${MODULE_NAME} ${GLEW_LIBRARIES})
endif (GLEW_FOUND)

find_package(OpenGL REQUIRED)
if (OPENGL_FOUND)
    include_directories(${OPENGL_INCLUDE_DIR})
    target_link_libraries(${MODULE_NAME} ${OPENGL_LIBRARIES})
endif (OPENGL_FOUND)

include_directories("${Bounce_SOURCE_DIR}/external/glm")

target_link_libraries(${MODULE_NAME} logging)

###########################################################
# Tests

#set(TEST_EXE_NAME bounce_unit_tests)

#add_executable(${TEST_EXE_NAME}
#    test/LockFreeQueueTest.cpp
#    test/KeyboardStateTest.cpp)

#target_include_directories(
#    ${TEST_EXE_NAME} PRIVATE
#    ${gtest_SOURCE_DIR}/include
#    ${gtest_SOURCE_DIR})

#target_link_libraries(${TEST_EXE_NAME} bounce)
#target_link_libraries(${TEST_EXE_NAME} gtest gtest_main)

#add_test(${TEST_EXE_NAME} ${TEST_EXE_NAME})
