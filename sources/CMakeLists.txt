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
#    set(CMAKE_CXX_FLAGS "-std=c++11 -stdlib=libc++ -Wall -Wextra -Weverything -Wno-c++98-compat")
#	set(CMAKE_CXX_FLAGS "-std=c++11 -stdlib=libc++ -Wall -Wno-c++98-compat")

	set(CMAKE_CXX_FLAGS "-std=c++11 -stdlib=libc++")

#    set(CMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LANGUAGE_STANDARD "c++11")
#    set(CMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LIBRARY "libc++")
#    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -stdlib=libc++")
endif()

if(MSVC)
    # Force to always compile with W4
    if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
        string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    else()
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
    endif()

	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /DNOMINMAX")
elseif(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
    # Update if necessary
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-long-long -pedantic")
endif()

message(STATUS "CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS}")
message(STATUS "CMAKE_CXX_FLAGS_DEBUG ${CMAKE_CXX_FLAGS_DEBUG}")
message(STATUS "CMAKE_CXX_FLAGS_RELEASE ${CMAKE_CXX_FLAGS_RELEASE}")

add_subdirectory(framework)
add_subdirectory(logging)
add_subdirectory(renderer)
#add_subdirectory(renderer_test)
add_subdirectory(importer)
add_subdirectory(engine)
    
if (WIN32)
    add_subdirectory(bounce_win)
elseif (APPLE)
    add_subdirectory(bounce_mac)
endif()

set(HEADERS
    ${PUBLIC_INCLUDE_DIR}/bounce.h
    ${PUBLIC_INCLUDE_DIR}/contrib/assimp.h
    ${PUBLIC_INCLUDE_DIR}/contrib/disable_clang_warnings.h
    ${PUBLIC_INCLUDE_DIR}/contrib/enable_clang_warnings.h
)

add_custom_target(bounce_lib SOURCES ${HEADERS})