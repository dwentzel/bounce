#include "window_procedure.h"
#include "controller.h"


LRESULT APIENTRY bounce_win::WndProc(
    HWND hWnd,
    UINT message,
    WPARAM wParam,
    LPARAM lParam) {

    LRESULT returnValue = 0;

    static Controller *ctrl;
    ctrl = (Controller*)::GetWindowLongPtr(hWnd, GWLP_USERDATA);

    if (message == WM_NCCREATE)
    {
        ctrl = (Controller*)(((CREATESTRUCT*)lParam)->lpCreateParams);
        ctrl->setHandle(hWnd);

        ::SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)ctrl);

        return ::DefWindowProc(hWnd, message, wParam, lParam);
    }


    if (!ctrl)
        return ::DefWindowProc(hWnd, message, wParam, lParam);

    switch (message) {
    case WM_CREATE:
        returnValue = ctrl->create();
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    case WM_KEYDOWN:
    case WM_SYSKEYDOWN:
        returnValue = ctrl->keyDown((int)wParam, lParam);
        break;

    case WM_KEYUP:
    case WM_SYSKEYUP:
        returnValue = ctrl->keyUp((int)wParam, lParam);
        break;
    case WM_CHAR:
        /* handle keyboard input */
        switch ((int)wParam) {
        case VK_ESCAPE:
            DestroyWindow(hWnd);
            break;
        default:
            break;
        }
        break;
    default:
        returnValue = ::DefWindowProc(hWnd, message, wParam, lParam);
    }

    return returnValue;
}
