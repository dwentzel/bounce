project(BounceMac)

set(EXENAME bounce_mac)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ObjC++")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -ObjC++")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -ObjC++")

find_library(COCOA_LIBRARY Cocoa)

set(SOURCES
    main.mm
    AppDelegate.h
    AppDelegate.mm
    GameView.h
    GameView.mm
    MacEventManager.h
    MacEventManager.cpp)

add_executable(${EXENAME} ${SOURCES})

source_group(\\ FILES ${SOURCES})

link_directories(${PROJECT_BINARY_DIR}/bounce)

target_link_libraries(${EXENAME} ${COCOA_LIBRARY} bounce)

file(GLOB ShellScript ${PROJECT_SOURCE_DIR}/bounce.sh)
add_custom_target(copy ALL)
add_custom_command(TARGET copy POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E
        copy "${PROJECT_SOURCE_DIR}/bounce.sh" "$<TARGET_FILE_DIR:bounce_mac>")
