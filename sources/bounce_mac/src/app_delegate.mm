#import "logging/log.h"
#import "app_delegate.h"

@implementation BounceApplicationDelegate : NSObject


- (id)init {
    
    [self release];
    
    @throw [NSException exceptionWithName:NSInternalInconsistencyException
                                   reason:@"-init is not a valid initializer for BounceApplicationDelegate"
                                 userInfo:nil];
    
    return nil;
    
    if (self = [super init]) {
        // allocate and initialize window and stuff here ..
    }

    return self;
}

- (id)initWithContext:(bounce::ApplicationContext*)context {
    if (self = [super init]) {
        application_context_ = context;
        event_manager_ = application_context_->event_manager_ptr();
    }
    
    return self;
}

- (void)applicationWillTerminate:(NSNotification *)notification {
    event_manager_->QueueEvent(bounce::EventPtr(new bounce::QuitEvent()));
}

//- (void)applicationWillFinishLaunching:(NSNotification *)notification {
//    [self.window makeKeyAndOrderFront:self];
//}


- (void)dealloc {
    [super dealloc];
}


- (void)applicationDidFinishLaunching:(NSNotification *)aNotification {
//    bounce_main(application_context_);
}

- (BOOL)applicationShouldTerminateAfterLastWindowClosed:(NSApplication *)_app {
    return YES;
}

@end
