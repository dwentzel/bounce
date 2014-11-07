setup_module(framework)

set(HEADERS
    ${MODULE_PUBLIC_INCLUDE_DIR}/lock_free_queue.h
    ${MODULE_PUBLIC_INCLUDE_DIR}/renderer.h
    ${MODULE_PUBLIC_INCLUDE_DIR}/timer.h
)

set(SOURCES
    src/framework.cc
    src/renderer.cc
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

#set(TEST_EXE_NAME framework_unit_tests)

#add_executable(${TEST_EXE_NAME}
#    test/lock_free_queue_test.cc
#)

#target_include_directories(
#    ${TEST_EXE_NAME} PRIVATE
#    ${gtest_SOURCE_DIR}/include
#    ${gtest_SOURCE_DIR})

#target_link_libraries(${TEST_EXE_NAME} ${MODULE_NAME})
#target_link_libraries(${TEST_EXE_NAME} gtest gtest_main)

#add_test(${TEST_EXE_NAME} ${TEST_EXE_NAME})