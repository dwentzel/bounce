#import "bounce_application.h"
#import "engine/bounce_main.h"

@implementation BounceApplication

bool shouldKeepRunning;

- (void)setApplicationContext:(bounce::ApplicationContext *)context {
    applicationContext = context;
}

- (void)run
{
    NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
    
    if (applicationContext == nil) {
        @throw [NSException exceptionWithName:NSInternalInconsistencyException
                                       reason:@"applicationContext == nil"
                                     userInfo:nil];
    }
    
    [self finishLaunching];
    
    applicationContext->Update();
    
    bounce_main(applicationContext);
        
    [pool release];
}

//- (void)terminate:(id)sender
//{
//    shouldKeepRunning = NO;
//}

@end
