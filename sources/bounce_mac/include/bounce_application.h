#import <AppKit/NSApplication.h>
#import "engine/application_context.h"

@interface BounceApplication : NSApplication

@property (nonatomic, assign)bounce::ApplicationContext* applicationContext;

@end
