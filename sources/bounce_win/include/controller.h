#ifndef BOUNCE_WIN_CONTROLLER_HPP_
#define BOUNCE_WIN_CONTROLLER_HPP_

#include <windows.h>
#include "bounce/event.h"
#include "bounce/application_context.h"
#include "gl_context.h"

namespace bounce_win {

    class Controller {
    public:
        Controller(GLContext* context);
        ~Controller();

        void setHandle(HWND window) { window_ = window; }

        int create();
        int keyDown(int key, LPARAM lParam);
        int keyUp(int key, LPARAM lParam);

    private:
        static void run_thread(void* param);
        void run();
        bounce::Key KeyCodeToKey(int keycode);

        bounce::ApplicationContext application_context_;

        HWND window_;
        GLContext* context_;

        HANDLE thread_handle_;
        unsigned int thread_id_;
    };
}

#endif