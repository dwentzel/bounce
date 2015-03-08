setup_module(logging)

set(HEADERS
    ${MODULE_PUBLIC_INCLUDE_DIR}/default_log_manager.h
    include/file_log_output.h
    ${MODULE_PUBLIC_INCLUDE_DIR}/log.h
    ${MODULE_PUBLIC_INCLUDE_DIR}/log_facade.h
    ${MODULE_PUBLIC_INCLUDE_DIR}/log_level.h
    ${MODULE_PUBLIC_INCLUDE_DIR}/log_manager.h
    ${MODULE_PUBLIC_INCLUDE_DIR}/log_message.h
    ${MODULE_PUBLIC_INCLUDE_DIR}/log_output.h
    include/log_stream_buffer.h
    ${MODULE_PUBLIC_INCLUDE_DIR}/log_sync.h
    include/log_worker.h
    ${MODULE_PUBLIC_INCLUDE_DIR}/null_log_manager.h
)

set(SOURCES
    src/default_log_manager.cc
    src/file_log_output.cc
    src/log.cc
    src/log_facade.cc
    src/log_level.cc
    src/log_manager.cc
    src/log_message.cc
    src/log_output.cc
    src/log_stream_buffer.cc
    src/log_sync.cc
    src/log_worker.cc
    src/null_log_manager.cc
)

add_library(
    ${MODULE_NAME}
    OBJECT
    ${HEADERS}
    ${SOURCES}
)

setup_compiler(${MODULE_NAME})
