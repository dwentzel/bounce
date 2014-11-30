setup_module(bounce)

set(HEADERS
    ${MODULE_PUBLIC_INCLUDE_DIR}/ai_component.h
    ${MODULE_PUBLIC_INCLUDE_DIR}/ai_strategy.h
    ${MODULE_PUBLIC_INCLUDE_DIR}/ai_orbit_strategy.h
    ${MODULE_PUBLIC_INCLUDE_DIR}/application_context.h
    ${MODULE_PUBLIC_INCLUDE_DIR}/body_component.h
    ${MODULE_PUBLIC_INCLUDE_DIR}/bounce_main.h
    include/console.h
    ${MODULE_PUBLIC_INCLUDE_DIR}/control_component.h
    ${MODULE_PUBLIC_INCLUDE_DIR}/event.h
    ${MODULE_PUBLIC_INCLUDE_DIR}/game_component.h
    ${MODULE_PUBLIC_INCLUDE_DIR}/game_component_type.h
    ${MODULE_PUBLIC_INCLUDE_DIR}/game_entity.h
    ${MODULE_PUBLIC_INCLUDE_DIR}/game_system.h
    ${MODULE_PUBLIC_INCLUDE_DIR}/input_system.h
    ${MODULE_PUBLIC_INCLUDE_DIR}/keyboard_state.h
    ${MODULE_PUBLIC_INCLUDE_DIR}/keys.h
    ${MODULE_PUBLIC_INCLUDE_DIR}/message.h
    ${MODULE_PUBLIC_INCLUDE_DIR}/movement_system.h
    ${MODULE_PUBLIC_INCLUDE_DIR}/object_manager.h
    ${MODULE_PUBLIC_INCLUDE_DIR}/object_manager_handle.h
    ${MODULE_PUBLIC_INCLUDE_DIR}/point_light_component.h
    ${MODULE_PUBLIC_INCLUDE_DIR}/render_component.h
    ${MODULE_PUBLIC_INCLUDE_DIR}/render_system.h
    ${MODULE_PUBLIC_INCLUDE_DIR}/window_context.h
)

set(SOURCES
    src/ai_component.cc
    src/ai_strategy.cc
    src/ai_orbit_strategy.cc
    src/application_context.cc
    src/body_component.cc
    src/console.cc
    src/control_component.cc
    src/event.cc
    src/game_component.cc
    src/game_entity.cc
    src/game_system.cc
    src/input_system.cc
    src/keyboard_state.cc
    src/message.cc
    src/movement_system.cc
    src/object_manager.cc
    src/object_manager_handle.cc
    src/point_light_component.cc
    src/render_component.cc
    src/render_system.cc
    src/window_context.cc
)

add_library(
    ${MODULE_NAME}
    STATIC
    ${HEADERS}
    ${SOURCES})

if (MSVC)
	set(GLEW_ROOT_DIR "${Bounce_SOURCE_DIR}/external/glew-1.10.0")
	set(GLEW_INCLUDE_DIR "${GLEW_ROOT_DIR}/include")
	set(GLEW_LIBRARY "${GLEW_ROOT_DIR}/lib/Release/Win32/glew32.lib")
endif()

#find_package(GLEW REQUIRED)
#if (GLEW_FOUND)
#    message("GLEW_INCLUDE_DIR: ${GLEW_INCLUDE_DIR}")
#    message("GLEW_LIBRARIES: ${GLEW_LIBRARIES}")
    include_directories(${GLEW_INCLUDE_DIR})
#    target_link_libraries(${MODULE_NAME} ${GLEW_LIBRARIES})
#endif (GLEW_FOUND)

#find_package(OPENGL REQUIRED)
#if (OPENGL_FOUND)
#    message("OPENGL_INCLUDE_DIR: ${OPENGL_INCLUDE_DIR}")
#    message("OPENGL_LIBRARIES: ${OPENGL_LIBRARIES}")
#    include_directories(${OPENGL_INCLUDE_DIR})
#    target_link_libraries(${MODULE_NAME} ${OPENGL_LIBRARIES})
#endif (OPENGL_FOUND)

include_directories("${Bounce_SOURCE_DIR}/external/glm")

target_link_libraries(${MODULE_NAME} logging importer renderer)

###########################################################
# Tests

set(TEST_SOURCES
    test/event_manager_test.cc
    test/keyboard_state_test.cc
)

setup_testing()
