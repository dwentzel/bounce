set(LIBNAME bounce)

set(MODULE_PUBLIC_INCLUDE_DIR ${PUBLIC_INCLUDE_DIR}/${LIBNAME})

include_directories(
    ${PUBLIC_INCLUDE_DIR}
    ${MODULE_PUBLIC_INCLUDE_DIR}
    include)

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
    src/EntryPoint.cpp
    src/KeyboardState.cpp
    src/ShaderManager.cpp)

add_library(
    ${LIBNAME}
    SHARED
    ${HEADERS}
    ${SOURCES})

#source_group(\\ FILES ${SOURCES} ${HEADERS})
#source_group(\\event FILES ${EVENT_SOURCES})
if (MSVC)
    message(MSVC)

	set(GLEW_ROOT_DIR "${Bounce_SOURCE_DIR}/external/glew-1.10.0")
	set(GLEW_INCLUDE_DIR "${GLEW_ROOT_DIR}/include")
	set(GLEW_LIBRARY "${GLEW_ROOT_DIR}/lib/Release/Win32/glew32.lib")
	#set(GLEW_LIBRARY "${GLEW_ROOT_DIR}/lib/Release/x64/glew.lib")
    #add_library(glew STATIC IMPORTED)
	#set_target_properties(glew PROPERTIES
	#    IMPORTED_LOCATION $(Bounce_SOURCE_DIR)/external/glew-1.10.0/lib/Release/Win32/glew32.lib)
	#include_directories($(Bounce_SOURCE_DIR)/external/glew-1.10.0/include)
else ()
    
endif()

include_directories("${Bounce_SOURCE_DIR}/external/glm")

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

#add_custom_target(copy_shaders ALL)

#add_custom_command(TARGET copy_shaders POST_BUILD
#    COMMAND ${CMAKE_COMMAND} -E
#        copy_directory "${PROJECT_SOURCE_DIR}/bounce/shaders" "${CMAKE_BINARY_DIR}/bin/shaders")

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
