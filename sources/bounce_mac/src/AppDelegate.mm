#import "bounce/entry_point.h"
#import "logging/log.h"
#import "logging/default_logger.h"

#import "AppDelegate.h"
#import "GameView.h"

@interface MyApplicationDelegate()
- (void) draw;
@end

@implementation MyApplicationDelegate : NSObject

@synthesize window;
@synthesize openGLContext;
@synthesize eventManager;
@synthesize applicationContext;


NSThread* bounceThread;

- (id)init {
    if (self = [super init]) {
        // allocate and initialize window and stuff here ..
    }
    return self;
}

- (void)applicationWillTerminate:(NSNotification *)notification {
    [bounceThread cancel];
    
    while (![bounceThread isFinished]) {
        
    }
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

    if (bounceThread.isCancelled)
    {
        self.eventManager->queueEvent(bounce::EventPtr(new bounce::QuitEvent()));
    }
    
    [self.openGLContext flushBuffer];
}

- (void)runBounce {
    [self.openGLContext makeCurrentContext];
    
    bounce::EntryPoint entryPoint;
    
    entryPoint.run(*self.applicationContext);
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
    bounce::LogManager::instance().set_logger(logger);
        
    self.applicationContext = new bounce::ApplicationContext(&draw, self);
    self.eventManager = self.applicationContext->event_manager_ptr();
    
    GameView* gameView = [[GameView alloc] init];
    
    gameView.eventManager = self.eventManager;
    
    [self.window setContentView: gameView];
    [self.openGLContext setView: gameView];
    
    bounceThread = [[NSThread alloc]initWithTarget:self selector:@selector(runBounce) object:nil];
    [bounceThread start];
}

- (BOOL)applicationShouldTerminateAfterLastWindowClosed:(NSApplication *)_app {
    return YES;
}
@end
