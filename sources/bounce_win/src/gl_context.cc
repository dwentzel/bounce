#include "gl_context.h"

namespace bounce_win {

    GLContext::GLContext() : hdc(0), hglrc(0) {

    }

    GLContext::~GLContext() {

    }

    bool GLContext::createContext(HWND window, int colorBits, int depthBits, int stencilBits) {
        hdc = ::GetDC(window);

        if (!setPixelFormat(hdc, colorBits, depthBits, stencilBits))
        {
            ::MessageBox(0, L"Cannot set a suitable pixel format.", L"Error", MB_ICONEXCLAMATION | MB_OK);
            ::ReleaseDC(window, hdc);
            return false;
        }

        hglrc = ::wglCreateContext(hdc);
        //::ReleaseDC(window, hdc);
        return true;
    }

    bool GLContext::setPixelFormat(HDC hdc, int colorBits, int depthBits, int stencilBits)
    {
        PIXELFORMATDESCRIPTOR pfd;

        int pixelFormat = findPixelFormat(hdc, colorBits, depthBits, stencilBits);
        if (pixelFormat == 0) {
            return false;
        }

        ::DescribePixelFormat(hdc, pixelFormat, sizeof(pfd), &pfd);

        if (!::SetPixelFormat(hdc, pixelFormat, &pfd)) {
            return false;
        }

        return true;
    }

    bool pixelFormatFulfillsRequirements(const PIXELFORMATDESCRIPTOR& pfd) {

        if (!(pfd.dwFlags & PFD_SUPPORT_OPENGL)) {
            return false;
        }

        if (!(pfd.dwFlags & PFD_DRAW_TO_WINDOW)) {
            return false;
        }

        if ((pfd.iPixelType != PFD_TYPE_RGBA) || (pfd.dwFlags & PFD_NEED_PALETTE)) {
            return false;
        }

        if (!(pfd.dwFlags & PFD_DOUBLEBUFFER)) {
            return false;
        }

        return true;
    }

    int GLContext::findPixelFormat(HDC hdc, int colorBits, int depthBits, int stencilBits)
    {
        int currentMode = 0;
        int bestMode = 0;
        int currentScore = 0;
        int bestScore = 0;
        PIXELFORMATDESCRIPTOR pfd;

        while (::DescribePixelFormat(hdc, ++currentMode, sizeof(pfd), &pfd) > 0)
        {
            if (!pixelFormatFulfillsRequirements(pfd)) {
                continue;
            }

            // try to find best candidate
            currentScore = 0;

            // colour bits
            if (pfd.cColorBits >= colorBits) {
                ++currentScore;
            }

            if (pfd.cColorBits == colorBits) {
                ++currentScore;
            }

            // depth bits
            if (pfd.cDepthBits >= depthBits) {
                ++currentScore;
            }

            if (pfd.cDepthBits == depthBits) {
                ++currentScore;
            }

            // stencil bits
            if (pfd.cStencilBits >= stencilBits) {
                ++currentScore;
            }

            if (pfd.cStencilBits == stencilBits) {
                ++currentScore;
            }

            // alpha bits
            if (pfd.cAlphaBits > 0) {
                ++currentScore;
            }

            if (currentScore > bestScore)
            {
                bestScore = currentScore;
                bestMode = currentMode;
            }
        }

        return bestMode;
    }
}