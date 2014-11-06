#import "bounce/bounce_main.h"

#import "logging/log.h"

#import "AppDelegate.h"
#import "GameView.h"

@interface BounceApplicationDelegate()
- (void) draw;
@end

@implementation BounceApplicationDelegate : NSObject

@synthesize window;
@synthesize openGLContext;
@synthesize eventManager;
@synthesize applicationContext;


//NSThread* bounceThread;

- (id)init {
    if (self = [super init]) {
        // allocate and initialize window and stuff here ..
    }
    return self;
}

- (void)applicationWillTerminate:(NSNotification *)notification {
    self.eventManager->QueueEvent(bounce::EventPtr(new bounce::QuitEvent()));
    
    quit = true;
    
//    [bounceThread cancel];
//    
//    while (![bounceThread isFinished]) {
//        
//    }
}

//- (void)applicationWillFinishLaunching:(NSNotification *)notification {
//    [self.window makeKeyAndOrderFront:self];
//}

bool quit = false;

- (void)dealloc {
    [self.window release];
    [super dealloc];
}

void draw(void* context) {
    BounceApplicationDelegate* appDelegate = (BounceApplicationDelegate*)context;
    [appDelegate draw];
}

- (void)draw {
    
//    if (bounceThread.isCancelled)
//    {
//        self.eventManager->queueEvent(bounce::EventPtr(new bounce::QuitEvent()));
//    }
    
    NSEvent *event =
    [NSApp
     nextEventMatchingMask:NSAnyEventMask
     untilDate:nil
     inMode:NSDefaultRunLoopMode
     dequeue:YES];
    
    if (!quit)
        [NSApp sendEvent:event];
    
    [NSApp updateWindows];
    
    [self.openGLContext flushBuffer];
}


- (void)applicationDidFinishLaunching:(NSNotification *)aNotification {
    
//    self.applicationContext = new bounce::ApplicationContext(&draw, self);
//    self.eventManager = self.applicationContext->event_manager_ptr();
    
    bounce_main(self.applicationContext);
    
    //bounceThread = [[NSThread alloc]initWithTarget:self selector:@selector(runBounce) object:nil];
    //[bounceThread start];
}

- (BOOL)applicationShouldTerminateAfterLastWindowClosed:(NSApplication *)_app {
    return YES;
}

@end
