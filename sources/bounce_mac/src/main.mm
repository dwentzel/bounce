#import <Cocoa/Cocoa.h>
#import "logging/log_manager.h"
#import "bounce_application.h"
#import "app_delegate.h"
#import "osx_application_context.h"
#import "bounce_window.h"

//void bounce_ui::CreateWindow()
//{
//    NSOpenGLPixelFormatAttribute attr[] = {
//        NSOpenGLPFAOpenGLProfile,
//        NSOpenGLProfileVersion3_2Core,
//        NSOpenGLPFAColorSize, 24,
//        NSOpenGLPFAAlphaSize, 8,
//        NSOpenGLPFAAccelerated,
//        NSOpenGLPFADoubleBuffer,
//        NSOpenGLPFADepthSize, 32,
//        0
//    };
//    
//    NSOpenGLPixelFormat *pixelFormat = [[NSOpenGLPixelFormat alloc] initWithAttributes:attr];
//    
//    openGLContext = [[NSOpenGLContext alloc] initWithFormat: pixelFormat shareContext: nil];
//    
//    GLint one = 1;
//    [openGLContext setValues:&one forParameter:NSOpenGLCPSwapInterval];
//    
//    
//    id window = [[[BounceWindow alloc]
//                  initWithContentRect:NSMakeRect(0, 0, 640, 480)
//                  styleMask:NSTitledWindowMask backing:NSBackingStoreBuffered defer:NO]
//                 autorelease];
//    [window cascadeTopLeftFromPoint:NSMakePoint(20,20)];
//    //[window setTitle:appName];
//    [window makeKeyAndOrderFront:nil];
//    [window setEventManager:eventManager];
//    
//    
//    GameView* gameView = [[GameView alloc] init];
//    //gameView.eventManager = eventManager;
//    
//    [window setContentView: gameView];
//    [openGLContext setView: gameView];
//    [openGLContext makeCurrentContext];
//}

int main(int argc, char** argv) {
    
    bounce::LogManager::instance().Startup();
    
    bounce::ApplicationContext* context = new bounce_mac::OsxApplicationContext();
//    eventManager = context->event_manager_ptr();
    
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
    
    BounceApplicationDelegate* appDelegate = [[BounceApplicationDelegate alloc] initWithContext:context];
    
    [(NSApplication*)NSApp setDelegate: appDelegate];
    [NSApp setApplicationContext:context];
    [NSApp run];
    
    bounce::LogManager::instance().Shutdown();
    
    [appDelegate release];
    
    return 0;
}