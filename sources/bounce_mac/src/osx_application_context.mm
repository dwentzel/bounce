#include "osx_application_context.h"
#import <AppKit/NSApplication.h>
#import <AppKit/NSOpenGL.h>
#import <AppKit/NSView.h>
#import "bounce_window.h"

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
        NSOpenGLPFAColorSize, 24,
        NSOpenGLPFAAlphaSize, 8,
        NSOpenGLPFAAccelerated,
        NSOpenGLPFADoubleBuffer,
        NSOpenGLPFADepthSize, 32,
        0
    };
    
    NSOpenGLPixelFormat *pixelFormat = [[NSOpenGLPixelFormat alloc] initWithAttributes:attr];
    
    openGLContext = [[NSOpenGLContext alloc] initWithFormat: pixelFormat shareContext: nil];
    
    GLint one = 1;
    [openGLContext setValues:&one forParameter:NSOpenGLCPSwapInterval];
    
    
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