setup_module(logging)

set(HEADERS
#    ${MODULE_PUBLIC_INCLUDE_DIR}/default_logger.h
    ${MODULE_PUBLIC_INCLUDE_DIR}/log_manager.h
#    ${MODULE_PUBLIC_INCLUDE_DIR}/logger.h
    ${MODULE_PUBLIC_INCLUDE_DIR}/log_manager.h
    ${MODULE_PUBLIC_INCLUDE_DIR}/log.h
    ${MODULE_PUBLIC_INCLUDE_DIR}/log_output.h
    ${MODULE_PUBLIC_INCLUDE_DIR}/log_stream.h
    ${MODULE_PUBLIC_INCLUDE_DIR}/log_stream_buffer.h
    include/stdout_log_output.h
)

set(SOURCES
    src/log_manager.cc
    src/log_output.cc
    src/log_stream.cc
    src/log_stream_buffer.cc
    src/log_target.cc
    src/stdout_log_output.cc
)

add_library(
    ${MODULE_NAME}
    STATIC
    ${HEADERS}
    ${SOURCES}
)
