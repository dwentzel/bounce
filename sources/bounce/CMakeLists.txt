setup_module(bounce)

set(HEADERS
    ${MODULE_PUBLIC_INCLUDE_DIR}/application_context.h
    ${MODULE_PUBLIC_INCLUDE_DIR}/event.h
    ${MODULE_PUBLIC_INCLUDE_DIR}/lock_free_queue.h
    ${MODULE_PUBLIC_INCLUDE_DIR}/entry_point.h
    include/app.h
    include/bounce_gl.h
    include/console.h
    include/game_component.h
    include/game_entity.h
    include/game_system.h
    include/keyboard_state.h
    include/mesh.h
    include/object.h
    include/render_system.h
    include/shader_manager.h
    include/single_color_texture_generator.h
    include/timer.h
    include/world_manager.h)

set(SOURCES
    src/app.cc
    src/application_context.cc
    src/console.cc
    src/entry_point.cc
    src/event.cc
    src/game_component.cc
    src/game_entity.cc
    src/game_system.cc
    src/keyboard_state.cc
    src/mesh.cc
    src/object.cc
    src/render_system.cc
    src/shader_manager.cc
    src/single_color_texture_generator.cc
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
