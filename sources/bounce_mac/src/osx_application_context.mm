#include "osx_application_context.h"
#import <AppKit/NSApplication.h>
#import <AppKit/NSOpenGL.h>
#import <AppKit/NSView.h>
#import "bounce_window.h"

bounce_mac::OsxApplicationContext::OsxApplicationContext()
{
    CFBundleRef mainBundle = CFBundleGetMainBundle();
    CFURLRef resourcesURL = CFBundleCopyResourcesDirectoryURL(mainBundle);
    char path[PATH_MAX];
    if (!CFURLGetFileSystemRepresentation(resourcesURL, TRUE, (UInt8 *)path, PATH_MAX)) // Error: expected unqualified-id before 'if'
    {
        // error!
    }
    CFRelease(resourcesURL); // error: expected constructor, destructor or type conversion before '(' token
    
    root_path_ = path;
    
//    chdir(path); // error: expected constructor, destructor or type conversion before '(' token
//    std::cout << "Current Path: " << path << std::endl;
}

const std::string& bounce_mac::OsxApplicationContext::root_path() const
{
    return root_path_;
}

void bounce_mac::OsxApplicationContext::Flush() const
{
    [openGLContext flushBuffer];
}

void bounce_mac::OsxApplicationContext::Update() const
{
    NSAutoreleasePool* pool = [[NSAutoreleasePool alloc]init];
    
    NSEvent* event;
    while ( (event =
             [NSApp
              nextEventMatchingMask:NSAnyEventMask
              untilDate:nil
              inMode:NSDefaultRunLoopMode
              dequeue:YES]) != nil)
    {
        [NSApp sendEvent:event];
        //[NSApp updateWindows];
    }
    
    [pool release];
}

void bounce_mac::OsxApplicationContext::CreateWindow()
{
    NSOpenGLPixelFormatAttribute attr[] = {
        NSOpenGLPFAOpenGLProfile,
        NSOpenGLProfileVersion3_2Core,
        NSOpenGLPFAAccelerated,
        NSOpenGLPFADoubleBuffer,
        NSOpenGLPFAColorSize, 32,
        NSOpenGLPFAAlphaSize, 8,
        NSOpenGLPFADepthSize, 24,
        0
    };
    
    NSOpenGLPixelFormat *pixelFormat = [[[NSOpenGLPixelFormat alloc] initWithAttributes:attr] autorelease];
    
    openGLContext = [[NSOpenGLContext alloc] initWithFormat: pixelFormat shareContext: nil];
    
    GLint vsync = 0;
    [openGLContext setValues:&vsync forParameter:NSOpenGLCPSwapInterval];
    
    
    id window = [[[BounceWindow alloc]
                  initWithContentRect:NSMakeRect(0, 0, 640, 480)
                  styleMask:NSTitledWindowMask backing:NSBackingStoreBuffered defer:NO]
                 autorelease];
    [window cascadeTopLeftFromPoint:NSMakePoint(20,20)];
    //[window setTitle:appName];
    [window makeKeyAndOrderFront:nil];
    [window setEventManager:&event_manager()];
    
    
//    GameView* gameView = [[GameView alloc] init];
//    gameView.eventManager = eventManager;
    
    NSView* gameView = [[[NSView alloc] init] autorelease];
    
    [window setContentView: gameView];
    [openGLContext setView: gameView];
    [openGLContext makeCurrentContext];
}
