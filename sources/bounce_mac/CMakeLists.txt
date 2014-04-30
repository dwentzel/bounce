set(EXENAME bounce_mac)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ObjC++")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -ObjC++")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -ObjC++")

set(MODULE_PUBLIC_INCLUDE_DIR ${PUBLIC_INCLUDE_DIR}/${LIBNAME})

include_directories(
    ${PUBLIC_INCLUDE_DIR}
    ${MODULE_PUBLIC_INCLUDE_DIR}
    include)

set(HEADERS
    include/AppDelegate.h
    include/GameView.h
    include/MacEventManager.hpp)

set(SOURCES
    src/main.mm
    src/AppDelegate.mm
    src/GameView.mm
    src/MacEventManager.cpp)

add_executable(
    ${EXENAME}
    ${HEADERS}
    ${SOURCES})

#source_group(\\ FILES ${SOURCES})

#link_directories(${PROJECT_BINARY_DIR}/bounce)

find_library(COCOA_LIBRARY Cocoa)


target_link_libraries(${EXENAME} ${COCOA_LIBRARY} bounce)

file(GLOB ShellScript ${PROJECT_SOURCE_DIR}/bounce.sh)
add_custom_target(copy ALL)
add_custom_command(TARGET copy POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E
        copy "${CMAKE_CURRENT_SOURCE_DIR}/bounce.sh" "$<TARGET_FILE_DIR:bounce_mac>")
