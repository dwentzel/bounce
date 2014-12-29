#import <Cocoa/Cocoa.h>
#import "engine/application_context.h"

@interface BounceApplicationDelegate : NSObject <NSApplicationDelegate, NSWindowDelegate>

- (id)initWithContext:(bounce::ApplicationContext*)context;

@end
