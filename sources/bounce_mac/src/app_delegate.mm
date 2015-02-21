#import "logging/log.h"
#import "app_delegate.h"

@interface BounceApplicationDelegate()

@property (nonatomic, assign)bounce::ApplicationContext* applicationContext;
@property (nonatomic, assign)bounce::EventManager* eventManager;

@end

@implementation BounceApplicationDelegate

@synthesize applicationContext;
@synthesize eventManager;

- (id)init {
    
    [self release];
    
    @throw [NSException exceptionWithName:NSInternalInconsistencyException
                                   reason:@"-init is not a valid initializer for BounceApplicationDelegate"
                                 userInfo:nil];
}

- (id)initWithContext:(bounce::ApplicationContext*)context {
    if ((self = [super init])) {
        [self setApplicationContext:context];
        [self setEventManager:[self applicationContext]->event_manager_ptr()];
    }
    
    return self;
}

- (void)applicationWillTerminate:(NSNotification *)notification {
#pragma unused (notification)
    [self eventManager]->QueueEvent(bounce::EventPtr(new bounce::QuitEvent()));
}

//- (void)applicationWillFinishLaunching:(NSNotification *)notification {
//    [self.window makeKeyAndOrderFront:self];
//}


- (void)dealloc {
    [super dealloc];
}


- (void)applicationDidFinishLaunching:(NSNotification *)notification {
#pragma unused (notification)
//    bounce_main(application_context_);
}

- (BOOL)applicationShouldTerminateAfterLastWindowClosed:(NSApplication *)app {
#pragma unused (app)
    return YES;
}

@end
