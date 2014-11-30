#ifndef BOUNCE_BOUNCE_MAC_OSX_APPLICATION_CONTEXT_
#define BOUNCE_BOUNCE_MAC_OSX_APPLICATION_CONTEXT_

#import "bounce/application_context.h"
#import <AppKit/NSOpenGL.h>
#import <string>

namespace bounce_mac {

    class OsxApplicationContext : public bounce::ApplicationContext {
    private:
        NSOpenGLContext* openGLContext;
        
        std::string root_path_;
        
    public:
        OsxApplicationContext();
        
        virtual void Flush() const;
        virtual void Update() const;
        
        virtual void CreateWindow(const bounce::WindowContext& window_context);
        
        virtual const std::string& root_path() const;
    };

}

#endif // BOUNCE_BOUNCE_MAC_OSX_APPLICATION_CONTEXT_
