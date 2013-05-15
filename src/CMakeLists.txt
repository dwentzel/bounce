cmake_minimum_required(VERSION 2.8)
project(BounceProject)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -std=c++11 -stdlib=libc++")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall -std=c++11 -stdlib=libc++")

add_subdirectory(bounce)
add_subdirectory(ui)
