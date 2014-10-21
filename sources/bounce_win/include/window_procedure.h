#ifndef WINDOWPROCEDURE_H_
#define WINDOWPROCEDURE_H_

#include <windows.h>

namespace bounce_win {
    LRESULT APIENTRY WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
}

#endif