setup_module(bounce_win)

add_definitions(-DUNICODE -D_UNICODE)

set(HEADERS
	include/controller.h
	include/debug_logger.h
	include/gl_context.h
	include/window.h
	include/window_procedure.h
	include/windows_application_context.h
)

set(SOURCES
	src/controller.cc
	src/gl_context.cc
	src/window.cc
	src/main.cc
	src/window_procedure.cc
	src/windows_application_context.cc
)

add_executable(
	${MODULE_NAME}
	WIN32
	${HEADERS}
	${SOURCES})
	
target_link_libraries(${MODULE_NAME} bounce)


#file(GLOB ShellScript ${PROJECT_SOURCE_DIR}/bounce.sh)

#add_custom_command(TARGET ${MODULE_NAME} POST_BUILD
#    COMMAND ${CMAKE_COMMAND} -E
#        copy "${CMAKE_CURRENT_SOURCE_DIR}/bounce.sh" "$<TARGET_FILE_DIR:bounce_mac>")
		

add_custom_command(TARGET ${MODULE_NAME} POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E
		copy "${CMAKE_SOURCE_DIR}/external/glew-1.10.0/bin/Release/Win32/glew32.dll" "$<TARGET_FILE_DIR:bounce_win>")

add_custom_command(TARGET ${MODULE_NAME} POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E
		copy_directory "${PROJECT_SOURCE_DIR}/resources/shaders" "$<TARGET_FILE_DIR:bounce_win>/shaders")

add_custom_command(TARGET ${MODULE_NAME} POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E
		copy_directory "${PROJECT_SOURCE_DIR}/resources/models" "$<TARGET_FILE_DIR:bounce_win>/models")

