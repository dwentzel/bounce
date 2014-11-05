#import <Cocoa/Cocoa.h>
#import "bounce_mac.h"
#import "AppDelegate.h"

void bounce_ui::CreateWindow()
{
    MyApplicationDelegate* appDelegate = (MyApplicationDelegate*)[NSApp delegate];
    [appDelegate createWindow];
}