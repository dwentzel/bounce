#ifndef BOUNCE_WIN_CONTROLLER_HPP_
#define BOUNCE_WIN_CONTROLLER_HPP_

#include <windows.h>
#include "bounce/Event.hpp"
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
        
        bounce::EventManager eventManager;

        HWND window;

        GLContext* context;

        HANDLE threadHandle;
        unsigned int threadId;
    };
}

#endif