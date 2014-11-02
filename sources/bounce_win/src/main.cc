#include <windows.h>

#include "logging\log.h"
//#include "logging\DefaultLogger.hpp"
#include "debug_logger.h"

#include "controller.h"
#include "window.h"
#include "gl_context.h"

int WINAPI WinMain(
    HINSTANCE hInstance,
    HINSTANCE hPreviousInst,
    LPSTR lpCmdLine,
    int nCmdShow)
{
    MSG msg;

    bounce::Logger* logger = new bounce_win::DebugLogger();
    bounce::LogManager::instance().set_logger(logger);

    LOG(bounce::LogLevel::Debug) << "STARTED" << std::endl;

    bounce_win::GLContext* context = new bounce_win::GLContext();
    bounce_win::Controller* controller = new bounce_win::Controller(context);
    
    bounce_win::Window window(hInstance, L"Bounce", 0, controller);

    HWND w = window.create();
    window.show();
    
    while (GetMessage(&msg, NULL, 0, 0) == TRUE) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return msg.wParam;
}

