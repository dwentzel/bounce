#import "AppDelegate.h"
#import "OpenGLViewCoreProfile.h"

#import "bounce/EntryPoint.h"
#import "MacEventManager.h"

@interface MyApplicationDelegate()
- (void) draw;
@end

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
    
    //[self.openGLContext makeCurrentContext];
    
    [self.openGLContext flushBuffer];
}

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification {
    NSOpenGLPixelFormatAttribute attr[] = {
        NSOpenGLPFAOpenGLProfile,
        NSOpenGLProfileVersion3_2Core,
        NSOpenGLPFAColorSize,     24,
        NSOpenGLPFAAlphaSize,     8,
        NSOpenGLPFAAccelerated,
        NSOpenGLPFADoubleBuffer,
        0
    };
    
    NSOpenGLPixelFormat *pixelFormat = [[NSOpenGLPixelFormat alloc] initWithAttributes:attr];
    
    self.openGLContext = [[NSOpenGLContext alloc] initWithFormat: pixelFormat shareContext: nil];
    [self.openGLContext setView:[self.window contentView]];
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
