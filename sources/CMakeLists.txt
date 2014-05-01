add_subdirectory(logging)
add_subdirectory(bounce)

if (APPLE)
    add_subdirectory(bounce_mac)
endif()