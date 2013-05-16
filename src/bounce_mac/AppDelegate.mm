#import "AppDelegate.h"
#import "OpenGLViewCoreProfile.h"

#import "bounce/EntryPoint.h"
#import "MacEventManager.h"

@implementation MyApplicationDelegate : NSObject
@synthesize window;
@synthesize openGLContext;

//@synthesize window = _window;
//@synthesize view = _view;

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

void draw(void* context) {
    MyApplicationDelegate* appDelegate = (MyApplicationDelegate*)context;
    [appDelegate draw];
}

- (void)draw {
    NSLog(@"Drawing...");
    
    [self.openGLContext makeCurrentContext];
    
    //glClearColor(1, 0, 1, 1);
    //glClear(GL_COLOR_BUFFER_BIT);
    
    [self.openGLContext flushBuffer];
}

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification {
    //NSRect mainDisplayRect = [[NSScreen mainScreen] frame]; // I'm going to make a full screen view.
    
    //NSRect frame = NSMakeRect(0, 0, 200, 200);
    
    //self.window = [[[NSWindow alloc] initWithContentRect:frame
    //                                         styleMask:NSTitledWindowMask backing:NSBackingStoreBuffered defer:NO]
    //             autorelease];
    //[self.window cascadeTopLeftFromPoint:NSMakePoint(20,20)];
    
    //id appName = [[NSProcessInfo processInfo] processName];
    //[self.window setTitle:appName];
    //[self.window makeKeyAndOrderFront:nil];
    
    NSOpenGLPixelFormatAttribute attr[] = {
        NSOpenGLPFAOpenGLProfile,
        NSOpenGLProfileVersion3_2Core, // Needed if using opengl 3.2 you can comment this line out to use the old version.
        NSOpenGLPFAColorSize,     24,
        NSOpenGLPFAAlphaSize,     8,
        NSOpenGLPFAAccelerated,
        NSOpenGLPFADoubleBuffer,
        0
    };
    
    NSOpenGLPixelFormat *pix = [[NSOpenGLPixelFormat alloc] initWithAttributes:attr];
    self.openGLContext = [[NSOpenGLContext alloc] initWithFormat: pix shareContext: nil];
    [self.openGLContext setView:[self.window contentView]];
    //self.view = [[OpenGLViewCoreProfile alloc] initWithFrame:self.window.frame pixelFormat:pix];
    
    //self.view = [[OpenGLViewCoreProfile alloc] initWithPixelFormat:pix];
    
    // Below shows how to make the view fullscreen. But you could just add to the contact view of any window.
    //self.window = [[NSWindow alloc] initWithContentRect:mainDisplayRect
    //                                          styleMask:NSBorderlessWindowMask
    //                                            backing:NSBackingStoreBuffered
    //                                              defer:YES];
    
    //self.window.opaque = YES;
    //self.window.hidesOnDeactivate = YES;
    //self.window.level = NSMainMenuWindowLevel + 1; // Show window above main menu.
    //self.window.contentView = self.view;
    
    //NSOpenGLContext* context = [NSOpenGLContext currentContext];
    //[context makeCurrentContext];
    //[self.window makeKeyAndOrderFront:self]; // Display window.
    [self.openGLContext makeCurrentContext];
    bounce::EntryPoint entryPoint;
    bounce_mac::MacEventManager eventManager;
    entryPoint.run(eventManager, &draw, self);
    
//    [NSTimer
//     scheduledTimerWithTimeInterval:.1
//     target:self
//     selector:@selector(draw)
//     userInfo:nil
//     repeats:YES];
}

- (BOOL)applicationShouldTerminateAfterLastWindowClosed:(NSApplication *)_app {
    return YES;
}
@end
