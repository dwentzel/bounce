#include <windows.h>

#include "logging\log.hpp"
//#include "logging\DefaultLogger.hpp"
#include "DebugLogger.hpp"

#include "Controller.hpp"
#include "Window.hpp"
#include "GLContext.hpp"

void flush(void* context) {
    bounce_win::GLContext* glContext = (bounce_win::GLContext*)context;

    ::SwapBuffers(glContext->getDC());
}

int WINAPI WinMain(
    HINSTANCE hInstance,
    HINSTANCE hPreviousInst,
    LPSTR lpCmdLine,
    int nCmdShow)
{
    MSG msg;

    bounce::Logger* logger = new bounce_win::DebugLogger();
    bounce::LogManager::getInstance().setLogger(logger);

    LOG(bounce::LogLevel::Debug) << "STARTED";

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

