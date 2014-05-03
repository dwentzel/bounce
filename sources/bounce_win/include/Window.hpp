#ifndef WINDOW_H_
#define WINDOW_H_

#include <windows.h>
#include "Controller.hpp"

namespace bounce_win {

    class Window {
    public:

        Window(HINSTANCE hInst, const wchar_t* name, HWND parent, Controller* ctrl);

        HWND create();
        void show(int cmdShow = SW_SHOWDEFAULT);

        HWND getHandle() const { return window; }

        void setWindowStyle(DWORD style) { winStyle = style; }
        void setWidth(int newWidth) { width = newWidth; }
        void setHeith(int newHeight) { height = newHeight; }

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
    };

}

#endif