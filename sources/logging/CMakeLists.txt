setup_module(logging)

set(HEADERS
    ${MODULE_PUBLIC_INCLUDE_DIR}/default_logger.h
    ${MODULE_PUBLIC_INCLUDE_DIR}/log_manager.h
    ${MODULE_PUBLIC_INCLUDE_DIR}/logger.h
    ${MODULE_PUBLIC_INCLUDE_DIR}/log_manager.h
    ${MODULE_PUBLIC_INCLUDE_DIR}/log.h)

set(SOURCES
    src/log_manager.cc)

add_library(
    ${MODULE_NAME}
    STATIC
    ${HEADERS}
    ${SOURCES})
