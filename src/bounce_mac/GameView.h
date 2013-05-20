#import <Cocoa/Cocoa.h>
#import "MacEventManager.h"
#import "bounce/Event.h"

@interface GameView : NSView {
	bounce_mac::MacEventManager* eventManager;
}

@property (assign) bounce_mac::MacEventManager* eventManager;

@end
