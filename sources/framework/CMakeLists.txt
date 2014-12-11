setup_module(framework)
include (GenerateExportHeader)
set(HEADERS
    ${MODULE_PUBLIC_INCLUDE_DIR}/exceptions.h
    ${MODULE_PUBLIC_INCLUDE_DIR}/lock_free_queue.h
    ${MODULE_PUBLIC_INCLUDE_DIR}/object_cache.h
    ${MODULE_PUBLIC_INCLUDE_DIR}/object_cache_handle.h
    ${MODULE_PUBLIC_INCLUDE_DIR}/renderer.h
    ${MODULE_PUBLIC_INCLUDE_DIR}/resource_loader.h
    ${MODULE_PUBLIC_INCLUDE_DIR}/timer.h
)

set(SOURCES
    src/exceptions.cc
    src/framework.cc
    src/object_cache.cc
    src/object_cache_handle.cc
    src/renderer.cc
    src/resource_loader.cc
)

add_library(
    ${MODULE_NAME}
    OBJECT
    ${HEADERS}
    ${SOURCES}
)

if (XCODE)
    setup_xcode(${MODULE_NAME})
endif (XCODE)

###########################################################
# Tests

#set(TEST_HEADERS
#)

#set(TEST_SOURCES
#    test/composite_cache_test.cc
#    test/lock_free_queue_test.cc
#)

#setup_testing(framework)
