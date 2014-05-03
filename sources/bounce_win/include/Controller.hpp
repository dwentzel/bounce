#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include <windows.h>
#include "WindowsEventManager.hpp"
#include "GLContext.hpp"

namespace bounce_win {

    class Controller {
    public:
        Controller(GLContext* glContext) : context(glContext) {}

        void setHandle(HWND wnd) { window = wnd; }

        int create();
        int keyDown(int key, LPARAM lParam);
        int keyUp(int key, LPARAM lParam);

    private:
        static void runThread(void* param);
        void run();
        
        WindowsEventManager eventManager;

        HWND window;

        GLContext* context;

        HANDLE threadHandle;
        unsigned int threadId;
    };
}

#endif