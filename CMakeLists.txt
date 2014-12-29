cmake_minimum_required(VERSION 2.8.12)
project(Bounce)

#set(BUILD_SHARED_LIBS OFF)
message(STATUS "CMAKE_SYSTEM: ${CMAKE_SYSTEM}")
message(STATUS "CMAKE_PREFIX_PATH: $ENV{CMAKE_PREFIX_PATH}")

#eclipse invocation
# -DCMAKE_ECLIPSE_VERSION=4.4 -DCMAKE_CXX_STANDARD=11 -DCMAKE_CXX_COMPILER_ARG1=-std=c++11 -DCMAKE_ECLIPSE_GENERATE_SOURCE_PROJECT=TRUE

#message(STATUS "Library prefixes: ${CMAKE_FIND_LIBRARY_PREFIXES}")
#message(STATUS "Library suffixes: ${CMAKE_FIND_LIBRARY_SUFFIXES}")

message(STATUS "Generator: ${CMAKE_GENERATOR}")

if (${CMAKE_EXTRA_GENERATOR} MATCHES "Eclipse CDT4")
	message(STATUS "Eclipse CDT4")
endif (${CMAKE_EXTRA_GENERATOR} MATCHES "Eclipse CDT4")


if (APPLE)
    set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${Bounce_SOURCE_DIR}/cmake/modules/osx")
endif (APPLE)
if (WIN32)
    set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${Bounce_SOURCE_DIR}/cmake/modules/win")
endif (WIN32)
message(STATUS "CMAKE_MODULE_PATH=${CMAKE_MODULE_PATH}")

set(gtest_force_shared_crt ON)

set(PUBLIC_INCLUDE_DIR ${Bounce_SOURCE_DIR}/headers)

set(CLANG_WARNINGS "-Wall -Wextra -Weverything -Wno-c++98-compat -Wno-padded")

macro(set_xcode_property TARGET XCODE_PROPERTY XCODE_VALUE)
    set_property (TARGET ${TARGET} PROPERTY XCODE_ATTRIBUTE_${XCODE_PROPERTY} ${XCODE_VALUE})
endmacro(set_xcode_property)

macro(setup_xcode TARGET)
    set_xcode_property(${TARGET} CLANG_CXX_LANGUAGE_STANDARD "c++11")
    set_xcode_property(${TARGET} CLANG_CXX_LIBRARY "libc++")
    set_xcode_property(${TARGET} WARNING_CFLAGS ${CLANG_WARNINGS})

    set_xcode_property(${TARGET} CLANG_WARN_BOOL_CONVERSION YES)
    set_xcode_property(${TARGET} CLANG_WARN_CONSTANT_CONVERSION YES)
    set_xcode_property(${TARGET} CLANG_WARN_EMPTY_BODY YES)
    set_xcode_property(${TARGET} CLANG_WARN_ENUM_CONVERSION YES)
    set_xcode_property(${TARGET} CLANG_WARN_IMPLICIT_SIGN_CONVERSION YES)
    set_xcode_property(${TARGET} CLANG_WARN_INT_CONVERSION YES)
    set_xcode_property(${TARGET} CLANG_WARN_SUSPICIOUS_IMPLICIT_CONVERSION YES)
    set_xcode_property(${TARGET} GCC_WARN_64_TO_32_BIT_CONVERSION YES)
    set_xcode_property(${TARGET} GCC_WARN_ABOUT_MISSING_FIELD_INITIALIZERS YES)
    set_xcode_property(${TARGET} GCC_WARN_ABOUT_MISSING_NEWLINE YES)
    set_xcode_property(${TARGET} GCC_WARN_ABOUT_RETURN_TYPE YES)
    set_xcode_property(${TARGET} GCC_WARN_HIDDEN_VIRTUAL_FUNCTIONS YES)
    set_xcode_property(${TARGET} GCC_WARN_INITIALIZER_NOT_FULLY_BRACKETED YES)
    set_xcode_property(${TARGET} GCC_WARN_NON_VIRTUAL_DESTRUCTOR YES)
    set_xcode_property(${TARGET} GCC_WARN_SIGN_COMPARE YES)
    set_xcode_property(${TARGET} GCC_WARN_UNINITIALIZED_AUTOS YES)
    set_xcode_property(${TARGET} GCC_WARN_UNUSED_FUNCTION YES)
    set_xcode_property(${TARGET} GCC_WARN_UNUSED_LABEL YES)
    set_xcode_property(${TARGET} GCC_WARN_UNUSED_PARAMETER YES)
    set_xcode_property(${TARGET} GCC_WARN_UNUSED_VALUE YES)
    set_xcode_property(${TARGET} GCC_WARN_UNUSED_VARIABLE YES)
endmacro(setup_xcode)

macro(setup_compiler TARGET)
	if (XCODE)
    	setup_xcode(${TARGET})
	elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
		set_target_properties(${TARGET} PROPERTIES COMPILE_FLAGS ${CLANG_WARNINGS})
	endif (XCODE)
endmacro(setup_compiler)

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

#set_property(GLOBAL PROPERTY USE_FOLDERS ON)
#set_property(TARGET game PROPERTY FOLDER GAMEE)
