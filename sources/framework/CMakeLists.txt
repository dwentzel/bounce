setup_module(framework)

set(HEADERS
    ${MODULE_PUBLIC_INCLUDE_DIR}/assertions.h
    ${MODULE_PUBLIC_INCLUDE_DIR}/contracts.h
    ${MODULE_PUBLIC_INCLUDE_DIR}/exceptions.h
    ${MODULE_PUBLIC_INCLUDE_DIR}/image_data.h
    ${MODULE_PUBLIC_INCLUDE_DIR}/lock_free_queue.h
    ${MODULE_PUBLIC_INCLUDE_DIR}/object_cache.h
    ${MODULE_PUBLIC_INCLUDE_DIR}/object_cache_handle.h
    ${MODULE_PUBLIC_INCLUDE_DIR}/renderer.h
    ${MODULE_PUBLIC_INCLUDE_DIR}/resource_loader.h
    ${MODULE_PUBLIC_INCLUDE_DIR}/timer.h
)

set(SOURCES
    src/contracts.cc
    src/exceptions.cc
    src/framework.cc
    src/image_data.cc
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

setup_compiler(${MODULE_NAME})

###########################################################
# Tests

set(TEST_HEADERS
)

set(TEST_SOURCES
    test/assertions_test.cc
    test/composite_cache_test.cc
    test/contracts_test.cc
    test/lock_free_queue_test.cc
    test/main.cc
)

set(TEST_EXE_NAME ${MODULE_NAME}_unit_tests)

add_executable(
    ${TEST_EXE_NAME}
    ${TEST_HEADERS}
    ${TEST_SOURCES}
    $<TARGET_OBJECTS:logging>
    $<TARGET_OBJECTS:${MODULE_NAME}>
)

if (XCODE)
    setup_xcode(${TEST_EXE_NAME})
endif (XCODE)

target_include_directories(
    ${TEST_EXE_NAME} PRIVATE
	${PUBLIC_INCLUDE_DIR}
    ${gtest_SOURCE_DIR}/include
    ${gtest_SOURCE_DIR}
)

target_link_libraries(${TEST_EXE_NAME} gtest)

add_test(${TEST_EXE_NAME} ${TEST_EXE_NAME})

#setup_testing(framework)
