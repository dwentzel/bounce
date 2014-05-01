setup_module(logging)

set(HEADERS
    ${MODULE_PUBLIC_INCLUDE_DIR}/DefaultLogger.hpp
    ${MODULE_PUBLIC_INCLUDE_DIR}/LogManager.hpp
    ${MODULE_PUBLIC_INCLUDE_DIR}/Logger.hpp
    ${MODULE_PUBLIC_INCLUDE_DIR}/LogManager.hpp
    ${MODULE_PUBLIC_INCLUDE_DIR}/log.hpp)

set(SOURCES
    src/LogManager.cpp)

add_library(
    ${MODULE_NAME}
    SHARED
    ${HEADERS}
    ${SOURCES})
