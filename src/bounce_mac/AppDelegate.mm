#import "AppDelegate.h"
#import "OpenGLViewCoreProfile.h"

#import "bounce/EntryPoint.h"
#import "MacEventManager.h"

@implementation MyApplicationDelegate : NSObject
@synthesize window = _window;
@synthesize view = _view;

- (id)init {
    if (self = [super init]) {
        // allocate and initialize window and stuff here ..
    }
    return self;
}

//- (void)applicationWillFinishLaunching:(NSNotification *)notification {
//    [self.window makeKeyAndOrderFront:self];
//}

- (void)dealloc {
    [self.window release];
    [super dealloc];
}



- (void)applicationDidFinishLaunching:(NSNotification *)aNotification {
    NSRect mainDisplayRect = [[NSScreen mainScreen] frame]; // I'm going to make a full screen view.
    
    NSOpenGLPixelFormatAttribute attr[] = {
        NSOpenGLPFAOpenGLProfile, NSOpenGLProfileVersion3_2Core, // Needed if using opengl 3.2 you can comment this line out to use the old version.
        NSOpenGLPFAColorSize,     24,
        NSOpenGLPFAAlphaSize,     8,
        NSOpenGLPFAAccelerated,
        NSOpenGLPFADoubleBuffer,
        0
    };
    
    NSOpenGLPixelFormat *pix = [[NSOpenGLPixelFormat alloc] initWithAttributes:attr];
    self.view = [[OpenGLViewCoreProfile alloc] initWithFrame:mainDisplayRect pixelFormat:pix];
    
    // Below shows how to make the view fullscreen. But you could just add to the contact view of any window.
    //self.window = [[NSWindow alloc] initWithContentRect:mainDisplayRect
    //                                          styleMask:NSBorderlessWindowMask
    //                                            backing:NSBackingStoreBuffered
    //                                              defer:YES];
    
    self.window.opaque = YES;
    self.window.hidesOnDeactivate = YES;
    self.window.level = NSMainMenuWindowLevel + 1; // Show window above main menu.
    self.window.contentView = self.view;
    [self.window makeKeyAndOrderFront:self]; // Display window.
    
    bounce::EntryPoint entryPoint;
    bounce_mac::MacEventManager eventManager;
    entryPoint.run(eventManager);
}

@end
