#import <Cocoa/Cocoa.h>
#import "bounce/application_context.h"

@interface BounceApplicationDelegate : NSObject <NSApplicationDelegate, NSWindowDelegate> {
    NSWindow* window;
	NSOpenGLContext* openGLContext;
	bounce::EventManager* eventManager;
	//@private NSView* _view;
}

- (void)createWindow;

@property(assign) NSWindow* window;
@property(assign) NSOpenGLContext* openGLContext;
@property(assign) bounce::EventManager* eventManager;
@property(assign) bounce::ApplicationContext* applicationContext;
		//@property(nonatomic, retain) NSView* view;
@end
