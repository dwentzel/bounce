#import <Cocoa/Cocoa.h>
#import "bounce/application_context.h"

@interface BounceApplicationDelegate : NSObject <NSApplicationDelegate, NSWindowDelegate> {
    bounce::ApplicationContext* application_context_;
    bounce::EventManager* event_manager_;
}

- (id)initWithContext:(bounce::ApplicationContext*)context;

@end
