#import "bounce_application.h"

@implementation BounceApplication

bool shouldKeepRunning;

- (void)run
{
    NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
    
    [self finishLaunching];
    
    shouldKeepRunning = YES;
    do
    {
        [pool release];
        pool = [[NSAutoreleasePool alloc] init];
        
        NSEvent *event =
        [self
         nextEventMatchingMask:NSAnyEventMask
         untilDate:[NSDate distantFuture]
         inMode:NSDefaultRunLoopMode
         dequeue:YES];
        
        [self sendEvent:event];
        [self updateWindows];
    } while (shouldKeepRunning);
    
    [pool release];
}

- (void)terminate:(id)sender
{
    shouldKeepRunning = NO;
}

@end
