#import "GameView.h"
#import "bounce/Event.h"
#import "bounce/LockFreeQueue.h"

@interface GameView()
{
    
}

@end

@implementation GameView : NSView

@synthesize eventManager = eventManager;

- (BOOL)acceptsFirstResponder {
    return YES;
}

- (void)keyDown:(NSEvent *) event {
    NSLog(@"Pressed key");
    
    self.eventManager->queueEvent(new bounce::KeydownEvent());
}

@end