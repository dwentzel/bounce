#include <windows.h>

#include "logging\log.h"
//#include "logging\DefaultLogger.hpp"
#include "debug_logger.h"

#include "windows_application_context.h"
#include "controller.h"
#include "window.h"
#include "gl_context.h"

#include "engine/bounce_main.h"

extern int bounce_main(bounce::ApplicationContext*);

int WINAPI WinMain(
    HINSTANCE hInstance,
    HINSTANCE hPreviousInst,
    LPSTR lpCmdLine,
    int nCmdShow)
{


    bounce::LogManager::instance().Startup();

    LOG_DEBUG << "STARTED" << std::endl;

    bounce_win::WindowsApplicationContext context(hInstance);

    bounce_main(&context);

    //bounce_win::GLContext* context = new bounce_win::GLContext();
    //bounce_win::Controller* controller = new bounce_win::Controller(context);
    //
    //bounce_win::Window window(hInstance, L"Bounce", 0, controller);

    //HWND w = window.create();
    //window.show();

    //MSG msg;
    
    //while (GetMessage(&msg, NULL, 0, 0) == TRUE) {
    //    TranslateMessage(&msg);
    //    DispatchMessage(&msg);
    //}

    bounce::LogManager::instance().Shutdown();

    return 0;
}

