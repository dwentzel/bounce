#include "windows_application_context.h"

#include <windows.h>

#include "controller.h"
#include "window.h"
#include "gl_context.h"

bounce_win::WindowsApplicationContext::WindowsApplicationContext(HINSTANCE hInstance)
    : hInstance_(hInstance)
{

    HMODULE hModule = GetModuleHandleW(NULL);
    CHAR path[MAX_PATH];
    DWORD len = GetModuleFileNameA(hModule, path, MAX_PATH);

    std::string path_str(path);

    root_path_ = path_str.substr(0, len - 9);
}

void bounce_win::WindowsApplicationContext::Flush() const
{
    gl_context_->flush();
    Sleep(10);
}

void bounce_win::WindowsApplicationContext::Update() const
{
    MSG msg;

    if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) == TRUE) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

void bounce_win::WindowsApplicationContext::CreateApplicationWindow(const bounce::WindowContext& window_context)
{
    gl_context_ = new bounce_win::GLContext();
    
    bounce_win::Controller* controller = new bounce_win::Controller(gl_context_, *this);

    bounce_win::Window window(hInstance_, L"Bounce", 0, controller);

    HWND w = window.create();

    

    window.show();

    gl_context_->createContext(w, 32, 24, 8);
    ::wglMakeCurrent(gl_context_->getDC(), gl_context_->getRC());
}

const std::string& bounce_win::WindowsApplicationContext::root_path() const
{
    return root_path_;
}