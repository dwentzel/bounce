#include <process.h>
#include "bounce\EntryPoint.hpp"
#include "Controller.hpp"

namespace bounce_win {

    void Controller::runThread(void* param)
    {
        ((Controller*)param)->run();
    }

    int Controller::create()
    {
        if (!context->createContext(window, 32, 24, 8))
        {
            //Win::log(L"[ERROR] Failed to create OpenGL rendering context from ControllerGL::create().");
            return -1;
        }

        threadHandle = (HANDLE)_beginthreadex(0, 0, (unsigned(__stdcall *)(void *))runThread, this, 0, &threadId);
        if (threadHandle)
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

    void flush(void* context)
    {
        GLContext* glContext = (GLContext*)context;

        glContext->flush();
        Sleep(10);
    }

    void Controller::run()
    {
        ::wglMakeCurrent(context->getDC(), context->getRC());

        bounce::EntryPoint entryPoint = bounce::EntryPoint();

        bounce::ApplicationContext applicationContext = bounce::ApplicationContext();

        entryPoint.run(applicationContext, eventManager, flush, context);

        ::wglMakeCurrent(0, 0);
        ::CloseHandle(threadHandle);
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
            eventManager.queueEvent(std::unique_ptr<bounce::Event>(new bounce::KeydownEvent(keysym)));
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
            eventManager.queueEvent(std::unique_ptr<bounce::Event>(new bounce::KeyupEvent(keysym)));
        }

        return 0;
    }
}