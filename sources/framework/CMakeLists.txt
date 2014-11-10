setup_module(framework)

set(HEADERS
    ${MODULE_PUBLIC_INCLUDE_DIR}/lock_free_queue.h
    ${MODULE_PUBLIC_INCLUDE_DIR}/renderer.h
    ${MODULE_PUBLIC_INCLUDE_DIR}/resource_loader.h
    ${MODULE_PUBLIC_INCLUDE_DIR}/timer.h
)

set(SOURCES
    src/framework.cc
    src/renderer.cc
    src/resource_loader.cc
)

add_library(
    ${MODULE_NAME}
    STATIC
    ${HEADERS}
    ${SOURCES}
)

###########################################################
# Tests

set(TEST_HEADERS
)

set(TEST_SOURCES
    test/lock_free_queue_test.cc
)

setup_testing(framework)
