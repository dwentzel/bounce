#import <AppKit/NSApplication.h>
#import "bounce/application_context.h"

@interface BounceApplication : NSApplication {
    bounce::ApplicationContext* applicationContext;
}

- (void)setApplicationContext:(bounce::ApplicationContext*)context;

@end
