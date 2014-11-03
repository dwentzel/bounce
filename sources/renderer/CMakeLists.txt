setup_module(renderer)

set(HEADERS
    ${MODULE_PUBLIC_INCLUDE_DIR}/material.h
    ${MODULE_PUBLIC_INCLUDE_DIR}/material_manager.h
    ${MODULE_PUBLIC_INCLUDE_DIR}/model.h
    ${MODULE_PUBLIC_INCLUDE_DIR}/model_manager.h
    ${MODULE_PUBLIC_INCLUDE_DIR}/vertex_buffer.h
    include/renderer.h
)

set(SOURCES
    src/model.cc
    src/model_manager.cc
    src/renderer.cc
    src/vertex_buffer.cc
)

add_library(
    ${MODULE_NAME}
    STATIC
    ${HEADERS}
    ${SOURCES}
)