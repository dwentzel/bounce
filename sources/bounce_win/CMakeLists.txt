setup_module(bounce_win)

add_definitions(-DUNICODE -D_UNICODE)

set(HEADERS
	include/controller.h
	${MODULE_PUBLIC_INCLUDE_DIR}/debug_string_output.h
	include/gl_context.h
	include/window.h
	include/window_procedure.h
	include/windows_application_context.h
)

set(SOURCES
	src/controller.cc
	src/debug_string_output.cc
	src/gl_context.cc
	src/window.cc
	src/main.cc
	src/window_procedure.cc
	src/windows_application_context.cc
)

add_library(
	${MODULE_NAME}
	STATIC
	${HEADERS}
	${SOURCES}
	)
	



target_link_libraries(${MODULE_NAME} engine)

