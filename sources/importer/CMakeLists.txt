setup_module(importer)

set(HEADERS
    ${MODULE_PUBLIC_INCLUDE_DIR}/importer.h
#    include/vertex_buffer.h
)

set(SOURCES
    src/importer.cc
#    src/vertex_buffer.cc
)

add_library(
    ${MODULE_NAME}
    STATIC
    ${HEADERS}
    ${SOURCES}
)

find_package(ASSIMP REQUIRED)
if (ASSIMP_FOUND)
#   message("assimp_DIR: ${assimp_DIR}")

    message("ASSIMP_INCLUDE_DIR: ${ASSIMP_INCLUDE_DIR}")
    include_directories(${ASSIMP_INCLUDE_DIR})

    message("ASSIMP_LIBRARIES: ${ASSIMP_LIBRARIES}")

#    if (APPLE)
#        target_link_libraries(${MODULE_NAME} /usr/local/lib/lib${ASSIMP_LIBRARIES}.dylib)
#    else (APPLE)
        target_link_libraries(${MODULE_NAME} ${ASSIMP_LIBRARIES})
#    endif (APPLE)
else (ASSIMP_FOUND)
    message("Could not find assimp")
endif (ASSIMP_FOUND)

include_directories(${GLEW_INCLUDE_DIR})

target_link_libraries(${MODULE_NAME} logging renderer)
