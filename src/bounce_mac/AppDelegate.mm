#import "AppDelegate.h"
#import "GameView.h"
#import "bounce/EntryPoint.h"
#import "bounce/log.h"
#import "bounce/DefaultLogger.h"
#import "MacEventManager.h"

@interface MyApplicationDelegate()
- (void) draw;
@end

@implementation MyApplicationDelegate : NSObject

@synthesize window;
@synthesize openGLContext;
@synthesize eventManager;

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
    //NSLog(@"Drawing...");
    
    //[self.openGLContext makeCurrentContext];
    
    [self.openGLContext flushBuffer];
}

- (void)runBounce {
    [self.openGLContext makeCurrentContext];
    
    bounce::EntryPoint entryPoint;
    
    entryPoint.run(*self.eventManager, &draw, self);
}

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification {
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
    
    self.openGLContext = [[NSOpenGLContext alloc] initWithFormat: pixelFormat shareContext: nil];
    
    GLint one = 1;
    [self.openGLContext setValues:&one forParameter:NSOpenGLCPSwapInterval];
    
    bounce::Logger* logger = new bounce::DefaultLogger();
    bounce::LogManager::getInstance().setLogger(logger);
    
    self.eventManager = new bounce_mac::MacEventManager;
    
    GameView* gameView = [[GameView alloc] init];
    
    gameView.eventManager = self.eventManager;
    
    //[self.openGLContext setView:[self.window contentView]];
    [self.window setContentView: gameView];
    [self.openGLContext setView: gameView];
    
    //[self.openGLContext makeCurrentContext];
    
    [NSThread detachNewThreadSelector:@selector(runBounce) toTarget:self withObject:nil];
    //bounce::EntryPoint entryPoint;
    //bounce_mac::MacEventManager eventManager;
    //entryPoint.run(eventManager, &draw, self);
    
    
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
