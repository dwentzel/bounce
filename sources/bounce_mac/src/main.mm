#import <Cocoa/Cocoa.h>
#import "bounce_application.h"
#import "AppDelegate.h"
#import "logging/log_manager.h"
#import "bounce_mac.h"
#import "bounce_window.h"
#import "GameView.h"

void pollEvents()
{
    NSEvent *event =
    [NSApp
     nextEventMatchingMask:NSAnyEventMask
     untilDate:nil
     inMode:NSDefaultRunLoopMode
     dequeue:YES];
    
    [NSApp sendEvent:event];
    [NSApp updateWindows];
}

NSOpenGLContext* openGLContext;
bounce::EventManager* eventManager;

void draw()
{
    [openGLContext flushBuffer];
}

void bounce_ui::CreateWindow()
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
    [window setEventManager:eventManager];
    
    
    GameView* gameView = [[GameView alloc] init];
    //gameView.eventManager = eventManager;
    
    [window setContentView: gameView];
    [openGLContext setView: gameView];
    [openGLContext makeCurrentContext];
}

int main(int argc, char** argv) {
    
    bounce::LogManager::instance().Startup();
    
    bounce::ApplicationContext* context = new bounce::ApplicationContext(&draw, &pollEvents);
    eventManager = context->event_manager_ptr();
    
    [NSAutoreleasePool new];
    //NSApp = [NSApplication sharedApplication];
    NSApp = [BounceApplication sharedApplication];
    
    [NSApp setActivationPolicy:NSApplicationActivationPolicyRegular];
    id menubar = [[NSMenu new] autorelease];
    id appMenuItem = [[NSMenuItem new] autorelease];
    [menubar addItem:appMenuItem];
    [NSApp setMainMenu:menubar];
    id appMenu = [[NSMenu new] autorelease];
    id appName = [[NSProcessInfo processInfo] processName];
    id quitTitle = [@"Quit " stringByAppendingString:appName];
    id quitMenuItem = [[[NSMenuItem alloc] initWithTitle:quitTitle
                                                  action:@selector(terminate:)
                                           keyEquivalent:@"q"]
                       autorelease];
    
    [appMenu addItem:quitMenuItem];
    [appMenuItem setSubmenu:appMenu];
    
    [NSApp activateIgnoringOtherApps:YES];
    
    BounceApplicationDelegate * appDelegate = [[[BounceApplicationDelegate alloc] init] autorelease];
    appDelegate.applicationContext = context;
    
    [(NSApplication*)NSApp setDelegate: appDelegate];
    [NSApp run];
    
    bounce::LogManager::instance().Shutdown();
    
    return 0;
    
}