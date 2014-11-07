setup_module(game)

set(HEADERS
    include/app.h
)

set(SOURCES
    src/app.cc
    src/bounce.cc
)

add_executable(
    ${MODULE_NAME}
    ${HEADERS}
    ${SOURCES}
)

target_link_libraries(${MODULE_NAME} bounce_mac renderer)

if (CMAKE_GENERATOR STREQUAL Xcode)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/build/Debug")
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/build/Release")

    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/build/Debug")
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/build/Release")

    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/build/Debug")
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/build/Release")
elseif(MSVC)
    #set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/bin/Debug")
    #set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/bin/Release")

    #set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/bin/Debug")
    #set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/bin/Release")

    #set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/bin/Debug")
    #set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/bin/Release")
endif()

if (APPLE)
    set(CMAKE_CXX_FLAGS "-std=c++11 -stdlib=libc++")

    set(CMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LANGUAGE_STANDARD "c++11")
    set(CMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LIBRARY "libc++")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -stdlib=libc++")
endif()

if(MSVC)
    # Force to always compile with W4
    if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
        string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    else()
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
    endif()
    elseif(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
    # Update if necessary
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-long-long -pedantic")
endif()

include_directories(${GLEW_INCLUDE_DIR})
include_directories("${Bounce_SOURCE_DIR}/external/glm")

add_custom_command(TARGET ${MODULE_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E
        copy_directory "${PROJECT_SOURCE_DIR}/resources/shaders" "$<TARGET_FILE_DIR:game>/shaders")

add_custom_command(TARGET ${MODULE_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E
        copy_directory "${PROJECT_SOURCE_DIR}/resources/models" "$<TARGET_FILE_DIR:game>/models")