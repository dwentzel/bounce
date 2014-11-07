#ifndef BOUNCE_BOUNCE_MAC_OSX_APPLICATION_CONTEXT_
#define BOUNCE_BOUNCE_MAC_OSX_APPLICATION_CONTEXT_

#import "bounce/application_context.h"
#import <AppKit/NSOpenGL.h>

namespace bounce_mac {

    class OsxApplicationContext : public bounce::ApplicationContext {
    private:
        NSOpenGLContext* openGLContext;
        
    public:

        virtual void Flush() const;
        virtual void Update() const;
        
        virtual void CreateWindow();
    };

}

#endif // BOUNCE_BOUNCE_MAC_OSX_APPLICATION_CONTEXT_
