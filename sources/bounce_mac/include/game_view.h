#import <Cocoa/Cocoa.h>
#import "bounce/event.h"

@interface GameView : NSView {
    bounce::EventManager* eventManager;
}

- (void)setEventManager: (bounce::EventManager*) eventManager;

@end
