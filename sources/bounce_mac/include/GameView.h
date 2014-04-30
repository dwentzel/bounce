#import <Cocoa/Cocoa.h>
#import "MacEventManager.hpp"
#import "bounce/Event.hpp"

@interface GameView : NSView {
	bounce_mac::MacEventManager* eventManager;
}

- (void)setEventManager: (bounce_mac::MacEventManager*) eventManager;

@end
