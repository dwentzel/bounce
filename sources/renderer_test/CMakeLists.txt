setup_module(renderer_test)

set(HEADERS
    include/renderer_test.h
)

set(SOURCES
    src/renderer_test.cc
)

add_executable(
    renderer_test
    ${HEADERS}
    ${SOURCES}
)

find_package(GLFW REQUIRED)
include_directories(${GLFW_INCLUDE_DIR})
target_link_libraries(renderer_test ${GLFW_LIBRARY})

include_directories(${GLEW_INCLUDE_DIR})
include_directories("${Bounce_SOURCE_DIR}/external/glm")

target_link_libraries(renderer_test renderer logging)