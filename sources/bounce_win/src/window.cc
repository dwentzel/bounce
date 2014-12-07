#include "window.h"
#include "window_procedure.h"

namespace bounce_win {

    Window::Window(HINSTANCE hInst, const wchar_t* name, HWND hParent, Controller* ctrl, const bounce::WindowContext& window_context)
        : controller(ctrl), window(0), instance(hInst), winStyle(WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN),
        winStyleEx(WS_EX_CLIENTEDGE), posX(CW_USEDEFAULT), posY(CW_USEDEFAULT),
        width(window_context.width()), height(window_context.height()), parent(hParent), menu(0)
    {
        wcsncpy_s(this->title, name, MAX_STRING - 1);
        wcsncpy_s(this->className, name, MAX_STRING - 1);

        wcex.cbSize = sizeof(WNDCLASSEX);
        wcex.style = winStyleEx;//CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
        wcex.lpfnWndProc = bounce_win::WndProc;
        wcex.cbClsExtra = 0;
        wcex.cbWndExtra = 0;
        wcex.hInstance = instance;
        wcex.hIcon = ::LoadIcon(instance, MAKEINTRESOURCE(IDI_APPLICATION));
        wcex.hCursor = ::LoadCursor(0, IDC_ARROW);
        //wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
        wcex.hbrBackground = 0;
        wcex.lpszMenuName = 0;
        wcex.lpszClassName = className;
        wcex.hIconSm = ::LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));
    }

    HWND Window::create() {
        if (!::RegisterClassEx(&wcex)) {
            ::MessageBox(0, L"Could not register class.", L"Error", MB_ICONEXCLAMATION | MB_OK);
            return 0;
        }

        window = ::CreateWindowEx(winStyleEx,
            className,
            title,
            winStyle, //WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS,
            posX,
            posY,
            width,
            height,
            parent,
            menu,
            instance,
            (LPVOID)controller);

        return window;
    }

    void Window::show(int cmdShow) {
        ::ShowWindow(window, cmdShow);
        ::UpdateWindow(window);
    }

}