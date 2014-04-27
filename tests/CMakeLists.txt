add_subdirectory(lib/gtest-1.7.0)

include_directories(${CMAKE_SOURCE_DIR}/src/bounce ${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(unit_tests 
    main.cpp
    framework/LockFreeQueueTest.cpp
    KeyboardStateTest.cpp)

target_link_libraries(unit_tests bounce)
target_link_libraries(unit_tests gtest gtest_main)

add_test(NAME test1 COMMAND unit_tests)
