cmake_minimum_required(VERSION 2.8.12)
project(Bounce)

#message(${CMAKE_GENERATOR})

#set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)
#set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
#set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

if (CMAKE_GENERATOR STREQUAL Xcode)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/build/Debug")
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/build/Release")

    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/build/Debug")
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/build/Release")

    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/build/Debug")
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/build/Release")
endif()


set(CMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LANGUAGE_STANDARD "c++11")
set(CMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LIBRARY "libc++")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11 -stdlib=libc++")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -std=c++11 -stdlib=libc++")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall -std=c++11 -stdlib=libc++")

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -stdlib=libc++")

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
