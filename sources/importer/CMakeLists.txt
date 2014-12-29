setup_module(importer)

set(HEADERS
    ${MODULE_PUBLIC_INCLUDE_DIR}/exceptions.h
    ${MODULE_PUBLIC_INCLUDE_DIR}/imported_model.h
    ${MODULE_PUBLIC_INCLUDE_DIR}/imported_material.h
    ${MODULE_PUBLIC_INCLUDE_DIR}/importer.h
)

set(SOURCES
    src/exceptions.cc
    src/imported_model.cc
    src/imported_material.cc
    src/importer.cc
)

add_library(
    ${MODULE_NAME}
    OBJECT
    ${HEADERS}
    ${SOURCES}
)

setup_compiler(${MODULE_NAME})

find_package(ASSIMP REQUIRED)
include_directories(${ASSIMP_INCLUDE_DIR})

find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIR})
