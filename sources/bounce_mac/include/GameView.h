#import <Cocoa/Cocoa.h>
#import "MacEventManager.h"
#import "bounce/event/Event.h"

@interface GameView : NSView {
	bounce_mac::MacEventManager* eventManager;
}

- (void)setEventManager: (bounce_mac::MacEventManager*) eventManager;

@end
