cmake_minimum_required(VERSION 2.8.12)
project(Bounce)

set(BUILD_SHARED_LIBS OFF)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules/")

message(${CMAKE_GENERATOR})

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
