#include <windows.h>

#include "logging\log.h"

#include "windows_application_context.h"
#include "controller.h"
#include "window.h"
#include "gl_context.h"
#include "debug_string_output.h"

#include "engine/bounce_main.h"

extern int bounce_main(bounce::ApplicationContext*);

int WINAPI WinMain(
    HINSTANCE hInstance,
    HINSTANCE hPreviousInst,
    LPSTR lpCmdLine,
    int nCmdShow)
{
    std::unique_ptr<bounce_win::DebugStringOutput> log_output(new bounce_win::DebugStringOutput());

    bounce::LogManager::instance().Startup();
    bounce::LogManager::instance().AddOutput(std::move(log_output));

    LOG_DEBUG << "STARTED" << std::endl;

    bounce_win::WindowsApplicationContext context(hInstance);

    bounce_main(&context);

    bounce::LogManager::instance().Shutdown();

    return 0;
}

