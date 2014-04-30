set(LIBNAME bounce)

set(MODULE_PUBLIC_INCLUDE_DIR ${PUBLIC_INCLUDE_DIR}/${LIBNAME})

include_directories(
    ${PUBLIC_INCLUDE_DIR}
    ${MODULE_PUBLIC_INCLUDE_DIR}
    include)

set(SOURCES
    ${MODULE_PUBLIC_INCLUDE_DIR}/Event.h
    ${MODULE_PUBLIC_INCLUDE_DIR}/LockFreeQueue.h
    ${MODULE_PUBLIC_INCLUDE_DIR}/EntryPoint.h
    include/App.h
    include/ShaderManager.h
    include/Timer.h
    include/bounceGL.h
    src/App.cpp
    src/EntryPoint.cpp
    src/KeyboardState.cpp
    src/ShaderManager.cpp)

add_library(
    ${LIBNAME}
    SHARED
    ${SOURCES}
)

#source_group(\\ FILES ${SOURCES} ${HEADERS})
#source_group(\\event FILES ${EVENT_SOURCES})

find_package(glew REQUIRED)
if (GLEW_FOUND)
    include_directories(${GLEW_INCLUDE_DIR})
    target_link_libraries(${LIBNAME} ${GLEW_LIBRARIES})
endif (GLEW_FOUND)

find_package(OpenGL REQUIRED)
if (OPENGL_FOUND)
    include_directories(${OPENGL_INCLUDE_DIR})
    target_link_libraries(${LIBNAME} ${OPENGL_LIBRARIES})
endif (OPENGL_FOUND)

target_link_libraries(${LIBNAME} logging)

add_custom_target(copy_shaders ALL)

add_custom_command(TARGET copy_shaders POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E
        copy_directory "${PROJECT_SOURCE_DIR}/bounce/shaders" "${CMAKE_BINARY_DIR}/bin/shaders")

###########################################################
# Tests

set(TEST_EXE_NAME bounce_unit_tests)

add_executable(${TEST_EXE_NAME}
    test/LockFreeQueueTest.cpp
    test/KeyboardStateTest.cpp)

target_include_directories(
    ${TEST_EXE_NAME} PRIVATE
    ${gtest_SOURCE_DIR}/include
    ${gtest_SOURCE_DIR})

target_link_libraries(${TEST_EXE_NAME} bounce)
target_link_libraries(${TEST_EXE_NAME} gtest gtest_main)

add_test(NAME bounce_unit_tests COMMAND bounce_unit_tests)
