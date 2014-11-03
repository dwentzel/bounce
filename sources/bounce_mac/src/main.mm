#import <Cocoa/Cocoa.h>
#import "AppDelegate.h"

int main(int argc, char** argv) {
    [NSAutoreleasePool new];
    [NSApplication sharedApplication];
    [NSApp setActivationPolicy:NSApplicationActivationPolicyRegular];
    id menubar = [[NSMenu new] autorelease];
    id appMenuItem = [[NSMenuItem new] autorelease];
    [menubar addItem:appMenuItem];
    [NSApp setMainMenu:menubar];
    id appMenu = [[NSMenu new] autorelease];
    id appName = [[NSProcessInfo processInfo] processName];
    id quitTitle = [@"Quit " stringByAppendingString:appName];
    id quitMenuItem = [[[NSMenuItem alloc] initWithTitle:quitTitle
                                                  action:@selector(terminate:) keyEquivalent:@"q"] autorelease];
    [appMenu addItem:quitMenuItem];
    [appMenuItem setSubmenu:appMenu];
    id window = [[[NSWindow alloc] initWithContentRect:NSMakeRect(0, 0, 640, 480)
                                             styleMask:NSTitledWindowMask backing:NSBackingStoreBuffered defer:NO]
                 autorelease];
    [window cascadeTopLeftFromPoint:NSMakePoint(20,20)];
    [window setTitle:appName];
    [window makeKeyAndOrderFront:nil];
    [NSApp activateIgnoringOtherApps:YES];
    
    MyApplicationDelegate * appDelegate = [[[MyApplicationDelegate alloc] init] autorelease];
    
    appDelegate.window = window;
    [(NSApplication*)NSApp setDelegate: appDelegate];
    [NSApp run];
    return 0;

}