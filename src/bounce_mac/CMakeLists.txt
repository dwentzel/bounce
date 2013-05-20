set(EXENAME bounce_mac)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -ObjC++")

find_library(COCOA_LIBRARY Cocoa)
message(${COCOA_LIBRARY})

add_executable(${EXENAME} main.mm AppDelegate.mm GameView.mm
    MacEventManager.cpp)

find_package(sdl REQUIRED)
link_directories(${PROJECT_BINARY_DIR}/bounce ${SDL_LIBRARY/..})
message(${SDLMAIN_LIBRARY})
target_link_libraries(${EXENAME} ${COCOA_LIBRARY} bounce)
