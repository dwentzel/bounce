#import <AppKit/NSWindow.h>
#import "engine/event_manager.h"

@interface BounceWindow : NSWindow

@property (nonatomic, assign)bounce::EventManager* eventManager;

@end
