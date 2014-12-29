message(STATUS "Setting up game")
set(MODULE_NAME game)

include_directories(
	${PUBLIC_INCLUDE_DIR}
    include)

set(HEADERS
    include/app.h
)

set(SOURCES
    src/app.cc
    src/bounce.cc
)

set(shaders_PATH ${PROJECT_SOURCE_DIR}/resources/shaders)
set(models_PATH ${PROJECT_SOURCE_DIR}/resources/models)
set(textures_PATH ${PROJECT_SOURCE_DIR}/resources/textures)


set(MODELS
    ${models_PATH}/quad.dae
    ${models_PATH}/simple_craft.dae
    ${models_PATH}/sphere.dae
)

set(TEXTURES
    ${textures_PATH}/Hull_Texture.bmp
)

set(SHADERS
    ${shaders_PATH}/triangleShader.frag.glsl
    ${shaders_PATH}/triangleShader.vert.glsl
    ${shaders_PATH}/geometry_pass.frag.glsl
    ${shaders_PATH}/geometry_pass.vert.glsl
    ${shaders_PATH}/light_pass.vert.glsl
    ${shaders_PATH}/directional_light_pass.frag.glsl
    ${shaders_PATH}/point_light_pass.frag.glsl
)

set(RESOURCES
    ${RESOURCES}
)

if (APPLE)
    set(MACOSX_BUNDLE BUNDLE_NAME ${MODULE_NAME})

    add_executable(
        ${MODULE_NAME}
        MACOSX_BUNDLE
        ${HEADERS}
        ${SOURCES}
        ${MODELS}
        ${TEXTURES}
        ${SHADERS}
    )

    if (XCODE)
        setup_xcode(${MODULE_NAME})
    endif (XCODE)

    set_source_files_properties(
        ${MODELS}
        PROPERTIES
        MACOSX_PACKAGE_LOCATION Resources/models
    )

    set_source_files_properties(
        ${TEXTURES}
        PROPERTIES
        MACOSX_PACKAGE_LOCATION Resources/textures
    )

    set_source_files_properties(
        ${SHADERS}
        PROPERTIES
        MACOSX_PACKAGE_LOCATION Resources/shaders
    )

    source_group(Resources\\models FILES ${MODELS})
    source_group(Resources\\textures FILES ${TEXTURES})
    source_group(Resources\\shaders FILES ${SHADERS})



    set_target_properties(${MODULE_NAME} PROPERTIES MACOSX_BUNDLE TRUE)

    target_link_libraries(${MODULE_NAME} bounce_mac)
else (APPLE)

    add_executable(
        ${MODULE_NAME}
		WIN32
        ${HEADERS}
        ${SOURCES}
    )

	target_link_libraries(${MODULE_NAME} engine bounce_win)

    add_custom_command(TARGET ${MODULE_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E
            copy_directory "${PROJECT_SOURCE_DIR}/resources/shaders" "$<TARGET_FILE_DIR:game>/shaders")

    add_custom_command(TARGET ${MODULE_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E
            copy_directory "${PROJECT_SOURCE_DIR}/resources/models" "$<TARGET_FILE_DIR:game>/models")

	add_custom_command(TARGET ${MODULE_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E
            copy_directory "${PROJECT_SOURCE_DIR}/resources/textures" "$<TARGET_FILE_DIR:game>/textures")

endif (APPLE)

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

	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /DNOMINMAX")
	set_target_properties(${MODULE_NAME} PROPERTIES LINK_FLAGS "/NODEFAULTLIB:\"libcmt\"")

#	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /NODEFAULTLIB:libcmt")

elseif(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
    # Update if necessary
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-long-long -pedantic")
endif()

find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIR})
target_link_libraries(${MODULE_NAME} ${GLEW_LIBRARY})
include_directories("${Bounce_SOURCE_DIR}/external/glm")
