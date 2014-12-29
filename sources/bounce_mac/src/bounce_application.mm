#import "bounce_application.h"
#import "engine/bounce_main.h"

@implementation BounceApplication

@synthesize applicationContext;

- (void)run
{
    NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
    
    if ([self applicationContext] == nil) {
        @throw [NSException exceptionWithName:NSInternalInconsistencyException
                                       reason:@"applicationContext == nil"
                                     userInfo:nil];
    }
    
    [self finishLaunching];
    
    [self applicationContext]->Update();
    
    bounce_main([self applicationContext]);
        
    [pool release];
}

//- (void)terminate:(id)sender
//{
//    shouldKeepRunning = NO;
//}

@end
