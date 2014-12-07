setup_module(logging)

set(HEADERS
    ${MODULE_PUBLIC_INCLUDE_DIR}/log.h
    ${MODULE_PUBLIC_INCLUDE_DIR}/log_manager.h
    ${MODULE_PUBLIC_INCLUDE_DIR}/log_message.h
    ${MODULE_PUBLIC_INCLUDE_DIR}/log_output.h
    ${MODULE_PUBLIC_INCLUDE_DIR}/log_stream_buffer.h
    ${MODULE_PUBLIC_INCLUDE_DIR}/log_sync.h
    ${MODULE_PUBLIC_INCLUDE_DIR}/log_worker.h
    include/stdout_log_output.h
    include/file_log_output.h
)

set(SOURCES
    src/log.cc
    src/log_manager.cc
    src/log_output.cc
    src/log_stream_buffer.cc
    src/log_sync.cc
    src/log_worker.cc
    src/stdout_log_output.cc
    src/file_log_output.cc
)

add_library(
    ${MODULE_NAME}
    OBJECT
    ${HEADERS}
    ${SOURCES}
)
