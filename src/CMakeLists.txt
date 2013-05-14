cmake_minimum_required(VERSION 2.8)
project(BounceProject)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall")

add_subdirectory(bounce)
add_subdirectory(ui)
