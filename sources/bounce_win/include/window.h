#ifndef WINDOW_H_
#define WINDOW_H_

#include <windows.h>
#include "controller.h"

namespace bounce_win {

    class Window {
    private:
        enum { MAX_STRING = 256 };

        WNDCLASSEX wcex;
        wchar_t title[MAX_STRING];
        wchar_t className[MAX_STRING];

        Controller* controller;

        HWND window;
        HINSTANCE instance;
        DWORD winStyle;
        DWORD winStyleEx;
        int posX;
        int posY;
        int width;
        int height;
        HWND parent;
        HMENU menu;

    public:

        Window(HINSTANCE hInst, const wchar_t* name, HWND parent, Controller* ctrl, const bounce::WindowContext& window_context);

        HWND create();
        void show(int cmdShow = SW_SHOWDEFAULT);

        HWND getHandle() const { return window; }

        void setWindowStyle(DWORD style) { winStyle = style; }
        void setWidth(int newWidth) { width = newWidth; }
        void setHeith(int newHeight) { height = newHeight; }

    };

}

#endif