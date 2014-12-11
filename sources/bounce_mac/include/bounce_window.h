#import <AppKit/NSWindow.h>
#import "engine/event_manager.h"

@interface BounceWindow : NSWindow {
    @private
    bounce::EventManager* eventManager_;
}

- (void)setEventManager: (bounce::EventManager*) eventManager;

@end
