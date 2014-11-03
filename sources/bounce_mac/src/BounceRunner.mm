#import "BounceRunner.h"

@implementation BounceRunner

// Initialise the class
- (id)init
{
    if (self = [super init])
    {
        // create the local autorelease pool
        pPool = [[NSAutoreleasePool alloc] init];
        if (pPool != nil)
            return (self);
        else
            return (nil);
    }
    else
        // the parent has failed to initialise
        return (nil);
}

// Dispose the class
- (void)dealloc
{
    // dispose the pool
    [pPool release];
    
    // invoke the parent method
    [super dealloc];
}

@end