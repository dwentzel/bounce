#ifndef BOUNCE_WIN_WINDOWS_APPLICATION_CONTEXT
#define BOUNCE_WIN_WINDOWS_APPLICATION_CONTEXT

#include <Windows.h>

#include "engine/application_context.h"
#include "engine/window_context.h"

#include "gl_context.h"

namespace bounce_win {

    class WindowsApplicationContext : public bounce::ApplicationContext {
    private:
        HINSTANCE hInstance_;

        GLContext* gl_context_;

        std::string root_path_;

    public:
        WindowsApplicationContext(HINSTANCE hInstance);

        virtual void Flush() const;

        virtual void Update() const;

        virtual void CreateApplicationWindow(const bounce::WindowContext& window_context);

        virtual const std::string& root_path() const;

    };


}

#endif // BOUNCE_WIN_WINDOWS_APPLICATION_CONTEXT