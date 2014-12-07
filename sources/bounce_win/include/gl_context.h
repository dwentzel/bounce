#ifndef BOUNCE_WIN_GLCONTEXT_HPP_
#define BOUNCE_WIN_GLCONTEXT_HPP_

#include <windows.h>

namespace bounce_win {

    class GLContext {
    private:
        static bool setPixelFormat(HDC hdc, int colorBits, int depthBits, int stencilBits);
        static int findPixelFormat(HDC hdc, int colorbits, int depthBits, int stencilBits);

        HDC hdc;
        HGLRC hglrc;

    public:
        GLContext();
        ~GLContext();

        bool createContext(HWND window, int colorBits, int depthBits, int stencilBits);
        void flush() { ::SwapBuffers(hdc); }

        HDC getDC() const { return hdc; }
        HGLRC getRC() const { return hglrc; }


    };

}

#endif