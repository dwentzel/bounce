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

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${Bounce_SOURCE_DIR}/cmake/modules")
message(STATUS "CMAKE_MODULE_PATH=${CMAKE_MODULE_PATH}")


#set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)
#set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
#set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

set(gtest_force_shared_crt ON)

set(PUBLIC_INCLUDE_DIR ${Bounce_SOURCE_DIR}/headers)

macro(setup_module MODULE)
    set(MODULE_NAME ${MODULE})

    set(MODULE_PUBLIC_INCLUDE_DIR ${PUBLIC_INCLUDE_DIR}/${MODULE_NAME})

    include_directories(
        ${PUBLIC_INCLUDE_DIR}
        ${MODULE_PUBLIC_INCLUDE_DIR}
        include)
endmacro(setup_module)

enable_testing()

add_subdirectory(external)
add_subdirectory(sources)
add_subdirectory(resources)
