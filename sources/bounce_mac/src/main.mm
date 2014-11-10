#import <Cocoa/Cocoa.h>
#import "logging/log_manager.h"
#import "bounce_application.h"
#import "app_delegate.h"
#import "osx_application_context.h"
#import "bounce_window.h"

int main(int argc, char** argv)
{    
    bounce::LogManager::instance().Startup();
    
    bounce::ApplicationContext* context = new bounce_mac::OsxApplicationContext();
    
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