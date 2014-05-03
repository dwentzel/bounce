setup_module(logging)

set(HEADERS
    ${MODULE_PUBLIC_INCLUDE_DIR}/DefaultLogger.hpp
    ${MODULE_PUBLIC_INCLUDE_DIR}/LogManager.hpp
    ${MODULE_PUBLIC_INCLUDE_DIR}/Logger.hpp
    ${MODULE_PUBLIC_INCLUDE_DIR}/LogManager.hpp
    ${MODULE_PUBLIC_INCLUDE_DIR}/log.hpp
    include/DllDefines.hpp)

set(SOURCES
    src/LogManager.cpp)

add_library(
    ${MODULE_NAME}
    STATIC
    ${HEADERS}
    ${SOURCES})
