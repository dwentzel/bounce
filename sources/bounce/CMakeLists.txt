setup_module(bounce)

set(HEADERS
    ${MODULE_PUBLIC_INCLUDE_DIR}/ApplicationContext.hpp
    ${MODULE_PUBLIC_INCLUDE_DIR}/Event.hpp
    ${MODULE_PUBLIC_INCLUDE_DIR}/LockFreeQueue.hpp
    ${MODULE_PUBLIC_INCLUDE_DIR}/EntryPoint.hpp
    include/App.hpp
    include/KeyboardState.hpp
    include/ShaderManager.hpp
    include/Timer.hpp
    include/bounceGL.hpp)

set(SOURCES
    src/App.cpp
    src/ApplicationContext.cpp
    src/EntryPoint.cpp
    src/KeyboardState.cpp
    src/ShaderManager.cpp)

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

add_test(${TEST_EXE_NAME} ${TEST_EXE_NAME})
