setup_module(engine)

set(HEADERS
    ${MODULE_PUBLIC_INCLUDE_DIR}/ai_component.h
    ${MODULE_PUBLIC_INCLUDE_DIR}/ai_strategy.h
    ${MODULE_PUBLIC_INCLUDE_DIR}/ai_orbit_strategy.h
    ${MODULE_PUBLIC_INCLUDE_DIR}/application_context.h
    ${MODULE_PUBLIC_INCLUDE_DIR}/body_component.h
    ${MODULE_PUBLIC_INCLUDE_DIR}/bounce_main.h
    include/console.h
    ${MODULE_PUBLIC_INCLUDE_DIR}/camera_component.h
    ${MODULE_PUBLIC_INCLUDE_DIR}/control_component.h
    ${MODULE_PUBLIC_INCLUDE_DIR}/entity_manager.h
    ${MODULE_PUBLIC_INCLUDE_DIR}/event.h
    ${MODULE_PUBLIC_INCLUDE_DIR}/event_manager.h
    ${MODULE_PUBLIC_INCLUDE_DIR}/exceptions.h
    ${MODULE_PUBLIC_INCLUDE_DIR}/game_component.h
    ${MODULE_PUBLIC_INCLUDE_DIR}/game_component_manager.h
    ${MODULE_PUBLIC_INCLUDE_DIR}/game_component_type.h
    ${MODULE_PUBLIC_INCLUDE_DIR}/game_entity.h
    ${MODULE_PUBLIC_INCLUDE_DIR}/game_entity_manager.h
    ${MODULE_PUBLIC_INCLUDE_DIR}/game_system.h
    ${MODULE_PUBLIC_INCLUDE_DIR}/input_system.h
    ${MODULE_PUBLIC_INCLUDE_DIR}/keyboard_state.h
    ${MODULE_PUBLIC_INCLUDE_DIR}/keys.h
    ${MODULE_PUBLIC_INCLUDE_DIR}/message.h
    ${MODULE_PUBLIC_INCLUDE_DIR}/movement_system.h
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
    src/camera_component.cc
    src/control_component.cc
    src/entity_manager.cc
    src/event.cc
    src/event_manager.cc
    src/exceptions.cc
    src/game_component.cc
    src/game_component_manager.cc
    src/game_entity.cc
    src/game_entity_manager.cc
    src/game_system.cc
    src/input_system.cc
    src/keyboard_state.cc
    src/message.cc
    src/movement_system.cc
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
    ${SOURCES}
	$<TARGET_OBJECTS:importer>
	$<TARGET_OBJECTS:framework>
	$<TARGET_OBJECTS:logging>
	$<TARGET_OBJECTS:renderer>)

if (XCODE)
    setup_xcode(${MODULE_NAME})
endif (XCODE)

find_package(GLEW REQUIRED)
target_link_libraries(${MODULE_NAME} ${GLEW_LIBRARY})

find_package(OPENGL REQUIRED)
target_link_libraries(${MODULE_NAME} ${OPENGL_LIBRARIES})

find_package(ASSIMP REQUIRED)
target_link_libraries(${MODULE_NAME} ${ASSIMP_LIBRARIES})

find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIR})

include_directories("${Bounce_SOURCE_DIR}/external/glm")


###########################################################
# Tests

#set(TEST_SOURCES
#    test/event_manager_test.cc
#    test/keyboard_state_test.cc
#)

#setup_testing()
