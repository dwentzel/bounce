set(LIBNAME logging)

set(MODULE_PUBLIC_INCLUDE_DIR ${PUBLIC_INCLUDE_DIR}/${LIBNAME})

include_directories(
    ${PUBLIC_INCLUDE_DIR}
    ${MODULE_PUBLIC_INCLUDE_DIR}
    include)

include_directories(${Bounce_SOURCES}/headers include)

set(SOURCES
    src/LogManager.cpp)

add_library(
    ${LIBNAME}
    SHARED
    ${SOURCES})
