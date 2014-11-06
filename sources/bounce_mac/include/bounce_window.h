#import <AppKit/NSWindow.h>
#import "bounce/event.h"

@interface BounceWindow : NSWindow {
    @private
    bounce::EventManager* eventManager_;
}

- (void)setEventManager: (bounce::EventManager*) eventManager;

@end