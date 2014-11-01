#include <process.h>
#include "bounce/entry_point.h"
#include "controller.h"

namespace bounce_win {

    void flush(void* context)
    {
        GLContext* glContext = (GLContext*)context;

        glContext->flush();
        Sleep(10);
    }

    Controller::Controller(GLContext* context) : context_(context), application_context_(flush, context)
    {

    }

    Controller::~Controller()
    {

    }

    void Controller::run_thread(void* param)
    {
        ((Controller*)param)->run();
    }

    int Controller::create()
    {
        if (!context_->createContext(window_, 32, 24, 8))
        {
            //Win::log(L"[ERROR] Failed to create OpenGL rendering context from ControllerGL::create().");
            return -1;
        }

        thread_handle_ = (HANDLE)_beginthreadex(0, 0, (unsigned(__stdcall *)(void *))run_thread, this, 0, &thread_id_);
        if (thread_handle_)
        {
            //loopFlag = true;
            //Win::log(L"Created a rendering thread for OpenGL.");
        }
        else
        {
            //Win::log(L"[ERROR] Failed to create rendering thread from ControllerGL::create().");
        }

        return 0;
    }



    void Controller::run()
    {
        ::wglMakeCurrent(context_->getDC(), context_->getRC());

        bounce::EntryPoint entryPoint = bounce::EntryPoint();

        entryPoint.run(application_context_);

        ::wglMakeCurrent(0, 0);
        ::CloseHandle(thread_handle_);
    }

    int Controller::keyDown(int key, LPARAM lParam)
    {
        bounce::Keysym keysym;
        keysym.mod = bounce::Modifier::NO_MODIFIER;
        keysym.sym = bounce::Key::NO_KEY;

        bool triggerEvent = true;

        switch (key) {
        case 0x41:
            keysym.sym = bounce::Key::A;
            break;
        case 0x44:
            keysym.sym = bounce::Key::D;
            break;
        case 0x45:
            keysym.sym = bounce::Key::E;
            break;
        case 0x51:
            keysym.sym = bounce::Key::Q;
            break;
        case 0x53:
            keysym.sym = bounce::Key::S;
            break;
        case 0x57:
            keysym.sym = bounce::Key::W;
            break;
        default:
            triggerEvent = false;
            break;
        }

        if (triggerEvent) {
            application_context_.event_manager().queueEvent(std::unique_ptr<bounce::Event>(new bounce::KeydownEvent(keysym)));
        }

        return 0;
    }

    int Controller::keyUp(int key, LPARAM lParam)
    {
        bounce::Keysym keysym;
        keysym.mod = bounce::Modifier::NO_MODIFIER;
        keysym.sym = bounce::Key::NO_KEY;

        bool triggerEvent = true;

        switch (key) {
        case 0x41:
            keysym.sym = bounce::Key::A;
            break;
        case 0x44:
            keysym.sym = bounce::Key::D;
            break;
        case 0x53:
            keysym.sym = bounce::Key::S;
            break;
        case 0x57:
            keysym.sym = bounce::Key::W;
            break;
        default:
            triggerEvent = false;
            break;
        }

        if (triggerEvent) {
            application_context_.event_manager().queueEvent(std::unique_ptr<bounce::Event>(new bounce::KeyupEvent(keysym)));
        }

        return 0;
    }
}