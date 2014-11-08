cmake_minimum_required(VERSION 2.8.12)
project(Bounce)

set(BUILD_SHARED_LIBS OFF)

message(STATUS "CMAKE_PREFIX_PATH: ${CMAKE_PREFIX_PATH}")



if (MSVC)
#   set(CMAKE_FIND_LIBRARY_PREFIXES "")
#   set(CMAKE_FIND_LIBRARY_SUFFIXES ".lib" ".dll")
elseif (APPLE)
#    set(CMAKE_FIND_LIBRARY_PREFIXES "lib")
#    set(CMAKE_FIND_LIBRARY_SUFFIXES ".so" ".dylib")
elseif (CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
#    message("GNUCC")
endif ()

message(STATUS "Library prefixes: ${CMAKE_FIND_LIBRARY_PREFIXES}")
message(STATUS "Library suffixes: ${CMAKE_FIND_LIBRARY_SUFFIXES}")

message(STATUS "Generator: ${CMAKE_GENERATOR}")

if (APPLE)
    set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${Bounce_SOURCE_DIR}/cmake/modules/osx")
endif (APPLE)
message(STATUS "CMAKE_MODULE_PATH=${CMAKE_MODULE_PATH}")


#set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)
#set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
#set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

set(gtest_force_shared_crt ON)

set(PUBLIC_INCLUDE_DIR ${Bounce_SOURCE_DIR}/headers)

macro(setup_module MODULE)
    message(STATUS "Setting up module ${MODULE}")
    set(MODULE_NAME ${MODULE})

    set(MODULE_PUBLIC_INCLUDE_DIR ${PUBLIC_INCLUDE_DIR}/${MODULE_NAME})

    include_directories(
        ${PUBLIC_INCLUDE_DIR}
        ${MODULE_PUBLIC_INCLUDE_DIR}
        include)
endmacro(setup_module)

macro(setup_testing)
    set(TEST_EXE_NAME ${MODULE_NAME}_unit_tests)

    add_executable(
        ${TEST_EXE_NAME}
        ${TEST_HEADERS}
        ${TEST_SOURCES}
    )

    target_include_directories(
        ${TEST_EXE_NAME} PRIVATE
        ${gtest_SOURCE_DIR}/include
        ${gtest_SOURCE_DIR}
    )

    target_link_libraries(${TEST_EXE_NAME} ${MODULE_NAME})
    target_link_libraries(${TEST_EXE_NAME} gtest gtest_main)

    add_test(${TEST_EXE_NAME} ${TEST_EXE_NAME})
endmacro(setup_testing)

enable_testing()

add_subdirectory(external)
add_subdirectory(sources)
add_subdirectory(resources)
add_subdirectory(tools)
add_subdirectory(game)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(TARGET game PROPERTY FOLDER GAMEE)
