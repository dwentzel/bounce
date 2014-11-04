#import <Cocoa/Cocoa.h>

@interface BounceRunner : NSObject
{
    NSAutoreleasePool *pPool;
//    NSOpenGLContext* openGLContext;
}

@property(assign) NSOpenGLContext* openGLContext;

- (void)RunBounce;

@end